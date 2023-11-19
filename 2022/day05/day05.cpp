#include "../../utils/utils.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using std::string;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "RNZLFZSJH";
static constexpr const char *correct_second_part_answer = "CNSFCGJSM";

string first_part(const Lines &lines);
string second_part(const Lines &lines);

int main()
{
  const Lines lines = read_file(fs::path(file_name));

  const string first_part_answer = first_part(lines);
  std::cout << "First part answer: " << first_part_answer << std::endl;

  std::cout << std::endl;

  const string second_part_answer = second_part(lines);
  std::cout << "Second part answer: " << second_part_answer << std::endl;

  assert(first_part_answer == correct_first_part_answer);
  assert(second_part_answer == correct_second_part_answer);

  return 0;
}

void print_stack(size_t index, std::stack<char> stack)
{
  std::cout << index << ": ";

  while (!stack.empty()) {
    std::cout << stack.top() << ", ";
    stack.pop();
  }

  std::cout << std::endl;
}

void print_stacks(const std::map<size_t, std::stack<char>> &stacks)
{
  for (const auto &item : stacks) { print_stack(item.first, item.second); }
}

std::vector<string> split(string input_string, const string &delimiter)
{
  std::vector<string> split_string;
  size_t pos = 0;
  while ((pos = input_string.find(delimiter)) != std::string::npos) {
    split_string.push_back(input_string.substr(0, pos));
    input_string.erase(0, pos + delimiter.length());
  }
  split_string.push_back(input_string);
  return split_string;
}

struct Move
{
  Move() = default;

  std::size_t crates_qty_to_move = 0;
  std::size_t id_from = 0;
  std::size_t id_to = 0;

  void print() const
  {
    std::cout << "Move " << crates_qty_to_move << " crates from " << id_from
              << " to " << id_to << std::endl;
  }
};

void print_moves(const std::vector<Move> &moves)
{
  for (const auto &move : moves) { move.print(); }
}

void apply_moves_first_part(std::map<size_t, std::stack<char>> &stacks,
  const std::vector<Move> &moves)
{
  if (moves.empty()) { return; }
  std::cout << "Init state" << std::endl;
  print_stacks(stacks);
  for (const auto &move : moves) {
    move.print();
    for (size_t i = 0; i < move.crates_qty_to_move; i++) {
      if (stacks[move.id_from].empty()) { break; }
      stacks[move.id_to].push(stacks[move.id_from].top());
      stacks[move.id_from].pop();
    }
    print_stacks(stacks);
  }
}

void apply_moves_second_part(std::map<size_t, std::stack<char>> &stacks,
  const std::vector<Move> &moves)
{
  if (moves.empty()) { return; }
  std::cout << "Init state" << std::endl;
  print_stacks(stacks);

  for (const auto &move : moves) {
    move.print();
    std::stack<char> temp_stack;
    for (size_t i = 0; i < move.crates_qty_to_move; i++) {
      if (stacks[move.id_from].empty()) { break; }
      temp_stack.push(stacks[move.id_from].top());
      stacks[move.id_from].pop();
    }

    while(!temp_stack.empty()){
      stacks[move.id_to].push(temp_stack.top());
      temp_stack.pop();
    }
    print_stacks(stacks);
  }
}


string first_part(const Lines &lines)
{
  const auto seperator_for_crates = std::find_if(lines.cbegin(),
    lines.cend(),
    [](const auto &item) { return item.at(1) == '1'; });

  const Lines stack_lines(lines.cbegin(),
    lines.cbegin() + 1 + (seperator_for_crates - lines.cbegin()));

  const Lines move_lines(
    lines.cbegin() + 2 + (seperator_for_crates - lines.cbegin()), lines.cend());

  // print_lines(stack_lines);

  const string &stack_numbers_line = stack_lines.back();

  std::map<size_t, std::stack<char>> stacks;

  for (std::size_t i = 0; i < stack_numbers_line.size(); i++) {
    if (stack_numbers_line.at(i) == ' ') { continue; }

    std::stack<char> stack;

    for (int j = static_cast<int>(stack_lines.size()) - 2; j >= 0; j--) {
      const char crate = stack_lines.at(j).at(i);
      if (stack_lines.at(j).at(i) == ' ') { break; }
      stack.push(crate);
    }

    const int crate_id = std::stoi(string() += stack_numbers_line.at(i));

    stacks.insert(std::pair<size_t, std::stack<char>>(crate_id, stack));
  }

  // print_lines(move_lines);

  print_stacks(stacks);

  std::vector<Move> moves;

  for (const auto &move_line : move_lines) {
    const auto split_line = split(move_line, " ");
    Move move;
    move.crates_qty_to_move = std::stoi(split_line.at(1));
    move.id_from = std::stoi(split_line.at(3));
    move.id_to = std::stoi(split_line.at(5));
    moves.push_back(move);
  }

  print_moves(moves);

  apply_moves_first_part(stacks, moves);

  string answer;

  for (const auto &stack : stacks) { answer += stack.second.top(); }

  return answer;
}

string second_part(const Lines &lines)
{
  const auto seperator_for_crates = std::find_if(lines.cbegin(),
    lines.cend(),
    [](const auto &item) { return item.at(1) == '1'; });

  const Lines stack_lines(lines.cbegin(),
    lines.cbegin() + 1 + (seperator_for_crates - lines.cbegin()));

  const Lines move_lines(
    lines.cbegin() + 2 + (seperator_for_crates - lines.cbegin()), lines.cend());

  // print_lines(stack_lines);

  const string &stack_numbers_line = stack_lines.back();

  std::map<size_t, std::stack<char>> stacks;

  for (std::size_t i = 0; i < stack_numbers_line.size(); i++) {
    if (stack_numbers_line.at(i) == ' ') { continue; }

    std::stack<char> stack;

    for (int j = static_cast<int>(stack_lines.size()) - 2; j >= 0; j--) {
      const char crate = stack_lines.at(j).at(i);
      if (stack_lines.at(j).at(i) == ' ') { break; }
      stack.push(crate);
    }

    const int crate_id = std::stoi(string() += stack_numbers_line.at(i));

    stacks.insert(std::pair<size_t, std::stack<char>>(crate_id, stack));
  }

  // print_lines(move_lines);

  print_stacks(stacks);

  std::vector<Move> moves;

  for (const auto &move_line : move_lines) {
    const auto split_line = split(move_line, " ");
    Move move;
    move.crates_qty_to_move = std::stoi(split_line.at(1));
    move.id_from = std::stoi(split_line.at(3));
    move.id_to = std::stoi(split_line.at(5));
    moves.push_back(move);
  }

  print_moves(moves);

  apply_moves_second_part(stacks, moves);

  string answer;

  for (const auto &stack : stacks) { answer += stack.second.top(); }

  return answer;
}
