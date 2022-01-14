#ifndef SUFFIX_TREE
#define SUFFIX_TREE
#include <string>
const int ALPHABET_SIZE = 26;
class suffix_tree {
   private:
   public:
    suffix_tree();
    ~suffix_tree();
    void insert(const std::string &str);
    bool search(const std::string &str);
};
#endif