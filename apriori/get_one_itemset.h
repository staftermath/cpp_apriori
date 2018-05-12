//
// Created by gwengww on 5/12/18.
//

#ifndef CPP_APRIORI_GET_ONE_ITEMSET_H
#define CPP_APRIORI_GET_ONE_ITEMSET_H

class GetOneItemSet {
public:
    long support;
    GetOneItemSet(long support): support(support) {};
    ~GetOneItemSet();
    void construct();

private:
};

#endif //CPP_APRIORI_GET_ONE_ITEMSET_H
