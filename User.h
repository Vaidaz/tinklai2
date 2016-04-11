#ifndef USER_H
#define USER_H

#include <cstdlib>
#include <iostream>
using namespace std;

class User{
  private:
    string nick;
    string password;
    string real_name;
    string randomPassword();
  public:
    User();
    User(string nick, string real_name);
    ~User();
    void setRealName(string real_name);
    void setNick(string nick);
    void setPassword(string password);
    string getRealName();
    string getNick();
    string getPassword();
};

#endif