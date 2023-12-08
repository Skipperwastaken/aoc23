#ifndef AOC23_SOLUTION6_2_H
#define AOC23_SOLUTION6_2_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <set>

void solution() {
    std::ifstream file("inputs/6.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::string timeStr;
    std::string distanceStr;
    std::string inputStr;
    file >> inputStr;
    while(file >> inputStr) {
        if (isdigit(inputStr[0]))
            timeStr+=inputStr;
        else
            break;
    }
    while(file >> inputStr) {
        distanceStr+=inputStr;
    }
    unsigned long long time = std::stoull(timeStr);
    unsigned long long distance = std::stoull(distanceStr);
    unsigned long long winCount = 0;
    for (unsigned long long j = 0; j < time; ++j)
        if ((time-j)*j > distance)
            ++winCount;
    std::cout << "Product: " << winCount << std::endl;
}

#endif //AOC23_SOLUTION6_2_H
