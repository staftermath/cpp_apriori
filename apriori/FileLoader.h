//
// Created by gwengww on 5/12/18.
//

#ifndef CPP_APRIORI_FILE_LOADER_H
#define CPP_APRIORI_FILE_LOADER_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class FileLoader {
public:
    FileLoader(string file_path, string sep): _file_path(move(file_path)), _sep(sep) {};
    ~FileLoader();
    void load();
    void load(bool to_memory);
    vector<string> next();
    void close();
private:
    string _file_path;
    string _sep;
    ifstream _buffer;
    vector<vector<string>> _hash;
    bool to_memory;
};


#endif //CPP_APRIORI_FILE_LOADER_H
