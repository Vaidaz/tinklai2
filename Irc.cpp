#include "./Irc.h"

Irc::Irc(){

};

Irc::~Irc(){

};

void Irc::setSocket(Socket *socket){
  this->socket = socket;
};

void Irc::setUser(User *user){
  this->user = user;
};

void Irc::sendMessage(string msg){
  this->socket->sendMessage(msg + "\r\n");
};

int Irc::isMessage(){
  return this->socket->isPackage();
};

IrcMessage Irc::receiveIrcMessage(){
  string msg = this->socket->receiveMessage();
  IrcMessage irc_message(msg);
  irc_message.parse();
  return irc_message;
};


void Irc::receiveAndExecuteMessage(){
  IrcMessage ircmsg = receiveIrcMessage();

  string command = ircmsg.getCommand();
  vector<string> params = ircmsg.getParams();

  if (command == "PRIVMSG"){
    string channels_string = params[0];
    string message = params[1];

    Channel channel;
    string full_msg;
    vector<string> channel_titles = StringUtils::splitByComma(channels_string);

    for(int i = 0; i < channel_titles.size(); i++){
      full_msg = ircmsg.getNick() + ": " + message + "\n";
      this->user->addMessageToChannel(channel_titles[i], full_msg);
    }
  }
};

void Irc::registerUser(){
  sendMessage("PASS " + this->user->getPassword());
  sendMessage("NICK " + this->user->getNick());
  sendMessage("USER guest tolmoon tolsun: Some User");
};

void Irc::join(string str){
  sendMessage("JOIN " + str);
  vector<string> parts = StringUtils::splitBySpaces(str);
  string channels_part = parts[0];
  vector<string> channel_titles = StringUtils::splitByComma(str);
  for(int i = 0; i < channel_titles.size(); i++){
    this->user->addChannel(channel_titles[i]);
  }
};

void Irc::privateMessage(string params, string msg){
  sendMessage("PRIVMSG " + params + " :" + msg);
};

void Irc::changeChannel(string title){
  this->user->changeActiveChannel(title);
};

void Irc::parseAndExecute(string msg){
  if(msg[0] == '/'){
    IrcMessage ircmsg(msg);
    ircmsg.parse();
    // command
    string command = ircmsg.getCommand();
    if (command == "/join"){
      join( ircmsg.getParmsString() );
    } else if (command == "/cc"){
      changeChannel( ircmsg.getParmsString() );
    }
  } else {
    Channel active_channel = this->user->getActiveChannel();
    string full_msg = this->user->getNick() + ": " + msg;
    privateMessage(active_channel.getTitle(), msg);
    this->user->addMessageToChannel(active_channel.getTitle(), full_msg);
  }
};
