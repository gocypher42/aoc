#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace og {

namespace fs = std::filesystem;

using std::string;
using std::vector;

class StringList : public vector<string>
{
public:
  StringList() = default;
  explicit StringList(const fs::path &file_path);
  explicit StringList(const vector<string> &list);

  void read_from_file(const fs::path &file_path);
  void remove_empty_lines();
  void trim_lines();
  void print_lines() const;
};

}// namespace og
