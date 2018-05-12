//
// Created by gwengww on 5/12/18.
//

#include <gtest/gtest.h>
#include "FileLoader.h"
using namespace std;

TEST(FileLoader, test_eq) {
    string sample_data = "/home/gwengww/Documents/repos/cpp_apriori/apriori_tests/test_data";
    FileLoader file_loader(sample_data + "/sample_file.txt");
    file_loader.load();
    cout << "load from file:" << endl;
    while (!file_loader.eof()) {
        auto thisLine = file_loader.next();
        for (const string & s: thisLine) {
            cout << s << ", " << flush;
        }
        cout << endl;
    }
    file_loader.close();

    file_loader.load(true);
    while (!file_loader.eof()) {
        file_loader.next();
    }
    cout << "load from cache:" << endl;
    for (const vector<string>& v: file_loader.get_cache()) {
        for (const string &s: v) {
            cout << s << "," << flush;
        }
        cout << endl;
    }
}

