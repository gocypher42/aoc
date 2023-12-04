#include "string_list.h"
#include "string_utils.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>

using std::accumulate;
using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "20117";
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
    StringList title_split = og::split(title_and_numbers.at(0), " ");
    title_split.remove_empty_lines();

    const uint64_t card_id = std::stoull(title_split.at(1));
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

  vector<uint64_t> cards_point;
  for (const auto &card : cards) {
    uint64_t points = 0;
    for (const uint64_t &card_number : card.m_numbers) {
      for (const uint64_t &winning_number : card.m_winning_numbers) {
        if (card_number == winning_number) {
          if (points == 0U) {
            points = 1;
          } else {
            points *= 2;
          }
          break;
        }
      }
    }
    cards_point.push_back(points);
  }

  return std::to_string(
    accumulate(cards_point.cbegin(), cards_point.cend(), (uint64_t)0));
}

string second_part(const StringList &lines)
{
  // lines.print_lines();
  return "0";
}
