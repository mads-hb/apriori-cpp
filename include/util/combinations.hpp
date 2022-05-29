#include <vector>

#include "apriori.hpp"
#ifndef APRIORI_UTIL_COMBINATIONS_H
#define APRIORI_UTIL_COMBINATIONS_H

template<typename T>
std::vector<T> combinations(T array, int k);

std::vector<CandidateKey> combinations(CandidateKey array, int k);
std::vector<std::vector<CandidateKey>> combinations(std::vector<CandidateKey> array, int k);

#endif //APRIORI_UTIL_COMBINATIONS_H