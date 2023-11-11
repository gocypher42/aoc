#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

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
  auto empty_lines = std::find_if(
    lines.begin(), lines.end(), [](std::string &line) { return line.empty(); });
  lines.erase(lines.begin(), empty_lines);
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
