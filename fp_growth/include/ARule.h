//
// Created by gwengww on 5/13/18.
//

#ifndef CPP_APRIORI_ARULE_H
#define CPP_APRIORI_ARULE_H

#include "FPTree.hpp"
using namespace std;


struct Rule {
    vector<ITEM> LHS;
    vector<ITEM> RHS;
    double confidence;
    double lift;
    double frequence;
};

class ARule {
public:
    ARule(double confidence, double lift): mConfidence(confidence), mLift(lift) {};
    vector<Rule> construct(const FPTree & fptree);
private:
    double mConfidence;
    double mLift;

};



#endif //CPP_APRIORI_ARULE_H
