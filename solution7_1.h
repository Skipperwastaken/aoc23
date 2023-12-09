#ifndef AOC23_SOLUTION7_1_H
#define AOC23_SOLUTION7_1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <set>

class Hand{
    static int getCardValue(const char &ch) {
        if (isdigit(ch))
            return ch - '0';
        switch (ch) {
            case 'T':
                return 10;
            case 'J':
                return 11;
            case 'Q':
                return 12;
            case 'K':
                return 13;
            case 'A':
                return 14;
        }
    }
public:
    std::string cards;
    int type;
    int bet;

    Hand(const std::string &str, int _bet) {
        cards = str;
        bet = _bet;
        std::array<int, 4> sames{0, 0, 0, 0};
        for (int i = 0; i < str.size(); ++i) {
            int same = 0;
            for (int j = i+1; j < str.size(); ++j)
                if (str[i]==str[j])
                    ++same;
            if (same != 0) {
                ++sames[same-1];
            }
        }
        if (sames[3])
            type=6;
        else if (sames[2])
            type=5;
        else if (sames[1] && sames[0] == 2)
            type=4;
        else if (sames[1])
            type=3;
        else if(sames[0] == 2)
            type=2;
        else if (sames[0])
            type=1;
        else
            type=0;
    }

    bool operator<(const Hand &other) const {
        if (type == other.type) {
            for (int i = 0; i < cards.size(); ++i) {
                if (cards[i] == other.cards[i])
                    continue;
                return getCardValue(cards[i]) < getCardValue(other.cards[i]);
            }
        }
        return type < other.type;
    }
};

void solution() {
    std::ifstream file("inputs/7.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::vector<Hand> hands;

    std::string inputStr;
    int inputInt;
    while(file.good() && !file.eof()) {
        file >> inputStr >> inputInt;
        hands.emplace_back(inputStr, inputInt);
    }
    std::ranges::sort(hands, [](const Hand &a, const Hand &b){ return a < b;});
    int sum = 0, rank=1;
    std::ranges::for_each(hands, [&sum, &rank](const Hand &hand) {sum+=hand.bet*rank++;});
    std::cout << "Sum: " << sum << std::endl;
}

#endif //AOC23_SOLUTION7_1_H
