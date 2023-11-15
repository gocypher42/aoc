#include "../../utils/utils.h"
#include <iostream>

namespace fs = std::filesystem;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "Not the right ans";
static constexpr const char *correct_second_part_answer = "Not the right ans";

std::string first_part(const Lines &lines);
std::string second_part(const Lines &lines);

int main()
{
  Lines lines = read_file(fs::path(file_name));

  std::string first_part_answer = first_part(lines);
  std::cout << "First part answer: " << first_part_answer << std::endl;

  std::string second_part_answer = second_part(lines);
  std::cout << "Second part answer: " << second_part_answer << std::endl;

  // assert(first_part_answer == correct_first_part_answer);
  // assert(second_part_answer == correct_second_part_answer);

  return 0;
}

std::string first_part(const Lines &lines)
{
  print_lines(lines);
  return "0";
}

std::string second_part(const Lines &lines)
{
  print_lines(lines);
  return "0";
}
