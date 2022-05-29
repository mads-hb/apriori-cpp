#include <vector>
#include <set>
#include <algorithm>

#include "util/combinations.hpp"


namespace {
    template<typename T>
    void findCombinations(std::vector<T> const &arr, int i, int k,
                          std::set<std::vector<T>> &subarrays, std::vector<T> &out){
        // do nothing for empty input
        if (arr.size() == 0) {
            return;
        }

        // base case: combination size is `k`
        if (k == 0) {
            subarrays.insert(out);
            return;
        }

        // return if no more elements are left
        if (i == arr.size()) {
            return;
        }

        // include the current element in the current combination and recur
        out.push_back(arr[i]);
        findCombinations(arr, i + 1, k - 1, subarrays, out);

        // exclude the current element from the current combination
        out.pop_back();        // backtrack

        // exclude the current element from the current combination and recur
        findCombinations(arr, i + 1, k, subarrays, out);
    }
}

std::vector<std::vector<CandidateKey>> combinations(std::vector<CandidateKey> array, int k){

    // set to store all combinations
    std::set<std::vector<CandidateKey>> subarrays;
    // vector to store a combination
    std::vector<CandidateKey> out;

    findCombinations<CandidateKey>(array, 0, k, subarrays, out);

    std::vector<std::vector<CandidateKey>> result;
    for (auto vec: subarrays) {
        std::sort(vec.begin(), vec.end());
        result.push_back(vec);
    }
    return result;
}

std::vector<CandidateKey> combinations(CandidateKey array, int k){

    // set to store all combinations
    std::set<CandidateKey> subarrays;
    // vector to store a combination
    CandidateKey out;

    findCombinations(array, 0, k, subarrays, out);

    std::vector<CandidateKey> result;
    for (auto vec: subarrays) {
        std::sort(vec.begin(), vec.end());
        result.push_back(vec);
    }
    return result;
}