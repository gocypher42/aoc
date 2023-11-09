#include "utils.h"
#include <fmt/core.h>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
  std::vector<std::string> lines = read_file("input.txt");
  fmt::print("Hello {}\n", "World");
  return 0;
}
