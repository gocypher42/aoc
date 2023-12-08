// Advent of Code 2023
// Day07: Camel Cards
// https://adventofcode.com/2023/day/7

#include "string_list.h"
#include "string_utils.h"
#include <algorithm>
#include <array>
#include <iostream>

namespace fs = std::filesystem;

using og::StringList;
using std::string;
using std::vector;

static constexpr const char *file_name = "input.txt";
static constexpr const size_t FIVE = 5;
static constexpr const size_t FOURTEEN = 14;

string first_part(const StringList &lines);
string second_part(const StringList &lines);

int main()
{
  const StringList lines((fs::path(file_name)));

  const string ans_part_1 = first_part(lines);
  std::cout << "First part answer: " << ans_part_1 << '\n';

  const string ans_part_2 = second_part(lines);
  std::cout << "Second part answer: " << ans_part_2 << '\n';

  return 0;
}


constexpr std::array<char, FOURTEEN> card_strengths_part_1 = {
  'A',
  'K',
  'Q',
  'J',
  'T',
  '9',
  '8',
  '7',
  '6',
  '5',
  '4',
  '3',
  '2',
  '1',
};

constexpr std::array<char, FOURTEEN> card_strengths_part_2 = {
  'A',
  'K',
  'Q',
  'T',
  '9',
  '8',
  '7',
  '6',
  '5',
  '4',
  '3',
  '2',
  '1',
  'J',
};

enum class HandType : size_t {
  Highcard = 0,
  OnePair = 1,
  TwoPair = 2,
  ThreeOfAKind = 3,
  FullHouse = 4,
  FourOfAKind = 5,
  FiveOfAKind = 6,
};

struct Hand
{
  std::array<char, FIVE> cards = { '\0', '\0', '\0', '\0', '\0' };
  std::size_t bid = 0;
  HandType hand_type = HandType::Highcard;
};

bool is_five_of_a_kind_part_1(const Hand &hand)
{
  const char must_match_card = hand.cards.at(0);
  return std::all_of(hand.cards.cbegin(),
    hand.cards.cend(),
    [must_match_card](char card) { return card == must_match_card; });
};

bool is_four_of_a_kind_part_1(const Hand &hand)
{
  const auto &cards = hand.cards;
  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j)) { count++; }
    }
    if (count == 4) { return true; }
  }
  return false;
};

bool is_full_house_part_1(const Hand &hand)
{
  const auto &cards = hand.cards;
  vector<char> cards_found;
  for (char card : cards) {
    bool found = false;

    for (char card_found : cards_found) {
      if (card == card_found) {
        found = true;
        break;
      }
    }
    if (!found) { cards_found.push_back(card); }
  }
  return cards_found.size() == 2;
}

bool is_three_of_a_kind_part_1(const Hand &hand)
{
  const auto &cards = hand.cards;
  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j)) { count++; }
    }
    if (count == 3) { return true; }
  }
  return false;
};

bool is_two_pair_part_1(const Hand &hand)
{
  std::array<char, 2> pairs = { '\0', '\0' };

  const auto &cards = hand.cards;

  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j)) { count++; }
    }
    if (count == 2 && pairs.at(0) != cards.at(i)
        && pairs.at(1) != cards.at(i)) {
      if (pairs.at(0) == '\0') {
        pairs.at(0) = cards.at(i);
      } else {
        pairs.at(1) = cards.at(i);
      }
    }
  }

  return pairs.at(0) != '\0' && pairs.at(1) != '\0';
}

bool is_one_pair_part_1(const Hand &hand)
{

  const auto &cards = hand.cards;
  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j)) { count++; }
    }
    if (count == 2) { return true; }
  }

  return false;
}

bool compare_hands_part_1(const Hand &l_hand, const Hand &r_hand)
{
  if (l_hand.hand_type != r_hand.hand_type) {
    return l_hand.hand_type < r_hand.hand_type;
  }
  for (size_t i = 0; i < l_hand.cards.size(); i++) {
    if (l_hand.cards.at(i) == r_hand.cards.at(i)) { continue; }
    const auto &l_card = std::find(card_strengths_part_1.cbegin(),
      card_strengths_part_1.cend(),
      l_hand.cards.at(i));
    const size_t l_pos = l_card - card_strengths_part_1.cbegin();
    const auto &r_card = std::find(card_strengths_part_1.cbegin(),
      card_strengths_part_1.cend(),
      r_hand.cards.at(i));
    const size_t r_pos = r_card - card_strengths_part_1.cbegin();
    return l_pos > r_pos;
  }
  return false;
}

string first_part(const StringList &lines)
{
  vector<Hand> hands;
  for (const string &line : lines) {
    const StringList split = og::split(line, " ");
    Hand hand;

    for (int i = 0; i < split.at(0).size(); i++) {
      hand.cards.at(i) = split.at(0).at(i);
    }
    hand.bid = std::stoull(split.at(1));
    hands.push_back(hand);
  }

  for (Hand &hand : hands) {
    if (is_five_of_a_kind_part_1(hand)) {
      hand.hand_type = HandType::FiveOfAKind;
    } else if (is_four_of_a_kind_part_1(hand)) {
      hand.hand_type = HandType::FourOfAKind;
    } else if (is_full_house_part_1(hand)) {
      hand.hand_type = HandType::FullHouse;
    } else if (is_three_of_a_kind_part_1(hand)) {
      hand.hand_type = HandType::ThreeOfAKind;
    } else if (is_two_pair_part_1(hand)) {
      hand.hand_type = HandType::TwoPair;
    } else if (is_one_pair_part_1(hand)) {
      hand.hand_type = HandType::OnePair;
    } else {
      hand.hand_type = HandType::Highcard;
    }
  }

  std::sort(hands.begin(), hands.end(), compare_hands_part_1);
  size_t sum = 0;
  for (size_t i = 0; i < hands.size(); i++) {
    const Hand &hand = hands.at(i);
    for (char card : hand.cards) { std::cout << card; }
    std::cout << " " << hand.bid << " " << (size_t)hand.hand_type << "\n";

    sum += hand.bid * (i + 1);
  }
  return std::to_string(sum);
}

bool is_five_of_a_kind_part_2(const Hand &hand)
{
  char must_match_card = '\0';
  for (char card : hand.cards) {
    if (card != 'J') {
      must_match_card = card;
      break;
    }
  }
  return std::all_of(
    hand.cards.cbegin(), hand.cards.cend(), [must_match_card](char card) {
      return card == must_match_card || card == 'J';
    });
};

bool is_four_of_a_kind_part_2(const Hand &hand)
{
  const auto &cards = hand.cards;
  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j) || cards.at(j) == 'J') { count++; }
    }
    if (count == 4) { return true; }
  }
  return false;
};

bool is_full_house_part_2(const Hand &hand)
{
  const auto &cards = hand.cards;
  vector<char> cards_found;
  for (char card : cards) {
    if (card == 'J') { continue; }
    bool found = false;

    for (char card_found : cards_found) {
      if (card == card_found) {
        found = true;
        break;
      }
    }
    if (!found) { cards_found.push_back(card); }
  }
  return cards_found.size() == 2;
}

bool is_three_of_a_kind_part_2(const Hand &hand)
{
  const auto &cards = hand.cards;
  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j) || cards.at(j) == 'J') { count++; }
    }
    if (count == 3) { return true; }
  }
  return false;
};

// AJAT3

bool is_two_pair_part_2(const Hand &hand)
{
  std::array<char, 2> pairs = { '\0', '\0' };

  const auto &cards = hand.cards;
  size_t number_of_jokers = 0;

  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    if (cards.at(i) == 'J') {
      number_of_jokers++;
      continue;
    }
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j)) { count++; }
    }
    if (count == 2 && pairs.at(0) != cards.at(i)
        && pairs.at(1) != cards.at(i)) {
      if (pairs.at(0) == '\0') {
        pairs.at(0) = cards.at(i);
      } else {
        pairs.at(1) = cards.at(i);
      }
    }
  }


  return (pairs.at(0) != '\0' && pairs.at(1) != '\0')
         || (pairs.at(0) != '\0' && number_of_jokers == 1)
         || number_of_jokers >= 2;
}

bool is_one_pair_part_2(const Hand &hand)
{

  const auto &cards = hand.cards;
  for (size_t i = 0; i < cards.size(); i++) {
    size_t count = 1;
    for (size_t j = 0; j < cards.size(); j++) {
      if (i == j) { continue; }
      if (cards.at(i) == cards.at(j) || cards.at(j) == 'J') { count++; }
    }
    if (count == 2) { return true; }
  }

  return false;
}

bool compare_hands_part_2(const Hand &l_hand, const Hand &r_hand)
{
  if (l_hand.hand_type != r_hand.hand_type) {
    return l_hand.hand_type < r_hand.hand_type;
  }
  for (size_t i = 0; i < l_hand.cards.size(); i++) {
    if (l_hand.cards.at(i) == r_hand.cards.at(i)) { continue; }
    const auto &l_card = std::find(card_strengths_part_2.cbegin(),
      card_strengths_part_2.cend(),
      l_hand.cards.at(i));
    const size_t l_pos = l_card - card_strengths_part_2.cbegin();
    const auto &r_card = std::find(card_strengths_part_2.cbegin(),
      card_strengths_part_2.cend(),
      r_hand.cards.at(i));
    const size_t r_pos = r_card - card_strengths_part_2.cbegin();
    return l_pos > r_pos;
  }
  return false;
}

string second_part(const StringList &lines)
{
  vector<Hand> hands;
  for (const string &line : lines) {
    const StringList split = og::split(line, " ");
    Hand hand;

    for (int i = 0; i < split.at(0).size(); i++) {
      hand.cards.at(i) = split.at(0).at(i);
    }
    hand.bid = std::stoull(split.at(1));
    hands.push_back(hand);
  }

  for (Hand &hand : hands) {
    if (is_five_of_a_kind_part_2(hand)) {
      hand.hand_type = HandType::FiveOfAKind;
    } else if (is_four_of_a_kind_part_2(hand)) {
      hand.hand_type = HandType::FourOfAKind;
    } else if (is_full_house_part_2(hand)) {
      hand.hand_type = HandType::FullHouse;
    } else if (is_three_of_a_kind_part_2(hand)) {
      hand.hand_type = HandType::ThreeOfAKind;
    } else if (is_two_pair_part_2(hand)) {
      hand.hand_type = HandType::TwoPair;
    } else if (is_one_pair_part_2(hand)) {
      hand.hand_type = HandType::OnePair;
    } else {
      hand.hand_type = HandType::Highcard;
    }
  }

  std::sort(hands.begin(), hands.end(), compare_hands_part_2);
  size_t sum = 0;
  for (size_t i = 0; i < hands.size(); i++) {
    const Hand &hand = hands.at(i);
    for (char card : hand.cards) { std::cout << card; }
    std::cout << " " << hand.bid << " " << (size_t)hand.hand_type << "\n";

    sum += hand.bid * (i + 1);
  }
  return std::to_string(sum);
}
