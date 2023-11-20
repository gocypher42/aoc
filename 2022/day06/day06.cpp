#include "../../utils/string_list.h"
#include <array>
#include <cassert>
#include <iostream>
#include <string>

using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "1275";
static constexpr const char *correct_second_part_answer = "3605";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  const og::StringList lines((fs::path(file_name)));

  const string first_part_answer = first_part(lines);
  std::cout << "First part answer: " << first_part_answer << std::endl;

  const string second_part_answer = second_part(lines);
  std::cout << "Second part answer: " << second_part_answer << std::endl;

  assert(first_part_answer == correct_first_part_answer);
  assert(second_part_answer == correct_second_part_answer);

  return 0;
}

bool is_marker(const string &potential_marker)
{
  for (std::size_t i = 0; i < potential_marker.length(); i++) {
    for (std::size_t j = i+1; j < potential_marker.length(); j++) {
      if (potential_marker.at(i) == potential_marker.at(j)) { return false; }
    }
  }

  return true;
}

string first_part(const StringList &lines)
{
  const std::size_t marker_size = 4;
  const string &stream = lines.at(0);

  for (std::size_t i = 0; i < stream.length() - marker_size; i++) {
    if(is_marker(stream.substr(i, marker_size))){
      return std::to_string(i + marker_size);
    }
  }

  return "0";
}

string second_part(const StringList &lines)
{
  const std::size_t marker_size = 14;
  const string &stream = lines.at(0);

  for (std::size_t i = 0; i < stream.length() - marker_size; i++) {
    if(is_marker(stream.substr(i, marker_size))){
      return std::to_string(i + marker_size);
    }
  }

  return "0";
}
