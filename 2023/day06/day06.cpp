// Advent of Code 2023
// Day06: Wait For It
// https://adventofcode.com/2023/day/6

#include "string_list.h"
#include "string_utils.h"
#include <cmath>
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
  const StringList lines((fs::path(file_name)));

  const string ans_part_1 = first_part(lines);
  std::cout << "First part answer: " << ans_part_1 << '\n';

  const string ans_part_2 = second_part(lines);
  std::cout << "Second part answer: " << ans_part_2 << '\n';

  return 0;
}

struct Race
{
  std::size_t time;
  std::size_t distance;
};

string first_part(const StringList &lines)
{
  StringList times_str = og::split(lines.at(0), ": ");
  times_str.erase(times_str.begin());
  times_str = og::split(times_str.at(0), " ");
  times_str.remove_empty_lines();

  StringList distances_str = og::split(lines.at(1), ": ");
  distances_str.erase(distances_str.begin());
  distances_str = og::split(distances_str.at(0), " ");
  distances_str.remove_empty_lines();

  vector<Race> races;
  for (std::size_t i = 0; i < distances_str.size(); i++) {
    races.emplace_back(
      Race{ std::stoull(times_str.at(i)), std::stoull(distances_str.at(i)) });
  }

  vector<std::size_t> ways_to_win;

  for (const auto &race : races) {
    const double div_factor = -2;
    const double numerator = -(int)race.time;
    const double numerator_sqrt =
      std::sqrt(std::pow(race.time, 2) + (-4 * -1 * -(int)race.distance));

    int lower_bound = std::ceil(((numerator + numerator_sqrt) / div_factor));
    if ((int)race.distance
        >= (-1 * std::pow(lower_bound, 2) + (int)race.time * lower_bound)) {
      lower_bound++;
    }
    int upper_bound = std::floor(((numerator - numerator_sqrt) / div_factor));
    if ((int)race.distance
        >= (-1 * std::pow(upper_bound, 2) + (int)race.time * upper_bound)) {
      upper_bound--;
    }
    ways_to_win.push_back(upper_bound - lower_bound + 1);
  }

  std::size_t acc = 1;
  for (auto ways : ways_to_win) { acc *= ways; }

  return std::to_string(acc);
}

string second_part(const StringList &lines)
{
  StringList times_str = og::split(lines.at(0), ": ");
  times_str.erase(times_str.begin());
  times_str = og::split(times_str.at(0), " ");
  times_str.remove_empty_lines();

  StringList distances_str = og::split(lines.at(1), ": ");
  distances_str.erase(distances_str.begin());
  distances_str = og::split(distances_str.at(0), " ");
  distances_str.remove_empty_lines();

  string time_str;
  string distance_str;
  for (std::size_t i = 0; i < distances_str.size(); i++) {
    time_str.append(times_str.at(i));
    distance_str.append(distances_str.at(i));
  }

  Race race{ std::stoull(time_str), std::stoull(distance_str) };

  const double div_factor = -2;
  const double numerator = -(int)race.time;
  const double numerator_sqrt =
    std::sqrt(std::pow(race.time, 2) + (-4 * -1 * -(int)race.distance));

  long lower_bound = std::ceil(((numerator + numerator_sqrt) / div_factor));

  while ((long)race.distance >= ((long)(-1 * std::pow(lower_bound, 2))
                                 + (long)race.time * lower_bound)) {
    lower_bound++;
  }

  long upper_bound = std::floor(((numerator - numerator_sqrt) / div_factor));

  while ((long)race.distance >= ((long)(-1 * std::pow(upper_bound, 2))
                                 + (long)race.time * upper_bound)) {
    upper_bound--;
  }

  return std::to_string(upper_bound - lower_bound + 1);
}
