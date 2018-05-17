//
// Created by gwengww on 5/13/18.
//

#include "include/ARule.hpp"
#include <iostream>
using namespace std;

vector<Rule> ARule::construct(const FPTree & fptree) {
    vector<Rule> result;
    for (auto item: fptree.header_table) {
        FPTree fptree = FPTree(fptree.min_support);
        fptree.construct(item.first, item.second);
    }
};

void ARule::build_rule(FPTree& targetTree, vector<Rule>& container, FPTree& mainTree) {
    for (auto child: targetTree.root->children) {
        Rule rule = Rule();
        rule.RHS.push_back(targetTree.root->word);
        rule.rhs_count = targetTree.root->frequency;
        auto link = child.second;
        while (link != nullptr && link->frequency >= targetTree.min_support) {
            rule.LHS.push_back(link->word);
            Rule newRule = rule;

        }
    }
}

long ARule::search_support(vector<ITEM>& pattern, shared_ptr<FPNode> node, size_t start) {
    long support = 0;
    cout << "searching node " << node->word << endl;
    for (auto child: node->children) {
        cout << "searching child of node " << node->word << ": " << child.second->word <<
             "freq: " << child.second->frequency << endl;
        cout << "support: " << support << endl;
        if (child.second->word == pattern[start]) {
            if (start == 0) support += child.second->frequency;
            else support += search_support(pattern, child.second, start - 1);
        } else {
            support += search_support(pattern, child.second, start);
        }
    }
    return support;
}
