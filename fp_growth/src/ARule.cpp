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

void ARule::build_rule(FPTree& fptree, vector<Rule>& container) {
    for (auto child: fptree.root->children) {
        Rule rule = Rule();
        rule.RHS.push_back(fptree.root->word);
        rule.rhs_count = fptree.root->frequency;
        auto link = child.second;
        while (link != nullptr && link->frequency >= fptree.min_support) {
            rule.LHS.push_back(link->word);
            Rule newRule = rule;
            newRule.lhs_count = link->frequency;
            newRule.confidence = static_cast<double>(newRule.lhs_count)/newRule.rhs_count;

        }
    }
}
