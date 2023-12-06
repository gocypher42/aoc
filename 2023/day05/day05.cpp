// Advent of Code 2023
// Day05: If You Give A Seed A Fertilizer
// https://adventofcode.com/2023/day/5

#include "string_list.h"
#include "string_utils.h"
#include <iostream>
#include <map>
#include <string>

namespace fs = std::filesystem;

using og::StringList;
using std::string;
using std::vector;
using std::map;

static constexpr const char *file_name = "input.txt";

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

struct Rule
{
  std::size_t source_start;
  std::size_t destination_start;
  std::size_t lenght;
};

struct GardeningMap
{
  [[nodiscard]] std::size_t apply_rules(std::size_t source) const;
  vector<Rule> rules;
};

std::size_t GardeningMap::apply_rules(const std::size_t source) const
{
  for (const Rule &rule : rules) {
    const std::size_t source_min = rule.source_start;
    const std::size_t source_max = source_min + rule.lenght - 1;
    if (source >= source_min && source <= source_max) {
      return rule.destination_start + source - rule.source_start;
    }
  }
  return source;
}

void parse_and_add_rules(const string &transformation_line, GardeningMap &map)
{
  vector<uint32_t> numbers;
  for (const string &number_str : og::split(transformation_line, " ")) {
    numbers.push_back(std::stoul(number_str));
  }
  map.rules.push_back(Rule{ numbers.at(1), numbers.at(0), numbers.at(2) });
}

void parse_rules(const StringList &lines, int &index, GardeningMap &map)
{
  index++;
  while (!lines.at(index).empty()) {
    parse_and_add_rules(lines.at(index), map);
    index++;
    if (index == lines.size()) { break; }
  }
}

string first_part(const StringList &lines)
{
  vector<std::size_t> seeds;
  for (const string &seed_str :
    og::split(og::split(lines.at(0), ": ").at(1), " ")) {
    seeds.push_back(std::stoul(seed_str));
  }

  GardeningMap seed_to_soil;
  GardeningMap soil_to_fertilizer;
  GardeningMap fertilizer_to_water;
  GardeningMap water_to_light;
  GardeningMap light_to_temperature;
  GardeningMap temperature_to_humidity;
  GardeningMap humidity_to_location;

  for (int i = 2; i < lines.size(); i++) {
    const string &line = lines.at(i);
    if (line.find("seed-to-soil") != std::string::npos) {
      parse_rules(lines, i, seed_to_soil);
      continue;
    }
    if (line.find("soil-to-fertilizer") != std::string::npos) {
      parse_rules(lines, i, soil_to_fertilizer);
      continue;
    }
    if (line.find("fertilizer-to-water") != std::string::npos) {
      parse_rules(lines, i, fertilizer_to_water);
      continue;
    }
    if (line.find("water-to-light") != std::string::npos) {
      parse_rules(lines, i, water_to_light);
      continue;
    }
    if (line.find("light-to-temperature") != std::string::npos) {
      parse_rules(lines, i, light_to_temperature);
      continue;
    }
    if (line.find("temperature-to-humidity") != std::string::npos) {
      parse_rules(lines, i, temperature_to_humidity);
      continue;
    }
    if (line.find("humidity-to-location") != std::string::npos) {
      parse_rules(lines, i, humidity_to_location);
      continue;
    }
  }

  int min = -1;
  for (std::size_t seed : seeds) {
    uint32_t soil = seed_to_soil.apply_rules(seed);
    uint32_t fertiliser = soil_to_fertilizer.apply_rules(soil);
    uint32_t water = fertilizer_to_water.apply_rules(fertiliser);
    uint32_t light = water_to_light.apply_rules(water);
    uint32_t temperature = light_to_temperature.apply_rules(light);
    uint32_t humitidy = temperature_to_humidity.apply_rules(temperature);
    uint32_t location = humidity_to_location.apply_rules(humitidy);
    if (min == -1) {
      min = (int)location;
      continue;
    }
    if (location < min) { min = (int)location; }
  }

  return std::to_string(min);
}

struct SeedRange
{
  std::size_t start{ 0 };
  std::size_t lenght{ 0 };
};

string second_part(const StringList &lines)
{
  vector<SeedRange> seed_ranges;
  const StringList seeds_str =
    og::split(og::split(lines.at(0), ": ").at(1), " ");
  seeds_str.print_lines();
  for (int i = 0; i < seeds_str.size(); i++) {
    SeedRange seed_range;
    seed_range.start = std::stoul(seeds_str.at(i));
    i++;
    seed_range.lenght = std::stoul(seeds_str.at(i));
    seed_ranges.push_back(seed_range);
  }

  GardeningMap seed_to_soil;
  GardeningMap soil_to_fertilizer;
  GardeningMap fertilizer_to_water;
  GardeningMap water_to_light;
  GardeningMap light_to_temperature;
  GardeningMap temperature_to_humidity;
  GardeningMap humidity_to_location;

  for (int i = 2; i < lines.size(); i++) {
    const string &line = lines.at(i);
    if (line.find("seed-to-soil") != std::string::npos) {
      parse_rules(lines, i, seed_to_soil);
      continue;
    }
    if (line.find("soil-to-fertilizer") != std::string::npos) {
      parse_rules(lines, i, soil_to_fertilizer);
      continue;
    }
    if (line.find("fertilizer-to-water") != std::string::npos) {
      parse_rules(lines, i, fertilizer_to_water);
      continue;
    }
    if (line.find("water-to-light") != std::string::npos) {
      parse_rules(lines, i, water_to_light);
      continue;
    }
    if (line.find("light-to-temperature") != std::string::npos) {
      parse_rules(lines, i, light_to_temperature);
      continue;
    }
    if (line.find("temperature-to-humidity") != std::string::npos) {
      parse_rules(lines, i, temperature_to_humidity);
      continue;
    }
    if (line.find("humidity-to-location") != std::string::npos) {
      parse_rules(lines, i, humidity_to_location);
      continue;
    }
  }

  int min = -1;
  for (const SeedRange &seed_range : seed_ranges) {
    for (std::size_t i = seed_range.start;
         i < seed_range.start + seed_range.lenght;
         i++) {
      uint32_t soil = seed_to_soil.apply_rules(i);
      uint32_t fertiliser = soil_to_fertilizer.apply_rules(soil);
      uint32_t water = fertilizer_to_water.apply_rules(fertiliser);
      uint32_t light = water_to_light.apply_rules(water);
      uint32_t temperature = light_to_temperature.apply_rules(light);
      uint32_t humitidy = temperature_to_humidity.apply_rules(temperature);
      uint32_t location = humidity_to_location.apply_rules(humitidy);
      if (min == -1) {
        min = (int)location;
        continue;
      }
      if (location < min) { min = (int)location; }
    }
    std::cout << "Seed: " << seed_range.start << " Done" << std::endl;
  }

  return std::to_string(min);
}
