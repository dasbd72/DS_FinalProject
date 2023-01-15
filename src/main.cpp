#define FILE_EXTENSION ".txt"

// #include <stdio.h>
// #include <time.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "search_tree.hpp"
#include "utilities.hpp"

using namespace std;

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, fmt, ##args);
#define DEBUG_MSG(str) std::cout << str << "\n";
#else
#define DEBUG_PRINT(fmt, args...)
#define DEBUG_MSG(str)
#endif  // DEBUG

#define TIMING
#ifdef TIMING
#include <ctime>
#define TIMING_START(arg)          \
    struct timespec __start_##arg; \
    clock_gettime(CLOCK_MONOTONIC, &__start_##arg);
#define TIMING_END(arg)                                                                       \
    {                                                                                         \
        struct timespec __temp_##arg, __end_##arg;                                            \
        double __duration_##arg;                                                              \
        clock_gettime(CLOCK_MONOTONIC, &__end_##arg);                                         \
        if ((__end_##arg.tv_nsec - __start_##arg.tv_nsec) < 0) {                              \
            __temp_##arg.tv_sec = __end_##arg.tv_sec - __start_##arg.tv_sec - 1;              \
            __temp_##arg.tv_nsec = 1000000000 + __end_##arg.tv_nsec - __start_##arg.tv_nsec;  \
        } else {                                                                              \
            __temp_##arg.tv_sec = __end_##arg.tv_sec - __start_##arg.tv_sec;                  \
            __temp_##arg.tv_nsec = __end_##arg.tv_nsec - __start_##arg.tv_nsec;               \
        }                                                                                     \
        __duration_##arg = __temp_##arg.tv_sec + (double)__temp_##arg.tv_nsec / 1000000000.0; \
        printf("%s took %lfs.\n", #arg, __duration_##arg);                                    \
    }
#else
#define TIMING_START(arg)
#define TIMING_END(arg)
#endif  // TIMING

int main(int argc, char* argv[]) {
    string data_dir = argv[1] + string("/");
    string query_path = string(argv[2]);
    string output_path = string(argv[3]);

    std::vector<std::vector<std::string>> titles;
    search_tree datas;

    TIMING_START(build_trie);
    for (int data_idx = 0;; data_idx++) {
        fstream data_file;
        string title_str, content_str;
        vector<string> title;

        // Open file
        data_file.open(data_dir + to_string(data_idx) + FILE_EXTENSION, ios::in);
        if (!data_file.is_open())
            break;

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
    TIMING_END(build_trie);
    TIMING_START(query);
    {
        string query_line;
        fstream query_file, output_file;
        query_file.open(query_path, ios::in);
        output_file.open(output_path, ios::out);

        while (getline(query_file, query_line, '\n')) {
            if (*(query_line.rbegin()) == 13)
                query_line.pop_back();
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
    TIMING_END(query);
}
/*
mingw32-make.exe all
g++ -std=c++17 -o essay-search.exe ./src/*.cpp -lstdc++fs
.\essay-search.exe data-more .\query\query-more.txt output.txt
.\essay-search.exe data-more .\query\query.txt output.txt

make all
g++-7 -std=c++17 -o essay-search ./src/*.cpp -lstdc++fs
g++-7 -std=c++17 -o essay-search ./src/*.cpp -lstdc++fs -fsanitize=address -g
./essay-search data-more ./query/query-more.txt output.txt
./essay-search data-more ./query/query.txt output.txt
time
timeout -s SIGINT 60
*/