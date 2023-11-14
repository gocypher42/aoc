#include "../utils/utils.h"
#include <algorithm>
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

std::string first_part(const Lines &lines)
{
  int sum = 0;
  std::for_each(lines.cbegin(), lines.cend(), [&sum](const std::string &line) {
    uint64_t bag_size = line.size() / 2;
    std::string bag1 = line.substr(0, bag_size);
    std::string bag2 = line.substr(bag_size, line.size());

    char duplicate = '\0';
    bool found = false;
    for (const char char1 : bag1) {
      for (const char char2 : bag2) {
        if (char1 == char2) {
          duplicate = char1;
          found = true;
          break;
        }
      }
      if (found) { break; }
    }

    const int value = duplicate > 96 ? duplicate - 96 : duplicate - 38;
    sum += value;
  });
  return std::to_string(sum);
}

std::string second_part(const Lines &lines) {

  for (size_t i = 0; i< lines.size(); i += 3){
    for(size_t j = 0; j < i; j++){
      std::cout << lines[j] << std::endl;
    }
    std::cout << std::endl;
  }

    // const int value = duplicate > 96 ? duplicate - 96 : duplicate - 38;
  return ""; }
