#include "./Channel.h"

Channel::Channel(){

}
void Channel::setTitle(string title){
  this->title = title;
}
string Channel::getTitle(){
  return this->title;
}
void Channel::addMessage(string message){
  this->messages.push_back(message);
}
vector<string> Channel::getMessages(){
  return this->messages;
}
Channel::~Channel(){

}
