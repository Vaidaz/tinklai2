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

void Irc::registerUser(){
  sendMessage("PASS " + this->user->getPassword());
  sendMessage("NICK " + this->user->getNick());
  sendMessage("USER guest tolmoon tolsun: Some User");
};

void Irc::join(string str){
  sendMessage("JOIN " + str);
};

void Irc::privateMessage(string params, string msg){
  sendMessage("PRIVMSG " + params + " :" + msg);
};
