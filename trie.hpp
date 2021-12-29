#ifndef TRIE
#define TRIE
#include <string>
const int ALPHABET_SIZE = 26;
class trie {
   private:
    struct node {
        bool isEnd;
        node *childs[ALPHABET_SIZE];
    };
    node *root;
    node *reversed_root;

    node *create_node();
    bool search_exact(const std::string &str);
    bool search_prefix(const std::string &str);
    bool search_suffix(const std::string &str);

   public:
    trie();
    ~trie();
    void insert(const std::string &str);
    bool search(const std::string &str);
};
#endif