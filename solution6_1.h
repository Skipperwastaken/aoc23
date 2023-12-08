#ifndef AOC23_SOLUTION6_1_H
#define AOC23_SOLUTION6_1_H
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
    std::vector<int> times;
    std::vector<int> distances;
    std::string inputStr;
    file >> inputStr;
    while(file >> inputStr) {
        if (isdigit(inputStr[0]))
            times.push_back(std::stoi(inputStr));
        else
            break;
    }
    while(file >> inputStr) {
        distances.push_back(std::stoi(inputStr));
    }
    int product = 1;
    for (int i = 0; i < times.size(); ++i) {
        int winCount = 0;
        for (int j = 0; j < times[i]; ++j) {
            if ((times[i]-j)*j > distances[i])
                ++winCount;
        }
        product *= winCount;
    }
    std::cout << "Product: " << product << std::endl;
}

#endif //AOC23_SOLUTION6_1_H
