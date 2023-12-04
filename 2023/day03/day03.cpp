#include "string_list.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "540025";
static constexpr const char *correct_second_part_answer = "84584891";

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
  constexpr uint64_t ZERO = 0;
  constexpr uint64_t NINE = 9;
  const int char_value = token - '0';
  return char_value >= ZERO && char_value <= NINE;
}

struct NumberLocation
{
  NumberLocation() = default;

  uint64_t line_number = 0;
  uint64_t start_position = 0;
  uint64_t lenght = 0;
  uint64_t number = 0;
};


vector<NumberLocation> find_number_locations(const StringList &lines)
{
  vector<NumberLocation> locations;
  for (int i = 0; i < lines.size(); i++) {
    const string &line = lines.at(i);
    for (int j = 0; j < line.size(); j++) {
      const char &letter = line.at(j);
      if (!is_digit(letter)) { continue; }
      for (int k = j; k < line.size(); k++) {
        if (!is_digit(line.at(k)) || k + 1 >= line.size()) {
          NumberLocation location;
          location.line_number = i;
          location.start_position = j;
          location.lenght = k - j;
          location.number = std::stoi(lines.at(i).substr(j, k - j + 1));

          locations.push_back(location);
          j = k;
          break;
        }
      }
    }
  }

  return locations;
}

string first_part(const StringList &lines)
{
  const vector<NumberLocation> locations = find_number_locations(lines);
  uint64_t sum = 0;
  for (const NumberLocation &location : locations) {
    bool is_part_number = false;

    const int top_left =
      std::max(0, static_cast<int>(location.line_number - 1));
    const int bottom_left = std::min(static_cast<int>(location.line_number + 2),
      static_cast<int>(lines.size()));

    for (int i = top_left; i < bottom_left; i++) {
      const int start_position =
        std::max(0, static_cast<int>(location.start_position - 1));
      const uint64_t lenght =
        location.lenght + (location.start_position == 0 ? 1 : 2);
      const string &segment = lines.at(i).substr(start_position, lenght);
      for (const char &token : segment) {
        if (!is_digit(token) && token != '.') {
          is_part_number = true;
          break;
        }
      }

      if (is_part_number) {
        sum += location.number;
        break;
      }
    }
  }

  return std::to_string(sum);
}

struct Position
{
  Position() = default;

  size_t x = 0;
  size_t y = 0;
};

struct NumberAndGear
{
  NumberAndGear() = default;

  size_t number = 0;
  Position gear_position;
};

vector<NumberAndGear> find_numbers_and_their_gear(const StringList &lines)
{
  const vector<NumberLocation> locations = find_number_locations(lines);
  vector<NumberAndGear> numbers_and_their_gear;
  for (const NumberLocation &location : locations) {
    bool is_attach_to_a_gear = false;

    const int top_left =
      std::max(0, static_cast<int>(location.line_number - 1));
    const int bottom_left = std::min(static_cast<int>(location.line_number + 2),
      static_cast<int>(lines.size()));

    for (int i = top_left; i < bottom_left; i++) {
      const int start_position =
        std::max(0, static_cast<int>(location.start_position - 1));
      const uint64_t lenght =
        location.lenght + (location.start_position == 0 ? 1 : 2);
      const string segment = lines.at(i).substr(start_position, lenght);

      for (int j = start_position; j < start_position + lenght; j++) {
        const char &token = lines.at(i).at(j);
        if (token == '*') {
          is_attach_to_a_gear = true;
          Position pos;
          pos.x = j;
          pos.y = i;
          NumberAndGear gear_part;
          gear_part.number = location.number;
          gear_part.gear_position = pos;
          numbers_and_their_gear.push_back(gear_part);

          break;
        }
      }

      if (is_attach_to_a_gear) { break; }
    }
  }

  return numbers_and_their_gear;
}

struct GearRatio
{
  Position gear_position;
  size_t gear1 = 0;
  size_t gear2 = 0;
};

string second_part(const StringList &lines)
{
  const vector<NumberAndGear> numbers_and_their_gear =
    find_numbers_and_their_gear(lines);

  vector<GearRatio> gear_ratios;

  for (const auto &gear : numbers_and_their_gear) {
    int position = -1;
    for (auto &ratio : gear_ratios) {
      if (ratio.gear_position.x == gear.gear_position.x
          && ratio.gear_position.y == gear.gear_position.y) {
        position = &ratio - &gear_ratios[0];
        break;
      }
    }
    if (position == -1) {
      GearRatio ratio;
      ratio.gear_position = gear.gear_position;
      ratio.gear1 = gear.number;
      gear_ratios.push_back(ratio);
      continue;
    }

    if (position >= 0) { gear_ratios.at(position).gear2 = gear.number; }
  }

  int sum = 0;
  for (auto &ratio : gear_ratios) {
    if (ratio.gear1 == 0 || ratio.gear2 == 0) { continue; }
    sum += (int)(ratio.gear1 * ratio.gear2);
  }


  return std::to_string(sum);
}
