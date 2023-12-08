#ifndef AOC23_SOLUTION4_2_H
#define AOC23_SOLUTION4_2_H

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
    std::vector<int> cards;
    int lineNumber = 0;
    std::string inputString;
    int inputInt;
    for (std::string line; getline(file, line);) {
        if (cards.size() == lineNumber)
            cards.push_back(1);
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
                points++;
            }
        }
        for (int i = lineNumber+1; i < lineNumber+1+points; ++i) {
            if (cards.size() == i)
                cards.push_back(1);
            cards[i]+=cards[lineNumber];
        }
        lineNumber++;
    }

    auto actualCards = cards
            | std::views::take(lineNumber);

    auto numOfCards = std::ranges::fold_left(actualCards, 0, std::plus());

    std::cout << "Number of scratchcards: " << numOfCards << std::endl;
}
#endif //AOC23_SOLUTION4_2_H
