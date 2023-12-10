#ifndef AOC23_SOLUTION9_2_H
#define AOC23_SOLUTION9_2_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <map>
#include <numeric>

std::vector<int> stringToNumVec(const std::string &line) {
    std::stringstream ss;
    ss << line;
    int inputInt;
    std::vector<int> output;
    while(ss.good() && !ss.eof()) {
        ss >> inputInt;
        output.push_back(inputInt);
    }
    return output;
}

int getFirstNumber(const std::vector<int> &nums) {
    std::vector<int> nextNums;
    bool allZeroes = true;
    for (int i = 1; i < nums.size(); ++i) {
        nextNums.push_back(nums[i]-nums[i-1]);
        if (nextNums.back() != 0)
            allZeroes = false;
    }
    if (allZeroes)
        return nums.front();
    return nums.front() - getFirstNumber(nextNums);
}

void solution() {
    std::ifstream file("inputs/9.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::string line;
    int sum = 0;
    for(; getline( file, line );) {

        sum += getFirstNumber(stringToNumVec(line));
    }

    std::cout << "sum: " << sum << std::endl;
}

#endif //AOC23_SOLUTION9_2_H
