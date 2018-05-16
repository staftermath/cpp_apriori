//
// Created by gwengww on 5/13/18.
//

#include "include/ARule.hpp"
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
