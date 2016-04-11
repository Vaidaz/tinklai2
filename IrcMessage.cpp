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

// Sena metodo versija
// void IrcMessage::parse(){
//   string
//     message = this->message,
//     prefix,
//     command,
//     param,
//     nick,
//     host,
//     user;

//   vector<string> params;

//   const int PREFIX_STAGE = 0;
//   const int COMMAND_STAGE = 1;
//   const int PARAMS_STAGE = 2;
//   int stage, param_index = 0;

//   stage = message[0] == ':' ? PREFIX_STAGE : COMMAND_STAGE;
//   int stop = 0;
//   for(int i = 0; i < message.length(); i++){
//     switch(stage){
//       case PREFIX_STAGE:{
//         if(message[i] == ' '){
//           stage = COMMAND_STAGE;
//         } else {
//           prefix += message[i];
//         }

//         break;
//       }
//       case COMMAND_STAGE:{
//         if(message[i] == ' '){
//           stage = PARAMS_STAGE;
//         } else {
//           command += message[i];
//         }
//         break;
//       }
//       case PARAMS_STAGE:{
//         if(message[i] == ':'){
//           param = message.substr(i + 1, message.find_first_of("\n", i+1) - i - 2);
//           params.push_back(param);
//           stop = 1;
//         } else if(1) {
//           if(message[i] == ' ' || message[i] == '\n'){
//             params.push_back(param);
//             param = "";
//           } else {
//             param += message[i];
//           }
//         }
//         break;
//       }
//     }

//     if(message[i] == '\n' || stop){
//       break;
//     }
//   }

//   // parsinamas prfiksas
//   const int NICK_STAGE = 3;
//   const int USER_STAGE = 4;
//   const int HOST_STAGE = 5;
//   for(int i = 0; i < prefix.length(); i++){
//     if(i == 0){
//       stage = NICK_STAGE;
//     } else if(message[i] == '!'){
//       stage = USER_STAGE;
//       continue;
//     } else if(message[i] == '@'){
//       stage = HOST_STAGE;
//       continue;
//     }

//     switch(stage){
//       case NICK_STAGE:{
//         if(message[i] == ':' && i == 0){
//           continue;
//         }
//         nick += message[i];
//         break;
//       }
//       case USER_STAGE:{
//         host += message[i];
//         break;
//       }
//       case HOST_STAGE:{
//         user += message[i];
//         break;
//       }
//     }
//   }

//   this->prefix = prefix;
//   this->command = command;
//   this->params = params;
//   this->nick = nick;
//   this->user = user;
//   this->host = host;
// };

void IrcMessage::parse(){
  string message = cutUntillNewLine(this->message);
  vector<string> words = splitBySpaces(message);

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

vector<string> IrcMessage::splitBySpaces(string message){
  string word;
  stringstream ss(message);

  vector<string> words;

  while (ss >> word){
    words.push_back(word);
  }

  return words;
};

string IrcMessage::cutUntillNewLine(string message){
  string msg;
  for(int i = 0; i < message.length() - 1; i++){
    if(message[i] == '\r' && message[i+1] == '\n'){
      break;
    }

    msg += message[i];
  }

  return msg;
};
