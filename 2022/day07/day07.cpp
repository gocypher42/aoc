#include "string_list.h"
#include "string_utils.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using std::shared_ptr;
using og::StringList;

static constexpr const char *file_name = "input.txt";
static constexpr const char *correct_first_part_answer = "1501149";
static constexpr const char *correct_second_part_answer = "10096985";

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

class File
{
public:
  File() = default;

  void print(const int level) const;

  std::size_t m_size = 0;
  string m_name;
};

void File::print(const int level) const
{
  std::cout << std::string(level, '\t') << "- " << m_name
            << " (file, size=" << m_size << ")" << std::endl;
}

class Directory
{
public:
  explicit Directory(string name) : m_name(std::move(name)) {}

  [[nodiscard]] shared_ptr<Directory> find_dir(const string &name) const;
  void print_tree(const int level = 0) const;
  void update_size();
  vector<shared_ptr<Directory>> get_exceeding_size_dir(const std::size_t limit);

  string m_name;
  vector<shared_ptr<File>> m_files;
  vector<shared_ptr<Directory>> m_directories;
  shared_ptr<Directory> m_parent;
  std::size_t m_size = 0;
};

shared_ptr<Directory> Directory::find_dir(const string &name) const
{
  for (const auto &dir : m_directories) {
    if (!dir) { continue; }
    if (dir->m_name == name) { return dir; }
  }
  return nullptr;
}

void Directory::print_tree(const int level) const
{
  std::cout << std::string(level, '\t') << "- " << m_name
            << " (dir, size=" << m_size << ")" << std::endl;
  for (const auto &file : m_files) {
    if (file) { file->print(level + 1); }
  }
  for (const auto &dir : m_directories) {
    if (dir) { dir->print_tree(level + 1); }
  }
}

void Directory::update_size()
{
  m_size = 0;
  for (const auto &dir : m_directories) {
    if (dir) {
      dir->update_size();
      m_size += dir->m_size;
    }
  }
  for (const auto &file : m_files) {
    if (file) { m_size += file->m_size; }
  }
}

vector<shared_ptr<Directory>> Directory::get_exceeding_size_dir(
  const std::size_t limit)
{
  vector<shared_ptr<Directory>> dir_list;
  for (const auto &dir : m_directories) {
    if (!dir) { continue; }
    if (dir->m_size < limit) { dir_list.push_back(dir); }
    vector<shared_ptr<Directory>> child_exceeding_dir =
      dir->get_exceeding_size_dir(limit);

    dir_list.insert(
      dir_list.end(), child_exceeding_dir.begin(), child_exceeding_dir.end());
  }

  return dir_list;
}


void process_cd_command(const shared_ptr<Directory> &root,
  shared_ptr<Directory> &current_dir,
  const string &command)
{

  StringList split_cmd = og::split(command, " ");
  const string &to_dir = split_cmd.at(2);
  if (to_dir == "/") {
    current_dir = root;
  } else if (to_dir == "..") {
    if (current_dir->m_parent) { current_dir = current_dir->m_parent; }
  } else {
    const shared_ptr<Directory> child_dir = current_dir->find_dir(to_dir);
    if (child_dir) { current_dir = child_dir; }
  }
}

shared_ptr<Directory> make_tree(const StringList &commands)
{
  auto root = std::make_shared<Directory>("/");
  auto current_dir = root;

  for (std::size_t i = 0; i < commands.size(); i++) {
    const string &line = commands.at(i);

    if (line.substr(0, 4) == "$ cd") {
      process_cd_command(root, current_dir, line);

    } else if (line.substr(0, 4) == "$ ls") {
      while (i + 1 < commands.size() && commands.at(i + 1).at(0) != '$') {
        const string &item = commands.at(i + 1);
        StringList properties = og::split(item, " ");
        if (properties.at(0) == "dir") {
          auto dir = std::make_shared<Directory>(properties.at(1));
          dir->m_parent = current_dir;
          current_dir->m_directories.push_back(dir);
        } else {
          auto file = std::make_shared<File>();
          file->m_size = std::stoll(properties.at(0));
          file->m_name = properties.at(1);
          current_dir->m_files.push_back(file);
        }
        i++;
      }
    }
  }

  root->update_size();
  return root;
}

string first_part(const StringList &lines)
{
  shared_ptr<Directory> root = make_tree(lines);

  constexpr std::size_t limit_size = 100000;
  vector<shared_ptr<Directory>> exceeding_dirs =
    root->get_exceeding_size_dir(limit_size);

  std::size_t sum = 0;
  for (const auto &dir : exceeding_dirs) {
    if (!dir) { continue; }
    sum += dir->m_size;
  }

  return std::to_string(sum);
}

string second_part(const StringList &lines)
{
  shared_ptr<Directory> root = make_tree(lines);

  constexpr std::size_t total_space = 70000000;
  constexpr std::size_t space_needed_for_update = 30000000;
  const std::size_t total_unused_space = total_space - root->m_size;
  const std::size_t size_to_free = space_needed_for_update - total_unused_space;

  vector<shared_ptr<Directory>> all_dirs =
    root->get_exceeding_size_dir(root->m_size + 1);
  all_dirs.insert(all_dirs.begin(), root);
  std::sort(all_dirs.begin(),
    all_dirs.end(),
    [](const shared_ptr<Directory> &dir1, const shared_ptr<Directory> &dir2) {
      return dir1->m_size < dir2->m_size;
    });

  for (const auto &dir : all_dirs) {
    if (!dir) { continue; }
    if (dir->m_size > size_to_free) { return std::to_string(dir->m_size); }
  }

  return "0";
}
