#include "../../utils/utils.h"
#include <iostream>

namespace fs = std::filesystem;

static constexpr const char *file_name = "input.txt";

std::string first_part(const Lines &lines);
std::string second_part(const Lines &lines);

int main()
{
  Lines lines = read_file(fs::path(file_name));

  std::string first_part_ans = first_part(lines);
  std::cout << "First part answer: " << first_part_ans << std::endl;

  std::string second_part_ans = second_part(lines);
  std::cout << "Second part answer: " << second_part_ans << std::endl;

  return 0;
}

std::string first_part(const Lines &lines) { return "0"; }

std::string second_part(const Lines &lines) { return "0"; }
