#include <iostream>
#include <unistd.h>

#include "./Socket.h"
#include "./StdioHelper.h"
#include "./IrcMessage.h"
#include "./Screen.h"
#include "./User.h"
#include "./Irc.h"

using namespace std;

void setUserInformation(User *user);

int main(int argc, char* argv[]){
  // Validate arguments
  if(argc != 3){
    cout << "Error: invalid usage" << endl;
    cout << "Example: " << argv[0] << " host port" << endl;
    return 1;
  }

  string host(argv[1]);
  string port(argv[2]);

  User user;
  setUserInformation(&user);

  Socket sock(host, port);
  sock.connectToServer();

  Irc irc;
  irc.setSocket(&sock);
  irc.setUser(&user);
  irc.registerUser();

  // Remove
  irc.join("#test");

  IrcMessage irc_message;

  Screen screen;
  string msg;

  for(;;){
    if(irc.isMessage()){
      irc_message = irc.receiveIrcMessage();

      if(irc_message.getCommand() == "PRIVMSG"){
        screen.printUserMessage(irc_message.getNick(), irc_message.getParams()[1]);
      }
    }

    if(StdioHelper::isInput()){
      if(screen.inputGetCh() == '\n'){
        msg = screen.popInputWindowContent();
        screen.printUserMessage(user.getNick(), msg);
        irc.privateMessage("#test", msg);
      }
    }

    usleep(100000);
  }

  return 0;
}

void setUserInformation(User *user){
  string str;
  cout << "Jūsų nick: ";
  getline(cin, str);
  user->setNick(str);
  cout << "Jūsų tikrasis vardas: ";
  getline(cin, str);
  user->setRealName(str);
}
