#include "search_tree.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "trie.hpp"

search_tree::search_tree(/* args */) {
}

search_tree::~search_tree() {
}

void search_tree::insert(const std::string& word) {
    this->mytrie.insert(word);
}

bool search_tree::search(const std::vector<std::string>& query) {
    return search_recursion(query, query.size() - 1);
}

bool search_tree::search_recursion(const std::vector<std::string>& query, int pos) {
    bool rchild_result = this->mytrie.search(query[pos]);
    if (pos - 2 >= 0) {
        if (query[pos - 1] == "+") {
            if (!rchild_result)
                return false;
            else
                return this->search_recursion(query, pos - 2);
        } else {
            if (rchild_result)
                return true;
            else
                return this->search_recursion(query, pos - 2);
        }
    } else
        return rchild_result;
}
