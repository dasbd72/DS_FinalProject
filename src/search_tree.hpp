#ifndef SEARCH_TREE
#define SEARCH_TREE
#include <string>
#include <vector>

#include "trie.hpp"

class search_tree {
   private:
   public:
    std::vector<std::string> title;
    trie mytrie;

   private:
    bool search_recursion(const std::vector<std::string>& query, int pos);

   public:
    search_tree(){};
    ~search_tree(){};
    void insert(const std::string& word);
    bool search(const std::vector<std::string>& query);
};

#endif