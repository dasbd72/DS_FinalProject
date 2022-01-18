#include "trie.hpp"

#include <algorithm>
#include <list>
#include <string>
trie::node *trie::create_node() {
    node *tmp = new node;
    for (int i = 0; i < ALPHABET_SIZE; i++) tmp->childs[i] = NULL;
    return tmp;
}

trie::trie() {
    this->root = this->create_node();
    this->reversed_root = this->create_node();
}

void trie::insert(const std::string &str, const int &index) {
    node *curr = this->root;
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (!curr->childs[(*it) - 'a'])
            curr->childs[(*it) - 'a'] = create_node();
        curr = curr->childs[(*it) - 'a'];
        if (curr->belong.empty() || *curr->belong.rbegin() != index)
            curr->belong.push_back(index);
    }
    if (curr->belong_end.empty() || *curr->belong_end.rbegin() != index)
        curr->belong_end.push_back(index);

    node *rcurr = this->reversed_root;
    for (auto rit = str.rbegin(); rit != str.rend(); ++rit) {
        if (!rcurr->childs[(*rit) - 'a'])
            rcurr->childs[(*rit) - 'a'] = create_node();
        rcurr = rcurr->childs[(*rit) - 'a'];
        if (rcurr->belong.empty() || *rcurr->belong.rbegin() != index)
            rcurr->belong.push_back(index);
    }
    if (rcurr->belong_end.empty() || *rcurr->belong_end.rbegin() != index)
        rcurr->belong_end.push_back(index);
}

std::list<int> trie::search(const std::string &str) {
    if (*(str.begin()) == '"') {
        return this->search_exact(str.substr(1, str.length() - 2));
    } else if (*(str.begin()) == '*') {
        return this->search_suffix(str.substr(1, str.length() - 2));
    } else {
        return this->search_prefix(str);
    }
}

std::list<int> trie::search_exact(const std::string &str) {
    node *curr = this->root;
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (curr->childs[(*it) - 'a'])
            curr = curr->childs[(*it) - 'a'];
        else
            return std::list<int>();
    }
    return curr->belong_end;
}

std::list<int> trie::search_prefix(const std::string &str) {
    node *curr = this->root;
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (curr->childs[(*it) - 'a'])
            curr = curr->childs[(*it) - 'a'];
        else
            return std::list<int>();
    }
    return curr->belong;
}

std::list<int> trie::search_suffix(const std::string &str) {
    node *curr = this->reversed_root;
    for (auto rit = str.rbegin(); rit != str.rend(); ++rit) {
        if (curr->childs[(*rit) - 'a'])
            curr = curr->childs[(*rit) - 'a'];
        else
            return std::list<int>();
    }
    return curr->belong;
}