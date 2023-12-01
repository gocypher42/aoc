#include "string_list.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>

using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "54940";
static constexpr const char *correct_second_part_answer = "54208";

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

bool is_digit(char token)
{
  const int char_value = token - '0';
  if (char_value >= 0 && char_value <= 9) { return true; }

  return false;
}

int to_digit(char token)
{
  const int token_value = token - '0';
  if (token_value >= 0 && token_value <= 9) { return token_value; }
  return 0;
}

string first_part(const StringList &lines)
{
  vector<int> calibrations;
  for (const string &line : lines) {
    vector<int> numbers;

    for (char token : line) {
      if (is_digit(token)) { numbers.push_back(to_digit(token)); }
    }

    calibrations.push_back(numbers.front() * 10 + numbers.back());
  }
  return std::to_string(
    std::accumulate(calibrations.cbegin(), calibrations.cend(), 0));
}


struct WordToInt
{
  std::string word;
  int value;
};

int to_digit(const string &token)
{
  const std::vector<WordToInt> map = {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 },
  };

  for (const auto &item : map) {
    if (token.find(item.word) != std::string::npos) { return item.value; }
  }
  return 0;
}

string second_part(const StringList &lines)
{
  vector<int> calibrations;
  for (const string &line : lines) {
    int first_number = 0;
    int last_number = 0;


    for (int i = 0; i < line.size(); i++) {
      if (is_digit(line.at(i))) {
        first_number = line.at(i) - '0';
        break;
      }

      const int value = to_digit(line.substr(0, i + 1));
      if (value != 0) {
        first_number = value;
        break;
      }
    }

    for (int i = line.size() - 1; i >= 0; i--) {
      if (is_digit(line.at(i))) {
        last_number = line.at(i) - '0';
        break;
      }

      const int value = to_digit(line.substr(i, line.size() - i));
      if (value != 0) {
        last_number = value;
        break;
      }
    }

    calibrations.push_back(first_number * 10 + last_number);
  }
  return std::to_string(
    std::accumulate(calibrations.cbegin(), calibrations.cend(), 0));
}
