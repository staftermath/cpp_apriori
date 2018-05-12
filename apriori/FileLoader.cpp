//
// Created by gwengww on 5/12/18.
//

#include "FileLoader.h"
#include <fstream>
using namespace std;

void FileLoader::load() {
    _buffer.open(_file_path);
}
void FileLoader::load(bool to_memory) {
    if (!_buffer.is_open()) load();
    cached = to_memory;
}

FileLoader::~FileLoader() {
    if (_buffer.is_open()) _buffer.close();
}

vector<string> FileLoader::next() {
    string this_line;
    getline(_buffer, this_line);
    vector<string> result;
    auto delimiter = this_line.find(_sep);
    size_t start = 0;
    while (delimiter != string::npos) {
        result.push_back(this_line.substr(start, delimiter-start));
        start = delimiter + 1;
        delimiter = this_line.find(_sep, start);
    }
    result.push_back(this_line.substr(start, delimiter-start));
    if (cached) {
        _cache.push_back(result);
    }
    return result;
}
void FileLoader::close() {
    if (_buffer.is_open()) _buffer.close();
}

bool FileLoader::eof() {
    return _buffer.eof();
}

const vector<vector<string>>& FileLoader::get_cache() {
    return _cache;
}