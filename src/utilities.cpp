#include "utilities.hpp"

#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> word_parse(std::vector<std::string> tmp_string) {
    std::vector<std::string> parse_string;
    for (auto& word : tmp_string) {
        std::string new_str;
        for (auto& ch : word) {
            if (isalpha(ch))
                new_str.push_back(ch);
        }
        parse_string.emplace_back(new_str);
    }
    return parse_string;
}

std::vector<std::string> split(const std::string& str, const std::string& delim) {
    std::vector<std::string> res;
    if ("" == str)
        return res;

    char* strs = new char[str.length() + 1];
    strcpy(strs, str.c_str());

    char* d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char* p = strtok(strs, d);
    while (p) {
        std::string s = p;
        res.push_back(s);
        p = strtok(NULL, d);
    }

    delete[] d;
    delete[] strs;
    return res;
}

std::string lower_str(const std::string& str) {
    std::string new_str;
    for (auto& c : str)
        new_str.push_back(tolower(c));
    return new_str;
}
