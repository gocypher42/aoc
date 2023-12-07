// Advent of Code 2023
// Day02: Cube Conundrum
// https://adventofcode.com/2023/day/2

#include "string_list.h"
#include "string_utils.h"
#include <cassert>
#include <iostream>
#include <string>

using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "2776";
static constexpr const char *correct_second_part_answer = "68638";

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

struct Game
{
  Game() = default;

  uint64_t id = 0;
  uint64_t reg_cube = 0;
  uint64_t blue_cube = 0;
  uint64_t green_cube = 0;
};

void print(const Game &game)
{
  std::cout << "Game id: " << game.id << std::endl
            << "\tRed: " << game.reg_cube << std::endl
            << "\tGreen: " << game.green_cube << std::endl
            << "\tBlue: " << game.blue_cube << std::endl;
}

constexpr uint64_t MAX_RED_CUBE = 12;
constexpr uint64_t MAX_BLUE_CUBE = 14;
constexpr uint64_t MAX_GREEN_CUBE = 13;

vector<Game> parse_games(const StringList &lines)
{
  vector<Game> games;
  for (const string &line : lines) {
    const StringList game_and_rounds = og::split(line, ": ");
    const StringList rounds = og::split(game_and_rounds.at(1), "; ");

    Game game;
    game.id = std::stoi(og::split(game_and_rounds.at(0), " ").at(1));

    for (const string &round : rounds) {
      const StringList cubes = og::split(round, ", ");
      for (const string &cube : cubes) {
        const StringList count_and_color = og::split(cube, " ");
        const uint64_t count = std::stoll(count_and_color.at(0));
        const string &color = count_and_color.at(1);

        if (color == "red") {
          if (count > game.reg_cube) { game.reg_cube = count; }
          continue;
        }
        if (color == "blue") {
          if (count > game.blue_cube) { game.blue_cube = count; }
          continue;
        }
        if (color == "green") {
          if (count > game.green_cube) { game.green_cube = count; }
          continue;
        }
      }
    }
    games.push_back(game);
  }
  return games;
}

string first_part(const StringList &lines)
{
  const vector<Game> games = parse_games(lines);
  uint64_t sum = 0;
  for (const Game &game : games) {
    if (game.reg_cube <= MAX_RED_CUBE && game.blue_cube <= MAX_BLUE_CUBE
        && game.green_cube <= MAX_GREEN_CUBE) {
      sum += game.id;
    }
  }
  return std::to_string(sum);
}

string second_part(const StringList &lines)
{
  const vector<Game> games = parse_games(lines);
  uint64_t sum = 0;
  for (const Game &game : games) {
    sum += game.reg_cube * game.blue_cube * game.green_cube;
  }
  return std::to_string(sum);
}
