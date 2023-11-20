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

}
