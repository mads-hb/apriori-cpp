#include <set>
#include <algorithm>
#include <bits/stdc++.h>
#include "apriori.hpp"
#include "util/combinations.hpp"
#include "iostream"

namespace {

    bool check_subset(const CandidateKey &key, const std::vector<int> &item_set){
        for (CandidateKey::const_iterator i = key.begin(); i != key.end(); i++){
            bool found = false;
            for (std::vector<int>::const_iterator j = item_set.begin(); j != item_set.end(); j++){
                if (*i == *j){
                    found = true;
                    break;
                }
            }
            if (!found){
                return false;
            }
        }
        return true;
    }

    FrequentItemSet compute_support(const Database &T, std::vector<CandidateKey> candidate_keys){
        FrequentItemSet counts;

        for (auto const &key: candidate_keys){
            counts.insert(std::pair<CandidateKey, Support>(key, 0));
            for (auto const &item_set: T){
                if (check_subset(key, item_set)) {
                    FrequentItemSet::iterator it = counts.find(key);
                    it->second++;
                }
            }
        }
        return counts;
    }

    std::vector<CandidateKey> get_initial_itemset(Database T){
        std::set<int> tmp;
        for (auto const &line: T) {
            for (auto const candidate_key: line) {
                auto it = tmp.find(candidate_key);
                if (it == tmp.end()) {
                    tmp.emplace(candidate_key);
                }
            }
        }
        std::vector<CandidateKey> output;
        for (auto const &val: tmp) {
            CandidateKey ck;
            ck.emplace_back(val);
            output.emplace_back(ck);
        }
        std::sort(output.begin(),output.end());
        return output;
    }

    std::vector<CandidateKey> get_supported_itemsets(FrequentItemSet counts, int min_support, FrequentItemSet * frequent_item_set){
        std::vector<CandidateKey> candidate_set;
        for (const auto& [key, support] : counts) {
            if (support >= min_support){
                candidate_set.emplace_back(key);
                frequent_item_set->insert(std::pair<CandidateKey, Support>(key, support));
            }
        }
        return candidate_set;
    }

    std::vector<CandidateKey> next_candidate_set(std::vector<CandidateKey> Lk){
        std::vector<CandidateKey> Ck;
        if (Lk.empty()) {
            return Ck;
        }
        // Define length of item sets to generate
        int k = Lk.at(0).size();

        auto combs = combinations(Lk, 2);
        for (auto const &comb: combs){
            auto lhs = comb.at(0);
            auto rhs = comb.at(1);
            if (k == 1){
                CandidateKey key(0);
                key.emplace_back(lhs.at(0));
                key.emplace_back(rhs.at(0));
                Ck.emplace_back(key);
            } else {
                auto it = std::search(lhs.begin(), lhs.end()-1, rhs.begin(), rhs.end()-1);
                if (it != lhs.end()) {
                    // Append end items. The rest are shared
                    lhs.emplace_back(rhs.at(k-1));
                    std::sort(lhs.begin(), lhs.end());
                    auto it2 = std::find(Ck.begin(), Ck.end(), lhs);
                    if (it2 == Ck.end()){
                        Ck.emplace_back(lhs);
                    }
                }
            }
        }

        std::vector<CandidateKey> frequents;
        for (auto const &candidate_key: Ck) {
            bool is_frequent = true;
            auto sub_combs= combinations(candidate_key, k);
            for (auto const &sub_key: sub_combs) {
                auto found_in_Lk = std::find(Lk.begin(), Lk.end(), sub_key) != Lk.end();
                if (!found_in_Lk){
                    is_frequent = false;
                    break;
                }
            }
            if (is_frequent) {
                auto already_in_frequents = std::find(frequents.begin(), frequents.end(), candidate_key) != frequents.end();
                if (!already_in_frequents){
                    frequents.emplace_back(candidate_key);
                }
            }
        }
        // prune now
        return frequents;
    }


} // anonymous namespace

FrequentItemSet apriori(const Database &T, int min_support){
    FrequentItemSet final_itemset;
    auto Ck = get_initial_itemset(T);
    int k = 1;


    while (!Ck.empty()){
        auto counts = compute_support(T, Ck);
        auto Lk = get_supported_itemsets(counts, min_support, &final_itemset);
        Ck = next_candidate_set(Lk);
        k++;
    }
    return final_itemset;
}