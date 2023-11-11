#include "../utils/utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs  = std::filesystem;

static constexpr const char * file_name = "input.txt";

int main(int argc, char *argv[])
{
  Lines lines = read_file(fs::path(file_name));
  for (const std::string& line : lines){
    std::cout << line << std::endl;
  }
  return 0;
}
