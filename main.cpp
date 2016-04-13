#include <iostream>
#include <unistd.h>

#include "./Socket.h"
#include "./StdioHelper.h"
#include "./IrcMessage.h"
#include "./Screen.h"
#include "./User.h"
#include "./Irc.h"

#define LINES_PER_CHAT_WINDOW 27

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
  // irc.parseAndExecute("/join #test\n");
  // irc.changeChannel("#test");
  // irc.join("#test");

  Screen screen;
  string msg;

  for(;;){
    // receive input from server
    if(irc.isMessage()){
      irc.receiveAndExecuteMessage();
    }

    // check std input
    if(StdioHelper::isInput()){
      if(screen.inputGetCh() == '\n'){
        msg = screen.popInputWindowContent();
        irc.parseAndExecute(msg);
      }
    }

    // print current channel
    screen.clearChatWindow();
    vector<string> active_channel_messages = user.getActiveChannelMessages(28);
    for(int i = 0; i < active_channel_messages.size(); i++){
      screen.printToChat(active_channel_messages[i]);
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
