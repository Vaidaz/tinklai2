#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>
#include <string.h>
#include <iostream>
using namespace std;

#define CHAT_WINDOW_ROWS_SIZE 30
#define INPUT_WINDOW_ROWS_SIZE 8
#define COLUMNS_SIZE 140

class Screen {
  private:
    WINDOW* chat_window_box;
    WINDOW* input_window_box;
    WINDOW* chat_window;
    WINDOW* input_window;
    string input_window_content;
  public:
    Screen();
    ~Screen();
    void draw();
    void printToChat(string str);
    void printToInput(string str);
    char inputGetCh();
    string getInputWindowContent();
    void clearInputWindowContent();
    void printUserMessage(string nick, string msg);
    string popInputWindowContent();
};

#endif