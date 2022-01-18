#ifndef TRIE
#define TRIE
#include <list>
#include <string>
const int ALPHABET_SIZE = 26;
class trie {
   private:
    struct node {
        node *childs[ALPHABET_SIZE];
        std::list<int> belong;
        std::list<int> belong_end;
    };
    node *root;
    node *reversed_root;

    node *create_node();
    std::list<int> search_exact(const std::string &str);
    std::list<int> search_prefix(const std::string &str);
    std::list<int> search_suffix(const std::string &str);

   public:
    trie();
    ~trie(){};
    void insert(const std::string &str, const int &index);
    std::list<int> search(const std::string &str);
};
#endif