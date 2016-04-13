#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include <iostream>
using namespace std;

class Channel{
  private:
    string title;
    vector<string> messages;
  public:
    Channel();
    void setTitle(string title);
    string getTitle();
    void addMessage(string message);
    vector<string> getMessages();
    ~Channel();
};

#endif