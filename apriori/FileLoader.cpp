//
// Created by gwengww on 5/12/18.
//

#include "FileLoader.h"

void FileLoader::load() {
    _buffer = infile(_file_path);
}
void FileLoader::load(bool to_memory) {
    load();
    to_memory = true;
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
    if (to_memory) {
        _hash.push_back(result);
    }
    return result;
}
void FileLoader::close() {
    if (_buffer.is_open()) _buffer.close();
}