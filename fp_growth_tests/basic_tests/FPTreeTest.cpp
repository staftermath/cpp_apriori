//
// Created by gwengww on 5/12/18.
//

#include <gtest/gtest.h>
#include <unordered_map>
#include <ctime>
#include <string>
#include <fstream>
#include "include/FPTree.hpp"
using namespace std;

TEST(FPTree, test_eq) {
    string sample_data = "/home/gwengww/Documents/repos/cpp_apriori/fp_growth_tests/test_data/sample_file.txt";
    auto fptree = FPTree(2);
    fptree.construct(sample_data);
    cout << "Count of transactions: " << fptree.count << endl;
    for (auto v: fptree.header_table) {
        cout << v.first << endl;
    }
    cout << "printing FP Tree" << endl;
    for (auto v: fptree.root->children) {
        cout << "children of root: " << v.first << endl;
        cout << "children of " << v.first << endl;
        for (auto k: v.second->children) {
            cout << k.first << endl;
        }
    }
    string large_data = "/home/gwengww/Documents/repos/cpp_apriori/fp_growth_tests/test_data/T40I10D100K.txt";
    clock_t cstart = clock();
    fptree = FPTree(10000);
    fptree.construct(large_data, " ");
    double duration = ( std::clock() - cstart ) / (double) CLOCKS_PER_SEC;
    cout << "total duration: "<< duration << endl;
    cout << "Count of transactions: " << fptree.count << endl;
    for (auto v: fptree.root->children) {
        cout << "Printing big tree: " << v.second->word << endl;
        for (auto w: v.second->children) {
            cout << w.first << ", " << flush;
        }
        cout << endl;
        if (v.second->children.size() >=3) break;
    }

}
