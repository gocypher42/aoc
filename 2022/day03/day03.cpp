#include "../../utils/utils.h"
#include <algorithm>
#include <iostream>
#include <cassert>

namespace fs = std::filesystem;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "8298";
static constexpr const char *correct_second_part_answer = "2708";

std::string first_part(const Lines &lines);
std::string second_part(const Lines &lines);

int main()
{
  Lines lines = read_file(fs::path(file_name));

  std::string first_part_answer = first_part(lines);
  std::cout << "First part answer: " << first_part_answer << std::endl;

  std::string second_part_answer = second_part(lines);
  std::cout << "Second part answer: " << second_part_answer << std::endl;

  assert(first_part_answer == correct_first_part_answer);
  assert(second_part_answer == correct_second_part_answer);

  return 0;
}

std::string overlap(const std::string &str1, const std::string &str2)
{
  std::string chars;
  for (const char char1 : str1) {
    for (const char char2 : str2) {
      if (char1 == char2) { chars.push_back(char1); }
    }
  }
  return chars;
}

std::string first_part(const Lines &lines)
{
  int sum = 0;
  std::for_each(lines.cbegin(), lines.cend(), [&sum](const std::string &line) {
    uint64_t bag_size = line.size() / 2;
    std::string bag1 = line.substr(0, bag_size);
    std::string bag2 = line.substr(bag_size, line.size());

    const char duplicate = overlap(bag1, bag2).at(0);
    sum += duplicate > 96 ? duplicate - 96 : duplicate - 38;
  });
  return std::to_string(sum);
}

std::string second_part(const Lines &lines)
{
  using std::vector;

  vector<Lines> groups;

  for (size_t i = 0; i < lines.size(); i += 3) {
    Lines group;
    for (size_t j = 0; j < 3; j++) { group.push_back(lines[i + j]); }
    groups.push_back(group);
  }

  int sum = 0;

  std::for_each(groups.cbegin(), groups.cend(), [&sum](const auto &group) {
    const std::string &bag1 = group[0];
    const std::string &bag2 = group[1];
    const std::string &bag3 = group[2];

    const char token = overlap(overlap(bag1, bag2), bag3).at(0);
    sum += token > 96 ? token - 96 : token - 38;
  });

  return std::to_string(sum);
}
