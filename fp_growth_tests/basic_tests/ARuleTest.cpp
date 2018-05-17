//
// Created by gwengww on 5/16/18.
//

#include <gtest/gtest.h>
#include <unordered_map>
#include <ctime>
#include <string>
#include <fstream>
#include "include/ARule.hpp"
#include "include/FPTree.hpp"
using namespace std;

TEST(ARule, test_eq) {
    string sample_data = "/home/gwengww/Documents/repos/cpp_apriori/fp_growth_tests/test_data/sample_file.txt";
    auto fptree = FPTree(2);
    fptree.construct(sample_data);
    ARule arule(0, 0);
    long spt;
    vector<ITEM> pattern = {"item2", "item1"};
    spt = arule.search_support(pattern, fptree.root, 1);
    cout << "got support: " << spt << endl;
}
