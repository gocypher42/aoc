#pragma once

#include <string>
#include <vector>
#include <filesystem>

std::vector<std::string> read_file(const std::filesystem::path& file_path);
