#define FILE_EXTENSION ".txt"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "search_tree.hpp"
#include "utilities.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string data_dir = argv[1] + string("/");
    string query_path = string(argv[2]);
    string output_path = string(argv[3]);

    vector<search_tree*> datas;
    for (int data_idx = 0; filesystem::exists(data_dir + to_string(data_idx) + FILE_EXTENSION); data_idx++) {
        fstream data_file;
        string title_str, content_str;
        search_tree* searchTree = new search_tree();

        // Open file
        data_file.open(data_dir + to_string(data_idx) + FILE_EXTENSION, ios::in);

        // Process title
        getline(data_file, title_str);
        searchTree->title = word_parse(split(title_str, " "));

        while (getline(data_file, content_str)) {
            vector<string> content;
            content = word_parse(split(content_str, " "));
            for (auto& word : content)
                searchTree->insert(lower_str(word));
        }
        data_file.close();
        datas.push_back(searchTree);
    }
    {
        string query_line;
        fstream query_file, output_file;
        query_file.open(query_path, ios::in);
        output_file.open(output_path, ios::out);

        while (getline(query_file, query_line, '\n')) {
            vector<string> query = split(query_line, " ");

            for (auto& data : datas) {
                if (data->search(query)) {
                    // Output title if matches
                    auto it = data->title.begin();
                    output_file << *it;
                    for (++it; it != data->title.end(); ++it)
                        output_file << " " + *it;
                    output_file << "\n";
                }
            }
        }
        output_file.flush();

        query_file.close();
        output_file.close();
    }
}

// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
