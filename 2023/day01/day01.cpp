#include "string_list.h"
#include <iostream>
#include <string>
#include <cassert>

using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "54940";
static constexpr const char *correct_second_part_answer = "54208";

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
  int sum = 0;
  for (const string& line: lines){
    int first_number = 0;
    int last_number = 0;
    
    for (char i : line){
      const int char_value = i - '0';
      if (char_value >=0 && char_value <= 9){
        first_number = char_value;
        break;
      }
    }

    for (int i =line.size()-1 ; i >=0; i--){
      const int char_value = line.at(i) - '0';
      if (char_value >=0 && char_value <= 9){
        last_number = char_value;
        break;
      }
    }
    const string str_value (std::to_string(first_number) + std::to_string(last_number));
    sum += std::stoi(str_value);
  }
  return std::to_string(sum);
}

bool is_digit(char token){
  const int char_value = token- '0';
  if (char_value >=0 && char_value <= 9){
    return true;
  }

  return false;
}

int to_digit(const string& token)
{
  if (token.find("one") != std::string::npos)
  {
    return 1;
  }
  if (token.find("two") != std::string::npos)
  {
    return 2;
  }
  if (token.find("three") != std::string::npos)
  {
    return 3;
  }
  if (token.find("four") != std::string::npos)
  {
    return 4;
  }
  if (token.find("five") != std::string::npos)
  {
    return 5;
  }
  if (token.find("six") != std::string::npos)
  {
    return 6;
  }
  if (token.find("seven") != std::string::npos)
  {
    return 7;
  }
  if (token.find("eight") != std::string::npos)
  {
    return 8;
  }
  if (token.find("nine") != std::string::npos)
  {
    return 9;
  }
  return 0;
}

string second_part(const StringList &lines)
{
  int sum = 0;
  for (const string& line: lines){
    int first_number = 0;
    int last_number = 0;

    
    for (int i = 0; i < line.size() ; i++){
      if (is_digit(line.at(i))){
        first_number = line.at(i) - '0';
        break;
      }

      const int value = to_digit(line.substr(0, i+1));
      if (value != 0){
        first_number = value;
        break;
      }
    }

    for (int i = line.size() -1; i >=0 ; i--){
      if (is_digit(line.at(i))){
        last_number = line.at(i) - '0';
        break;
      }

      const int value = to_digit(line.substr(i, line.size()-i));
      if (value != 0){
        last_number = value;
        break;
      }
     }

    const string str_value (std::to_string(first_number) + std::to_string(last_number));
    sum += std::stoi(str_value);
  }
  return std::to_string(sum);
}
