// Advent of Code 2023
// DayXX: [TITLE]
// https://adventofcode.com/2023/day/XX

#include "string_list.h"
#include "string_utils.h"
#include <iostream>
#include <string>

namespace fs = std::filesystem;

using og::StringList;
using std::string;

static constexpr const char *file_name = "input.txt";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  const StringList lines((fs::path(file_name)));

  std::cout << "First part answer: " << first_part(lines) << '\n';
  std::cout << "Second part answer: " << second_part(lines) << '\n';

  return 0;
}

string first_part(const StringList &lines)
{
  lines.print_lines();
  return "0";
}

string second_part(const StringList &lines)
{
  // lines.print_lines();
  return "0";
}
