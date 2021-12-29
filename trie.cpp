#include "trie.hpp"

#include <string>
trie::node *trie::create_node() {
    node *tmp = new node;
    tmp->isEnd = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) tmp->childs[i] = NULL;
    return tmp;
}

trie::trie() {
    this->root = this->create_node();
    this->reversed_root = this->create_node();
}

trie::~trie() {
    // TODO : add later
}

void trie::insert(const std::string &str) {
    {
        node *curr = this->root;
        for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
            if (curr->childs[(*it) - 'a'])
                curr = curr->childs[(*it) - 'a'];
            else
                curr = curr->childs[(*it) - 'a'] = create_node();
        }
        curr->isEnd = true;
    }
    {
        node *curr = this->reversed_root;
        for (auto rit = str.rbegin(); rit != str.rend(); ++rit) {
            if (curr->childs[(*rit) - 'a'])
                curr = curr->childs[(*rit) - 'a'];
            else
                curr = curr->childs[(*rit) - 'a'] = create_node();
        }
        curr->isEnd = true;
    }
}

bool trie::search(const std::string &str) {
    if (*str.begin() == '"') {
        return this->search_prefix(str.substr(1, str.length() - 2));
    } else if (*str.begin() == '*') {
        return this->search_suffix(str.substr(1, str.length() - 2));
    } else {
        return this->search_exact(str);
    }
}

bool trie::search_exact(const std::string &str) {
    node *curr = this->root;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (curr->childs[(*it) - 'a'])
            curr = curr->childs[(*it) - 'a'];
        else
            return false;
    }
    return (curr->isEnd);
}

bool trie::search_prefix(const std::string &str) {
    node *curr = this->root;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (curr->childs[(*it) - 'a'])
            curr = curr->childs[(*it) - 'a'];
        else
            return false;
    }
    return true;
}

bool trie::search_suffix(const std::string &str) {
    node *curr = this->reversed_root;
    for (auto rit = str.rbegin(); rit != str.rend(); ++rit) {
        if (curr->childs[(*rit) - 'a'])
            curr = curr->childs[(*rit) - 'a'];
        else
            return false;
    }
    return true;
}