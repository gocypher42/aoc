#include "string_utils.h"
#include <algorithm>
#include <locale>

namespace og {

string &ltrim(string &line)
{
  auto iterator = std::find_if(line.begin(), line.end(), [](char character) {
    return !std::isspace<char>(character, std::locale::classic());
  });
  line.erase(line.begin(), iterator);
  return line;
}

string &rtrim(string &line)
{
  auto iterator = std::find_if(line.rbegin(), line.rend(), [](char character) {
    return !std::isspace<char>(character, std::locale::classic());
  });
  line.erase(iterator.base(), line.end());
  return line;
}

StringList split(string line, const string &delimiter)
{
  StringList split_string;
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != std::string::npos) {
    split_string.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  split_string.push_back(line);
  return split_string;
}

}// namespace og
