#include "./User.h"

User::User(){
  this->password = randomPassword();
  initMainChannel();
};

void User::initMainChannel(){
  Channel main;
  main.setTitle("main");
  this->channels.push_back(main);
  this->active_channel_title = "main";
};

User::~User(){};

User::User(string nick, string real_name){
  this->nick = nick;
  this->real_name = real_name;
  this->password = randomPassword();
  initMainChannel();
};

string User::randomPassword(){
  string password;
  srand(time(NULL));
  for(int i = 0; i < 20; i++){
    password += rand() % 10 + '0';
  }
  return password;
};

string User::getRealName(){
  return this->real_name;
};

string User::getNick(){
  return this->nick;
};

string User::getPassword(){
  return this->password;
};

void User::setRealName(string real_name){
  this->real_name = real_name;
};

void User::setNick(string nick){
  this->nick = nick;
};

void User::setPassword(string password){
  this->password = password;
};

Channel User::getChannel(string title){
  Channel channel;
  for(int i = 0; i < this->channels.size(); i++){
    channel = this->channels[i];
    if(channel.getTitle() == title){
      return channel;
    }
  }
  return getActiveChannel();
};

void User::addChannel(Channel channel){
  this->channels.push_back(channel);
};

void User::addChannel(string title){
  Channel channel;
  channel.setTitle(title);
  addChannel(channel);
};

void User::removeChannel(string title){
  Channel channel;
  for(int i = 0; i < this->channels.size(); i++){
    channel = this->channels[i];
    if(channel.getTitle() == title){
      this->channels.erase(this->channels.begin() + i);
    }
  }
};

Channel User::getActiveChannel(){
  return getChannel(this->active_channel_title);
};

void User::changeActiveChannel(string title){
  Channel channel;
  for(int i = 0; i < this->channels.size(); i++){
    channel = this->channels[i];
    if(channel.getTitle() == title){
      this->active_channel_title = title;
    }
  }
};

vector<string> User::getActiveChannelMessages(int number){
  vector<string> all_messages = getActiveChannel().getMessages();
  vector<string> few_messages;
  int messages_count = all_messages.size();

  if(messages_count <= number){
    return all_messages;
  } else {
    for(int i = messages_count - number; i < messages_count; i++){
      few_messages.push_back(all_messages[i]);
    }
    return few_messages;
  }

};

void User::addMessageToChannel(string channel_title, string message){
  for(int i = 0; i < this->channels.size(); i++){
    if(channels[i].getTitle() == channel_title){
      channels[i].addMessage(message);
    }
  }
}
