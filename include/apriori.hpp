//
// Created by mads on 5/28/22.
//
#include <unordered_map>
#include <map>

#include "database.hpp"

#ifndef APRIORI_APRIORI_H
#define APRIORI_APRIORI_H


typedef int Support;
typedef std::vector<int> CandidateKey;
typedef std::map<CandidateKey, Support> FrequentItemSet;

FrequentItemSet apriori(const Database &T, Support min_support);

#endif //APRIORI_APRIORI_H
