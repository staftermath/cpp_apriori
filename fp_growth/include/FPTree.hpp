//
// Created by gwengww on 5/12/18.
//

#ifndef CPP_APRIORI_FREQUENTPATTERN_H
#define CPP_APRIORI_FREQUENTPATTERN_H

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <unordered_map>

using namespace std;

using ITEM = string;
using TRANSACTION = vector<ITEM>;

struct FPNode {
    const ITEM word;
    long frequency=1;
    shared_ptr<FPNode> parent= nullptr;
    unordered_map<ITEM, shared_ptr<FPNode>> children = {};
    shared_ptr<FPNode> node_link = nullptr;
    shared_ptr<FPNode> last_node_link = nullptr;
    FPNode(ITEM item): word(item) {};
};

struct FPTree {
public:
    FPTree(long min_support);
    void construct(string filename, string sep);
    void construct(string filename) {
        construct(filename, ",");
    };
    void construct(ITEM leaf, shared_ptr<FPNode> link_head);
    shared_ptr<FPNode> root;
    unordered_map<ITEM, shared_ptr<FPNode>> header_table;
    long min_support;
    long count=0;
private:
    void build_pattern(shared_ptr<FPNode> from, shared_ptr<FPNode> to);
};

#endif //CPP_APRIORI_FREQUENTPATTERN_H
