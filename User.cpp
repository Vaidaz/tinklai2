#include "./User.h"

User::User(){
  this->password = randomPassword();
};

User::~User(){};

User::User(string nick, string real_name){
  this->nick = nick;
  this->real_name = real_name;
  this->password = randomPassword();
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


