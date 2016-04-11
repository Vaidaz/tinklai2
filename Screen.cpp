#include "./Screen.h"

Screen::Screen(){
  initscr();
  curs_set(0);

  this->chat_window_box = newwin(CHAT_WINDOW_ROWS_SIZE, COLUMNS_SIZE, 1, 1);
  this->input_window_box = newwin(INPUT_WINDOW_ROWS_SIZE, COLUMNS_SIZE, CHAT_WINDOW_ROWS_SIZE + 1, 1);

  box(this->chat_window_box, 0, 0);
  box(this->input_window_box, 0, 0);

  this->chat_window = newwin(CHAT_WINDOW_ROWS_SIZE - 2, COLUMNS_SIZE - 2, 2, 2);
  this->input_window = newwin(INPUT_WINDOW_ROWS_SIZE - 2, COLUMNS_SIZE - 2, CHAT_WINDOW_ROWS_SIZE + 2, 2);

  refresh();
  wrefresh(this->chat_window_box);
  wrefresh(this->input_window_box);
  wrefresh(this->chat_window);
  wrefresh(this->input_window);
};

Screen::~Screen(){
  delwin(this->chat_window_box);
  delwin(this->input_window_box);
  delwin(this->chat_window);
  delwin(this->input_window);
  endwin();
};

void Screen::printToChat(string str){
  wprintw(this->chat_window, "%s", str.c_str());
  wrefresh(this->chat_window);
};

void Screen::printToInput(string str){
  wprintw(this->input_window, "%s", str.c_str());
  wrefresh(this->input_window);
};

char Screen::inputGetCh(){
  char ch = wgetch(this->input_window);
  if(ch != '\n'){
    this->input_window_content += ch;
    wrefresh(this->input_window);
  }
  return ch;
}

string Screen::getInputWindowContent(){
  return this->input_window_content;
}

void Screen::clearInputWindowContent(){
  this->input_window_content = "";
  werase(this->input_window);
  wrefresh(this->input_window);
}

void Screen::printUserMessage(string nick, string msg){
  printToChat(nick + ": " + msg + "\n");
};

string Screen::popInputWindowContent(){
  string content;
  content = getInputWindowContent();
  clearInputWindowContent();
  return content;
};
