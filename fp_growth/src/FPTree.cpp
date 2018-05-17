//
// Created by gwengww on 5/12/18.
//

#include "include/FPTree.hpp"
#include "include/FileLoader.hpp"
#include <fstream>
#include <algorithm>

using namespace std;

void insertTree(shared_ptr<FPNode>& node,
                const vector<ITEM>& trans,
                const size_t & start,
                unordered_map<ITEM, shared_ptr<FPNode>>& hash) {
    if (start >= trans.size()) return;
    auto search = node->children.find(trans[start]);
    shared_ptr<FPNode> next;
    if (search != node->children.end()) {
        next = search->second;
        next->frequency++;
    } else {
        next = make_shared<FPNode>(trans[start]);
        next->parent = node;
        node->children[trans[start]] = next;
        if (hash[trans[start]] == nullptr) {
            hash[trans[start]] = next;
            next->last_node_link = next;
        } else {
            hash[trans[start]]->last_node_link->node_link = next;
            hash[trans[start]]->last_node_link = next;
        }
    }
    insertTree(next, trans, start+1, hash);
}

FPTree::FPTree(long min_support) {
    this->min_support = min_support;
}

void FPTree::construct(string filename, string sep) {
    this->root = make_shared<FPNode>("dummy");
    FileLoader fileLoader(move(filename), move(sep));
    fileLoader.load(true);
//    first iteration to create frequent items.
    unordered_map<ITEM, long> freqItems;
    while (!fileLoader.eof()) {
        auto transaction = fileLoader.next();
        for (const ITEM& s: transaction) {
            freqItems[s]++;
        }
        this->count++;
    }
    fileLoader.close();
//    create header links
//    FPNode* temp;
    for (auto p: freqItems) {
        if (p.second >= this->min_support) {
//            this->header_table[p.first] = make_shared<FPNode>("");
//            this->header_table[p.first]->frequency = p.second;
//            this->header_table[p.first]->last_node_link = this->header_table[p.first];
            this->header_table[p.first] = nullptr;
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
        insertTree(root, transaction, 0, header_table);
    }

}

void FPTree::construct(ITEM leaf, shared_ptr<FPNode> link_head) {
    this->root = make_shared<FPNode>(leaf);
    while (link_head != nullptr) {
        root->frequency += link_head->frequency; // consider keeping a frequency table for all freq items;
        build_pattern(link_head, root);
        link_head = link_head->node_link;
    }
    this->count = root->frequency;
}

void FPTree::build_pattern(shared_ptr<FPNode> from, shared_ptr<FPNode> to) {
    if (from->parent == nullptr) return;
    auto search = to->children.find(from->word);
    if (search != to->children.end()) {
        search->second->frequency += from->frequency;
        build_pattern(from->parent, to);
        build_pattern(from->parent, search->second);
    } else {
        shared_ptr<FPNode> next = make_shared<FPNode>(from->word);
        next->parent = to;
        to->children[from->word] = next;
        build_pattern(from->parent, to);
        build_pattern(from->parent, next);
    }
}