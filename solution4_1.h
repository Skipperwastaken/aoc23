#ifndef AOC23_SOLUTION4_1_H
#define AOC23_SOLUTION4_1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <set>

void solution() {
    std::ifstream file("inputs/4.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    int sum = 0;
    std::string inputString;
    int inputInt;
    for (std::string line; getline(file, line);) {
        int points = 0;
        std::set<int> winningNumbers;
        std::stringstream ss;
        ss << line;
        ss >> inputString >> inputString;
        for (int i = 0; i < 10; ++i) {
            ss >> inputInt;
            winningNumbers.insert(inputInt);
        }
        ss >> inputString;
        for (int i = 0; i < 25; ++i) {
            ss >> inputInt;
            if (winningNumbers.contains(inputInt)) {
                points = points == 0 ? 1 : points*2;
            }
        }
        sum+=points;
    }

    std::cout << "Sum: " << sum << std::endl;
}

#endif //AOC23_SOLUTION4_1_H
