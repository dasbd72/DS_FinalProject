#define FILE_EXTENSION ".txt"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utilities.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string data_dir = argv[1] + string("/");
    string query = string(argv[2]);
    string output = string(argv[3]);

    fstream fi;
    int data_idx = 100;
    while (filesystem::exists(data_dir + to_string(data_idx) + FILE_EXTENSION)) {
        string file, title_str, content_str;
        fi.open(data_dir + to_string(data_idx) + FILE_EXTENSION, ios::in);
        getline(fi, title_str);
        vector<string> title;
        title = word_parse(split(title_str, " "));

        while (getline(fi, content_str)) {
            vector<string> content;
            content = word_parse(split(content_str, " "));
            for (auto& word : content) {
                cout << word << endl;
            }
        }
        fi.close();
        data_idx++;
    }

    // Read File & Parser Example

    // string file, title_name, tmp;
    // fstream fi;
    // vector<string> tmp_string;

    // // from data_dir get file ....
    // // eg : use 0.txt in data directory
    // fi.open("data/0.txt", ios::in);

    // // GET TITLENAME
    // getline(fi, title_name);

    // // GET TITLENAME WORD ARRAY
    // tmp_string = split(title_name, " ");

    // vector<string> title = word_parse(tmp_string);

    // // for(auto &word : title){
    // // 	cout << word << endl;
    // // }

    // // GET CONTENT LINE BY LINE
    // while(getline(fi, tmp)){

    //     // GET CONTENT WORD VECTOR
    // 	tmp_string = split(tmp, " ");

    // 	// PARSE CONTENT
    // 	vector<string> content = word_parse(tmp_string);

    // 	for(auto &word : content){
    // 		cout << word << endl;
    // 	}
    // 	//......
    // }

    // // CLOSE FILE
    // fi.close();
}

// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
