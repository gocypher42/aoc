#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

Lines read_file(const fs::path &file_path)
{
  std::ifstream file_handle(file_path);
  if (!file_handle.is_open()) {
    throw std::invalid_argument(std::string("Invalid file ").append(file_path));
  }

  Lines lines;
  std::string line;
  while (std::getline(file_handle, line)) { lines.push_back(line); }
  file_handle.close();
  return lines;
}

Lines &remove_empty_lines(Lines &lines)
{
  std::vector<std::size_t> id_to_remove;
  for (std::size_t i = 0; i < lines.size(); i++) {
    if (lines[i].empty()) {
      lines.erase(lines.begin() + static_cast<int>(i));
      i--;
    }
  }
  return lines;
}

Lines &trim(Lines &lines)
{
  std::for_each(
    lines.begin(), lines.end(), [](std::string &line) { ltrim(rtrim(line)); });
  return lines;
}

std::string &ltrim(std::string &line)
{
  auto iterator = std::find_if(line.begin(), line.end(), [](char character) {
    return !std::isspace<char>(character, std::locale::classic());
  });
  line.erase(line.begin(), iterator);
  return line;
}

std::string &rtrim(std::string &line)
{
  auto iterator = std::find_if(line.rbegin(), line.rend(), [](char character) {
    return !std::isspace<char>(character, std::locale::classic());
  });
  line.erase(iterator.base(), line.end());
  return line;
}

void print_lines(const Lines &lines)
{
  std::for_each(lines.cbegin(), lines.cend(), [](const std::string &line) {
    std::cout << "'" << line << "'" << std::endl;
  });
}
