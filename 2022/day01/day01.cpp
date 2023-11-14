#include "../../utils/utils.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static constexpr const char *file_name = "input.txt";

void first_part(const Lines &lines);
void second_part(const Lines &lines);

int main()
{
  Lines lines = read_file(fs::path(file_name));
  first_part(lines);
  second_part(lines);

  return 0;
}

void first_part(const Lines &lines)
{
  std::vector<size_t> elfs;

  uint64_t sum = 0;
  for (const auto &line : lines) {
    if (line.empty()) {
      elfs.push_back(sum);
      sum = 0;
      continue;
    }

    sum += std::stol(line);
  }

  std::cout << "First part answer: "
            << *std::max_element(elfs.cbegin(), elfs.cend()) << std::endl;
}

void second_part(const Lines &lines)
{
  std::vector<size_t> elfs;

  uint64_t sum = 0;
  for (const auto &line : lines) {
    if (line.empty()) {
      elfs.push_back(sum);
      sum = 0;
      continue;
    }

    sum += std::stol(line);
  }

  uint64_t sum_top_3 = 0;

  for (int i = 0; i < 3; i++) {
    auto max_element = std::max_element(elfs.cbegin(), elfs.cend());
    if (max_element == elfs.end()) { continue; }

    sum_top_3 += *max_element;
    elfs.erase(max_element);
  }

  std::cout << "Second part answer: " << sum_top_3 << std::endl;
}
