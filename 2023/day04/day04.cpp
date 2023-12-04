#include "string_list.h"
#include "string_utils.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "Not the right ans";
static constexpr const char *correct_second_part_answer = "Not the right ans";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  const StringList lines((fs::path(file_name)));

  const string first_part_answer = first_part(lines);
  std::cout << "First part answer: " << first_part_answer << '\n';

  const string second_part_answer = second_part(lines);
  std::cout << "Second part answer: " << second_part_answer << '\n';

  assert(first_part_answer == correct_first_part_answer);
  assert(second_part_answer == correct_second_part_answer);

  return 0;
}

class Card final
{
public:
  explicit Card(uint64_t index) : m_id(index) {}

  void print() const
  {
    printf("Card id: %ld\n", m_id);
    printf("\tNumbers: ");
    for (auto number : m_numbers) { printf("%ld ", number); }
    printf("\n");
    printf("\tWinning numbers: ");
    for (auto number : m_winning_numbers) { printf("%ld ", number); }
    printf("\n");
  }

  uint64_t m_id;
  vector<uint64_t> m_numbers;
  vector<uint64_t> m_winning_numbers;
};

string first_part(const StringList &lines)
{
  vector<Card> cards;
  lines.print_lines();
  for (const string &line : lines) {
    const StringList title_and_numbers = og::split(line, ": ");
    const uint64_t card_id =
      std::stoll(og::split(title_and_numbers.at(0), " ").at(1));
    const StringList numbers_and_winnings =
      og::split(title_and_numbers.at(1), " | ");

    StringList card_numbers_str = og::split(numbers_and_winnings.at(0), " ");
    card_numbers_str.trim_lines();
    card_numbers_str.remove_empty_lines();

    StringList winning_numbers_str = og::split(numbers_and_winnings.at(1), " ");
    winning_numbers_str.remove_empty_lines();
    winning_numbers_str.trim_lines();

    Card card(card_id);

    for (const string &number : card_numbers_str) {
      card.m_numbers.push_back(std::stoll(number));
    }

    for (const string &number : winning_numbers_str) {
      card.m_winning_numbers.push_back(std::stoll(number));
    }
    std::sort(card.m_numbers.begin(), card.m_numbers.end());
    std::sort(card.m_winning_numbers.begin(), card.m_winning_numbers.end());
    card.print();
    cards.push_back(card);
  }


  return "0";
}

string second_part(const StringList &lines)
{
  // lines.print_lines();
  return "0";
}
