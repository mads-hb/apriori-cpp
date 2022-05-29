#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <chrono>

#include "database.hpp"
#include "apriori.hpp"

std::vector<int> parse_line(std::string line){
    std::string delim = " ";  // Split by spaces.
    std::vector<int> res;
    auto start = 0U;
    auto end = line.find(delim);
    while (end != std::string::npos) {
        int item = std::stoi(line.substr(start, end - start));
        res.push_back(item);
        start = end + delim.length();
        end = line.find(delim, start);
    }
    return res;
}

Database read_data(std::filesystem::path path){
    std::ifstream data_file;
    std::string line;

    std::vector<std::vector<int>> res;
    data_file.open(path);
    if (data_file.is_open()){
        while ( getline (data_file,line)) {
            auto line_vector = parse_line(line);
            res.push_back(line_vector);
        }
        data_file.close();
        return res;
    } else {
        throw std::runtime_error("File does not exist.");
    }
}

int main() {
    std::filesystem::path path("../data/retail.txt");
    auto database = read_data(path);

    auto tic = std::chrono::high_resolution_clock::now();
    auto res = apriori(database, 2000);
    auto toc = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic);
    std::cout << "Running took " << duration.count() * 1e-3 << "seconds." << std::endl;
    std::cout << "All item sets and their support:" << std::endl;
    for (auto const &item_set: res){
        for (auto const &key: item_set.first){
            std::cout << key << ", ";
        }
         std::cout << ": " << item_set.second << std::endl;
    }
    return 0;
}
