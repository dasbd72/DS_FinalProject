#ifndef SEARCH_TREE
#define SEARCH_TREE
#include <list>
#include <string>
#include <vector>

#include "trie.hpp"

class search_tree {
   public:
    trie mytrie;

   public:
    search_tree(){};
    ~search_tree(){};
    void insert(const std::string& word, const int& index);
    std::list<int> search(const std::vector<std::string>& query);
};

#endif