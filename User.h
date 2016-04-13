#ifndef USER_H
#define USER_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include "./Channel.h"
using namespace std;

class User{
  private:
    string nick;
    string password;
    string real_name;
    string randomPassword();
    vector<Channel> channels;
    string active_channel_title;
    void initMainChannel();
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
    Channel getChannel(string title);
    void addChannel(Channel channel);
    void addChannel(string title);
    void removeChannel(string title);
    void changeActiveChannel(string title);
    Channel getActiveChannel();
    vector<string> getActiveChannelMessages(int number);
    void addMessageToChannel(string channel_title, string msg);
};

#endif