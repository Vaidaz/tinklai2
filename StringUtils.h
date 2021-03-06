#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

namespace StringUtils {
  vector<string> splitBySpaces(string str);
  vector<string> splitByComma(string str);
  string removeCrLf(string str);
  string cutUntillNewLine(string str);
};

#endif