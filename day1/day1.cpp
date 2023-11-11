#include "../utils/utils.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static constexpr const char *file_name = "input.txt";

int main(int argc, char *argv[])
{
  Lines lines = read_file(fs::path(file_name));
  std::vector<size_t> elfs;

  size_t sum = 0;
  for (const auto& line: lines){
    if (line.empty()){
      elfs.push_back(sum);
      sum = 0;
      continue;
    } 

    sum += std::stol(line);
  }

  std::cout << *std::max_element(elfs.cbegin(), elfs.cend()) << std::endl;

  return 0;
}
