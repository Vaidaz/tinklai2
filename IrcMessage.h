#ifndef IRC_MESSAGE_H
#define IRC_MESSAGE_H

#include <iostream>
#include <vector>
using namespace std;
#include "./StringUtils.h"

class IrcMessage {
  private:
    string message;
    string prefix;
    string command;
    string nick;
    string user;
    string host;
    vector<string> params;
    vector<string> splitBySpaces(string message);
    string cutUntillNewLine(string message);
  public:
    IrcMessage();
    IrcMessage(string msg);
    void setMessage(string message);
    string getMessage();
    string getPrefix();
    string getCommand();
    string getNick();
    vector<string> getParams();
    void parse();
    string getParmsString();
    ~IrcMessage();
};

#endif
