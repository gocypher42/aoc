#include "string_list.h"
#include <iostream>
#include <string>
#include <cassert>

using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "Not the right ans";
static constexpr const char *correct_second_part_answer = "Not the right ans";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  const og::StringList lines((fs::path(file_name)));

  const string first_part_answer = first_part(lines);
  std::cout << "First part answer: " << first_part_answer << std::endl;

  const string second_part_answer = second_part(lines);
  std::cout << "Second part answer: " << second_part_answer << std::endl;

  assert(first_part_answer == correct_first_part_answer);
  assert(second_part_answer == correct_second_part_answer);

  return 0;
}

string first_part(const StringList &lines)
{
  lines.print_lines();
  int sum = 0;
  for (const string& line: lines){
    int first_number = 0;
    int last_number = 0;
    
    for (char i : line){
      const int char_value = i - '0';
      if (char_value >=0 && char_value <= 9){
        first_number = char_value;
      }
    }

    for (int i =line.size()-1 ; i >=0; i--){
      const int char_value = line.at(i) - '0';
      if (char_value >=0 && char_value <= 9){
        last_number = char_value;
      }
    }


    std::cout << last_number << first_number << std::endl;
    string str_value;
    str_value.append(std::to_string(last_number)).append(std::to_string(first_number));
    sum += std::stoi(str_value);
  }
  return std::to_string(sum);
}

string second_part(const StringList &lines)
{
  return "0";
}
