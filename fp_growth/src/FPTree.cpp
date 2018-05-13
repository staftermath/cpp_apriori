//
// Created by gwengww on 5/12/18.
//

#include "include/FPTree.hpp"
#include "include/FileLoader.hpp"
#include <fstream>
#include <algorithm>

using namespace std;

void insertTree(shared_ptr<FPNode>& root,
                const vector<ITEM>& trans,
                const size_t & start,
                unordered_map<ITEM, shared_ptr<FPNode>>& hash) {
    if (start >= trans.size()) return;
    auto search = root->children.find(trans[start]);
    shared_ptr<FPNode> next;
    if (search != root->children.end()) {
        next = search->second;
        next->frequency++;
    } else {
        next = make_shared<FPNode>(trans[start]);
        next->parent = root;
        root->children[trans[start]] = next;
        auto last_node_link = hash[trans[start]]->last_node_link;
        hash[trans[start]]->last_node_link = next;
        last_node_link->node_link = next;
    }
    insertTree(next, trans, start+1, hash);
}

FPTree::FPTree(string filename, long min_support, string sep) {
    this->min_support = min_support;
    this->root = make_shared<FPNode>("");
    FileLoader fileLoader(move(filename), move(sep));
    fileLoader.load(true);
//    first iteration to create frequent items.
    unordered_map<ITEM, long> freqItems;
    while (!fileLoader.eof()) {
        auto transaction = fileLoader.next();
        for (const ITEM& s: transaction) {
            freqItems[s]++;
        }
    }
    fileLoader.close();
//    create header links
//    FPNode* temp;
    for (auto p: freqItems) {
        if (p.second >= this->min_support) {
            this->header_table[p.first] = make_shared<FPNode>("");
            this->header_table[p.first]->frequency = p.second;
            this->header_table[p.first]->last_node_link = this->header_table[p.first];
        }
    }

//    grow FP tree
    for (const vector<ITEM> & trans: fileLoader.get_cache()) {
        // output only item with frequency >= min_support
        vector<ITEM> transaction(trans.size());
        unsigned long length = 0;
        for (int i=0; i<trans.size();i++) {
            if (freqItems[trans[i]] >= min_support) {
                transaction[length] = trans[i];
                length++;
            }
        }
        transaction.resize(length);
        // sorting by frequency
        sort(transaction.begin(), transaction.end(), [&freqItems](const ITEM & a, const ITEM & b){
            return tie(freqItems[a], a) > tie(freqItems[b], b);
        });
        for (const string& str: transaction) {
            insertTree(root, transaction, 0, header_table);
        }
    }

}

FPTree::FPTree(string filename, long min_support): FPTree(move(filename), min_support, ","){
}