#include "string_list.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using std::tuple;
using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "595";
static constexpr const char *correct_second_part_answer = "952";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  StringList lines((fs::path(file_name)));

  string first_part_answer = first_part(lines);
  std::cout << "First part answer: " << first_part_answer << std::endl;

  string second_part_answer = second_part(lines);
  std::cout << "Second part answer: " << second_part_answer << std::endl;

  assert(first_part_answer == correct_first_part_answer);
  assert(second_part_answer == correct_second_part_answer);

  return 0;
}

tuple<string, string> split(const string &line, const char delimiter)
{
  const std::size_t split_id = line.find(delimiter);
  const string list1 = line.substr(0, split_id);
  const string list2 = line.substr(split_id + 1, line.length());
  return { list1, list2 };
}

tuple<int, int> split_to_int(const string &line, const char delimiter)
{
  const auto [list1, list2] = split(line, delimiter);
  return { std::stol(list1), std::stol(list2) };
}


string first_part(const StringList &lines)
{
  std::size_t count = 0;
  std::for_each(
    lines.cbegin(), lines.cend(), [&count](const std::string &line) {
      const auto [list1, list2] = split(line, ',');
      const auto [start_list1, end_list1] = split_to_int(list1, '-');
      const auto [start_list2, end_list2] = split_to_int(list2, '-');

      if ((start_list1 >= start_list2 && end_list1 <= end_list2)
          || (start_list1 <= start_list2 && end_list1 >= end_list2)) {
        count++;
      }
    });
  return std::to_string(count);
}

string second_part(const StringList &lines)
{
  std::size_t count = 0;
  std::for_each(
    lines.cbegin(), lines.cend(), [&count](const std::string &line) {
      const auto [list1, list2] = split(line, ',');
      const auto [start_list1, end_list1] = split_to_int(list1, '-');
      const auto [start_list2, end_list2] = split_to_int(list2, '-');

      if ((start_list1 <= start_list2 && end_list1 >= start_list2)
          || (start_list2 <= start_list1 && end_list2 >= start_list1)) {
        count++;
      }
    });
  return std::to_string(count);
}
