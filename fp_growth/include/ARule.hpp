//
// Created by gwengww on 5/13/18.
//

#ifndef CPP_APRIORI_ARULE_H
#define CPP_APRIORI_ARULE_H

#include "FPTree.hpp"
using namespace std;


struct Rule {
    vector<string> LHS;
    vector<string> RHS;
    long lhs_count;
    double confidence;
    double lift;
    long rhs_count;

    Rule& operator=(const Rule& other) {
        if (this != &other) {
            lhs_count = other.lhs_count;
            confidence = other.confidence;
            lift = other.lift;
            rhs_count = other.rhs_count;
            LHS = other.LHS;
            RHS = other.RHS;
        }
    }
};

class ARule {
public:
    ARule(double confidence, double lift): mConfidence(confidence), mLift(lift) {};
    vector<Rule> construct(const FPTree & fptree);
    FPTree growPatternTree(ITEM leaf, FPTree fptree);
private:
    double mConfidence;
    double mLift;
    void build_rule(FPTree& fptree, vector<Rule>& container);

};



#endif //CPP_APRIORI_ARULE_H