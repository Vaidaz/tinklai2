#ifndef IRC_H
#define IRC_H

#include "./Socket.h"
#include "./User.h"
#include "./IrcMessage.h"
#include <iostream>
using namespace std;

class Irc{
  private:
    Socket *socket;
    User *user;
    void sendMessage(string msg);
  public:
    Irc();
    void setSocket(Socket *socket);
    void setUser(User *user);
    int isMessage();
    IrcMessage receiveIrcMessage();
    void registerUser();
    void join(string str);
    void privateMessage(string params, string msg);
    void parseAndExecute(string msg);
    void changeChannel(string title);
    void receiveAndExecuteMessage();
    ~Irc();
};

#endif