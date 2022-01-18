#define FILE_EXTENSION ".txt"

// #include <stdio.h>
// #include <time.h>

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "search_tree.hpp"
#include "utilities.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // clock_t t;
    // t = clock();

    string data_dir = argv[1] + string("/");
    string query_path = string(argv[2]);
    string output_path = string(argv[3]);

    std::vector<std::vector<std::string>> titles;
    search_tree datas;

    for (int data_idx = 0; std::experimental::filesystem::exists(data_dir + to_string(data_idx) + FILE_EXTENSION); data_idx++) {
        fstream data_file;
        string title_str, content_str;
        vector<string> title;

        // Open file
        data_file.open(data_dir + to_string(data_idx) + FILE_EXTENSION, ios::in);

        // Process title
        getline(data_file, title_str);
        title = split(title_str, " ");
        titles.push_back(title);

        // Insert Title
        title = word_parse(title);
        for (auto& word : title)
            datas.insert(lower_str(word), data_idx);
        // Insert Contents
        while (getline(data_file, content_str)) {
            vector<string> content;
            content = word_parse(split(content_str, " "));
            for (auto& word : content)
                datas.insert(lower_str(word), data_idx);
        }
        // Close File
        data_file.close();
    }
    {
        string query_line;
        fstream query_file, output_file;
        query_file.open(query_path, ios::in);
        output_file.open(output_path, ios::out);

        while (getline(query_file, query_line, '\n')) {
            bool found = false;
            // output_file << query_line << "\n";
            vector<string> query = split(query_line, " ");
            for (auto& data : query)
                for (auto& c : data)
                    c = tolower(c);

            list<int> result = datas.search(query);

            if (result.size() == 0) {
                output_file << "Not Found!\n";
            } else {
                for (auto& index : result) {
                    auto it = titles[index].begin();
                    output_file << *it;
                    for (++it; it != titles[index].end(); ++it)
                        output_file << " " + *it;
                    output_file << "\n";
                }
            }
        }
        output_file.flush();

        query_file.close();
        output_file.close();
    }
    // t = clock() - t;
    // double time_taken = ((double)t) / CLOCKS_PER_SEC;
    // printf("The program took %f seconds to execute\n", time_taken);
}
/* 
mingw32-make.exe all
.\essay-search.exe data-more .\querry\query-more.txt output.txt

make all
./essay-search data-more ./querry/query-more.txt output.txt
*/