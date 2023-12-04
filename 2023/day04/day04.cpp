#include "string_list.h"
#include "string_utils.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>

namespace fs = std::filesystem;

using og::StringList;
using std::vector;
using std::string;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "20117";
static constexpr const char *correct_second_part_answer = "13768818";

string first_part(const StringList &lines);
string second_part(const StringList &lines);

class Card final
{
public:
  explicit Card(uint64_t index) : m_id(index) {}

  void print() const;

  uint64_t m_id;
  vector<uint64_t> m_numbers;
  vector<uint64_t> m_winning_numbers;
  uint64_t m_count{ 1 };
};

void Card::print() const
{
  std::cout << "Card id: " << m_id << "\n\tNumbers: ";
  for (auto number : m_numbers) { std::cout << number << "\n"; }
  std::cout << "\n\tWinning numbers: ";
  for (auto number : m_winning_numbers) { std::cout << number << "\n"; }
  std::cout << "\n\tCount: " << m_count << "\n";
}

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

vector<Card> parse_cards(const StringList &lines)
{
  vector<Card> cards;
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
    cards.push_back(card);
  }
  return cards;
}

string first_part(const StringList &lines)
{
  const vector<Card> cards = parse_cards(lines);

  vector<uint64_t> cards_point;
  for (const auto &card : cards) {
    uint64_t points = 0;
    for (const uint64_t &card_number : card.m_numbers) {
      for (const uint64_t &winning_number : card.m_winning_numbers) {
        if (card_number == winning_number) {
          if (points == (uint64_t)0) {
            points = 1;
            break;
          }
          points *= 2;
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
  vector<Card> cards = parse_cards(lines);

  for (const auto &card : cards) {
    uint64_t number_found = 0;
    for (const uint64_t &card_number : card.m_numbers) {
      for (const uint64_t &winning_number : card.m_winning_numbers) {
        if (card_number == winning_number) {
          number_found++;
          const auto winning_card = std::find_if(cards.begin(),
            cards.end(),
            [&card, &number_found](Card &other_card) {
              return card.m_id + number_found == other_card.m_id;
            });
          if (winning_card != cards.end()) {
            (*winning_card).m_count += card.m_count;
          }
          break;
        }
      }
    }
  }

  return std::to_string(std::accumulate(
    cards.cbegin(), cards.cend(), 0, [](uint64_t sum, const Card &card) {
      return sum += card.m_count;
    }));
}
