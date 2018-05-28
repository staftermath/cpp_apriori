//
// Created by gwengww on 5/12/18.
//

#include "include/FPTree.hpp"
#include "include/FileLoader.hpp"
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <assert.h>
#include <iostream>

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
    this->root = make_shared<FPNode>("");
}

void FPTree::construct(string filename, string sep) {
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
        build_pattern(link_head);
        link_head = link_head->node_link;
    }
    this->count = root->frequency;
}

void FPTree::build_pattern(shared_ptr<FPNode> root) {

}

FPTree FPTree::build_conditional_tree(ITEM word, FPTree& fptree) {
    auto link_head = fptree.header_table[word];
    FPTree newTree = FPTree(fptree.min_support);
    shared_ptr<FPNode> new_head_link;
    shared_ptr<FPNode> node;
    shared_ptr<FPNode> new_node;
    unordered_map<shared_ptr<FPNode>, shared_ptr<FPNode>> visited;

    // add new root to visited;
    visited[fptree.root] = newTree.root;
    // construct link head for target word
    new_head_link = make_shared<FPNode>(link_head->word);
    new_head_link->frequency = link_head->frequency;
    new_head_link->last_node_link = new_head_link;
    newTree.header_table[word] = new_head_link;
    visited[link_head] = new_head_link;
    link_head = link_head->node_link;

    while (link_head != nullptr) {
        new_head_link->node_link = make_shared<FPNode>(link_head->word);
        newTree.header_table[word]->last_node_link = new_head_link->node_link;

        new_head_link = new_head_link->node_link;
        new_head_link->frequency = link_head->frequency;
        visited[link_head] = new_head_link;
        link_head = link_head->node_link;
    }
    link_head = fptree.header_table[word];
    long counter = 0;
    while (link_head != nullptr) {
        new_head_link = visited[link_head];
        new_node = new_head_link;
        node = link_head->parent;
        while (!node->word.empty()) {
//            not root node
            auto searchParent = visited.find(node);
            if ( searchParent != visited.end()) {
                new_node->parent = searchParent->second;
                auto children_of_parent = new_node->parent->children;
                if (children_of_parent.find(new_node->word) == children_of_parent.end());{
                    new_node->parent->children[new_node->word] = new_node;
                }
                new_node = new_node->parent;
                new_node->frequency += node->frequency;
            } else {
                new_node->parent = make_shared<FPNode>(node->word);
                new_node->parent->children[new_node->word] = new_node;
                visited[node] = new_node->parent;
                new_node = new_node->parent;
                new_node->frequency = node->frequency;
                auto searchLink = newTree.header_table.find(node->word);
                if ( searchLink == newTree.header_table.end()) {
                    newTree.header_table[node->word] = new_node;
                    newTree.header_table[node->word]->last_node_link = newTree.header_table[node->word];
                } else {
                    searchLink->second->last_node_link->node_link = new_node;
                    searchLink->second->last_node_link = new_node;
                }
            }
            node = node->parent;
        }
        // root shouldn't already have a children with this word
        auto children_of_root = newTree.root->children;
        auto searchVisited = children_of_root.find(new_node->word);
        if (searchVisited == children_of_root.end()) {
            newTree.root->children[new_node->word] = new_node;
            new_node->parent = fptree.root;
        }
        // move to next link_node
        link_head = link_head->node_link;
        counter++;
    }

    return newTree;
}