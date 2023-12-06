// Advent of Code 2023
// DayXX: [TITLE]
// https://adventofcode.com/2023/day/XX

#include "string_list.h"
#include "string_utils.h"
#include <iostream>

namespace fs = std::filesystem;

using og::StringList;
using std::string;

static constexpr const char *file_name = "input.txt";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  const StringList lines((fs::path(file_name)));

  const string ans_part_1 = first_part(lines);
  std::cout << "First part answer: " << ans_part_1 << '\n';
  
  const string ans_part_2 = second_part(lines);
  std::cout << "Second part answer: " << ans_part_2 << '\n';

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
