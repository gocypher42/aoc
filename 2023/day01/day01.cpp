#include "../../utils/utils.h"

namespace fs = std::filesystem;

static constexpr const char *file_name = "input.txt";

void first_part(const Lines &lines) {}

void second_part(const Lines &lines) {}

int main()
{
  Lines lines = read_file(fs::path(file_name));
  first_part(lines);
  second_part(lines);
  return 0;
}
