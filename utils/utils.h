#pragma once

#include <filesystem>
#include <string>
#include <vector>

using Lines = std::vector<std::string>;
namespace fs = std::filesystem;

Lines read_file(const fs::path &file_path);

Lines &remove_empty_lines(Lines& lines);
Lines &trim(Lines &lines);
std::string &ltrim(std::string &line);
std::string &rtrim(std::string &line);

void print_lines(const Lines& lines);


