#pragma once

#include "string_list.h"
#include <string>
#include <vector>

using std::string;

namespace og {

string &ltrim(string &line);
string &rtrim(string &line);
StringList split(string line, const string& delimiter);
  
}
