#include "search_tree.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "trie.hpp"
#include "utilities.hpp"

void search_tree::insert(const std::string& word, const int& index) {
    this->mytrie.insert(word, index);
}

std::list<int> search_tree::search(const std::vector<std::string>& query) {
    // Sequential
    int qsize = query.size();
    if (qsize == 0)
        return std::list<int>();
    std::list<int> search_result;
    std::list<int> answer;

    answer = this->mytrie.search(query[0]);
    for (int i = 1; i < qsize; i += 2) {
        search_result = this->mytrie.search(query[i + 1]);
        if (query[i] == "/") {
            auto it_search = search_result.begin();
            auto it_answer = answer.begin();
            while (it_answer != answer.end() && it_search != search_result.end()) {
                if (*it_answer < *it_search) {
                    ++it_answer;
                } else if (*it_answer == *it_search) {
                    ++it_answer;
                    ++it_search;
                } else {
                    answer.insert(it_answer, *it_search);
                    ++it_search;
                }
            }
            while (it_search != search_result.end()) {
                answer.insert(it_answer, *it_search);
                ++it_search;
            }
        } else {
            auto it_search = search_result.begin();
            auto it_answer = answer.begin();
            while (it_answer != answer.end() && it_search != search_result.end()) {
                if (*it_answer < *it_search) {
                    it_answer = answer.erase(it_answer);
                } else if (*it_answer == *it_search) {
                    ++it_answer;
                    ++it_search;
                } else {
                    ++it_search;
                }
            }
            while (it_answer != answer.end()) {
                it_answer = answer.erase(it_answer);
            }
        }
    }

    return answer;
}