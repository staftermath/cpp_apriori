//
// Created by gwengww on 5/12/18.
//

#ifndef CPP_APRIORI_FILE_LOADER_H
#define CPP_APRIORI_FILE_LOADER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;
class FileLoader {
public:
    FileLoader(string file_path, string sep): _file_path(move(file_path)), _sep(move(sep)) {};
    FileLoader(string file_path): _file_path(move(file_path)), _sep(",") {};
    ~FileLoader();

    void load();
    void load(bool to_memory);
    vector<string> next();
    vector<string> next(unordered_map<string, long> count, long support);
    void close();
    bool eof();
    vector<vector<string>>& get_cache();

private:
    string _file_path;
    string _sep;
    ifstream _buffer;
    vector<vector<string>> _cache;
    bool cached=false;
};
#endif //CPP_APRIORI_FILE_LOADER_H
