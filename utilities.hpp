#ifndef UTILITIES
#define UTILITIES
#include <string>
#include <vector>

std::vector<std::string> word_parse(std::vector<std::string> tmp_string);
std::vector<std::string> split(const std::string& str, const std::string& delim);
std::vector<std::string> file_to_data(const std::string& filename);
std::string lower_str(const std::string& str);
#endif