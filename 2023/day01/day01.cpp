// Advent of Code 2023
// Day01: Trebuchet?!
// https://adventofcode.com/2023/day/1

#include "string_list.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

namespace fs = std::filesystem;

using og::StringList;
using std::string;
using std::vector;

static constexpr const char *file_name = "input.txt";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  const og::StringList lines((fs::path(file_name)));

  std::cout << "First part answer: " << first_part(lines) << std::endl;
  std::cout << "Second part answer: " << second_part(lines) << std::endl;

  return 0;
}

constexpr uint32_t ZERO = 0;
constexpr uint32_t NINE = 9;
constexpr uint32_t TEN = 10;

bool is_digit(char token)
{
  const int char_value = token - '0';
  return char_value >= ZERO && char_value <= NINE;
}

int to_digit(char token)
{
  if (is_digit(token)) { return token - '0'; }
  return -1;
}

string first_part(const StringList &lines)
{
  vector<int> calibrations;
  for (const string &line : lines) {
    vector<int> numbers;

    for (char token : line) {
      if (is_digit(token)) { numbers.push_back(to_digit(token)); }
    }

    calibrations.push_back(numbers.front() * (int)TEN + numbers.back());
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

    calibrations.push_back(first_number * (int)TEN + last_number);
  }
  return std::to_string(
    std::accumulate(calibrations.cbegin(), calibrations.cend(), 0));
}
