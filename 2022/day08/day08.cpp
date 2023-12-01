#include "string_list.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using og::StringList;
using std::size_t;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "1715";
static constexpr const char *correct_second_part_answer = "Not the right ans";

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

class TreeMap
{
public:
  explicit TreeMap(const StringList &lines)
  {
    for (const string &line : lines) {
      vector<int> row;
      for (const char &item : line) { row.push_back(item - '0'); }

      map.push_back(row);
      visibility.emplace_back(row.size(), false);
    }
  }

  void print_map() const
  {
    for (const auto &row : map) {
      for (const int item : row) { std::cout << item << " "; }
      std::cout << std::endl;
    }
  }

  void print_visibility() const
  {
    for (const auto &row : visibility) {
      for (const auto item : row) { std::cout << item << " "; }
      std::cout << std::endl;
    }
  }

  [[nodiscard]] std::size_t get_visible_trees() const
  {
    std::size_t sum = 0;
    for (const auto &row : visibility) {

      for (const auto &item : row) {
        if (item) { sum++; }
      }
    }
    return sum;
  }


  vector<vector<int>> map;
  vector<vector<bool>> visibility;
};

void look_from_top(TreeMap &map)
{
  const vector<vector<int>> &trees = map.map;

  for (int i = 0; i < trees.at(0).size(); i++) {
    int max_height = -1;
    for (int j = 0; j < trees.size(); j++) {
      if (trees.at(j).at(i) > max_height) {
        map.visibility.at(j).at(i) = true;
        max_height = trees.at(j).at(i);
      }
    }
  }
}

void look_from_bottom(TreeMap &map)
{
  const vector<vector<int>> &trees = map.map;

  for (std::size_t i = trees.at(0).size(); i > 0; i--) {
    int max_height = -1;
    const std::size_t i_id = i - 1;
    for (std::size_t j = trees.size(); j > 0; j--) {
      const std::size_t j_id = j - 1;
      if (trees.at(j_id).at(i_id) > max_height) {
        map.visibility.at(j_id).at(i_id) = true;
        max_height = trees.at(j_id).at(i_id);
      }
    }
  }
}

void look_from_left(TreeMap &map)
{
  const vector<vector<int>> &trees = map.map;

  for (int i = 0; i < trees.at(0).size(); i++) {
    int max_height = -1;
    for (int j = 0; j < trees.size(); j++) {
      if (trees.at(i).at(j) > max_height) {
        map.visibility.at(i).at(j) = true;
        max_height = trees.at(i).at(j);
      }
    }
  }
}

void look_from_right(TreeMap &map)
{
  const vector<vector<int>> &trees = map.map;

  for (std::size_t i = trees.at(0).size(); i > 0; i--) {
    int max_height = -1;
    const std::size_t i_id = i - 1;
    for (std::size_t j = trees.size(); j > 0; j--) {
      const std::size_t j_id = j - 1;
      if (trees.at(i_id).at(j_id) > max_height) {
        map.visibility.at(i_id).at(j_id) = true;
        max_height = trees.at(i_id).at(j_id);
      }
    }
  }
}

void look_from_all_direction(TreeMap &map)
{
  look_from_top(map);
  look_from_bottom(map);
  look_from_left(map);
  look_from_right(map);
}


string first_part(const StringList &lines)
{
  TreeMap map(lines);
  look_from_all_direction(map);
  return std::to_string(map.get_visible_trees());
}

string second_part(const StringList &lines)
{
  lines.print_lines();

  for (size_t i = 0; i < lines.size(); i++) {
    const string &line = lines.at(i);
    for (size_t j = 0; j < line.size(); j++) {



    }
  }

  return "0";
}
