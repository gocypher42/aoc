#include "string_list.h"
#include "string_utils.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace og {

StringList::StringList(const fs::path &file_path) { read_from_file(file_path); }

StringList::StringList(const vector<string> &list)
{
  clear();
  for (const string &item : list) { emplace_back(item); }
}

void StringList::read_from_file(const fs::path &file_path)
{
  std::ifstream file_handle(file_path);
  if (!file_handle.is_open()) {
    throw std::invalid_argument(std::string("Invalid file ").append(file_path));
  }

  clear();

  std::string line;
  while (std::getline(file_handle, line)) { push_back(line); }
  file_handle.close();
}

void StringList::remove_empty_lines()
{
  for (std::size_t i = 0; i < size(); i++) {
    if (at(i).empty()) {
      erase(begin() + static_cast<int>(i));
      i--;
    }
  }
}

void StringList::trim_lines()
{
  for (string &line : *this) { ltrim(rtrim(line)); }
}

void StringList::print_lines() const
{
  for (const string &line : *this) {
    std::cout << "'" << line << "'" << std::endl;
  }
}
}// namespace og
