#include "./IrcMessage.h"

IrcMessage::IrcMessage(){

};

IrcMessage::IrcMessage(string msg){
  this->message = msg;
};

IrcMessage::~IrcMessage(){

};

void IrcMessage::setMessage(string message){
  this->message = message;
};

string IrcMessage::getMessage(){
  return this->message;
};

string IrcMessage::getPrefix(){
  return this->prefix;
};

string IrcMessage::getCommand(){
  return this->command;
};

string IrcMessage::getNick(){
  return this->nick;
};

vector<string> IrcMessage::getParams(){
  return this->params;
};

void IrcMessage::parse(){
  string message = StringUtils::cutUntillNewLine(this->message);
  vector<string> words = StringUtils::splitBySpaces(message);

  string word;
  for(int i = 0; i < words.size(); i++){
    word = words[i];

    if(i == 0 && word[0] == ':'){
      this->prefix = word;
    } else if(this->command.empty()){
      this->command = word;
    } else {
      // Jei parametras turi : tai trailing
      if(word[0] == ':'){
        word.erase(0,1); // Ištrinu :
        for(int j = i + 1; j < words.size(); j++){
          word = word + " " + words[j];
        }
        this->params.push_back(word);
        break;
      } else {
        this->params.push_back(word);
      }
    }
  }

  string *str;
  for(int i = 0; i < this->prefix.length(); i++){
    switch(this->prefix[i]){
      case ':': str = &this->nick;
                break;
      case '!': str = &this->user;
                break;
      case '@': str = &this->host;
                break;
      default: *str += this->prefix[i];

    }
  }
};

string IrcMessage::getParmsString(){
  string str = "";
  for(int i = 0; i < params.size(); i++){
    str += params[i];
  }
  return str;
};
