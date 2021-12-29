#include "utilities.hpp"

#include <cctype>
#include <cstring>
#include <filesystem>
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
    //先將要切割的字串從string型別轉換為char*型別
    char* strs = new char[str.length() + 1];  //不要忘了
    strcpy(strs, str.c_str());

    char* d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char* p = strtok(strs, d);
    while (p) {
        std::string s = p;  //分割得到的字串轉換為string型別
        res.push_back(s);   //存入結果陣列
        p = strtok(NULL, d);
    }

    return res;
}

std::vector<std::string> file_to_data(const std::string& filename) {
    std::ifstream file;
    std::vector<std::string> res;
    std::string str;
    file.open(filename, std::ios::in);
    while (std::getline(file, str)) {
        res.push_back(str);
    }
    file.close();
    return res;
}
std::string lower_str(const std::string& str) {
    std::string new_str;
    for (auto& c : str)
        new_str.push_back(tolower(c));
    return new_str;
}
