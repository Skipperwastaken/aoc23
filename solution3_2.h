#ifndef AOC23_SOLUTION3_2_H
#define AOC23_SOLUTION3_2_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>

class GearNumber {
public:
    int startPos, endPos, number;

    GearNumber(int s, int e, int n) : startPos(s), endPos(e), number(n) {}
};

std::vector<GearNumber> getGearNumbersFromLine(const std::string &line) {
    std::vector<GearNumber> symbols;
    std::string numString;
    int startNumPos;
    for (int i = 0; i < line.size(); ++i) {
        if (isdigit(line[i])) {
            if (numString.empty())
                startNumPos = i;
            numString += line[i];
        }
        if (!isdigit(line[i]) || i == line.size() - 1) {
            if (numString.empty())
                continue;
            symbols.emplace_back(startNumPos, i - 1, std::stoi(numString));
            numString = "";
        }
    }
    return symbols;
}

void setAdjacentGearNumbers(
        std::pair<int, int> &gearNumbers,
        const std::vector<GearNumber> &lineOfGearNumbers,
        int pos) {
    if (gearNumbers.first == -2)
        return;
    for (const auto &gearNumber : lineOfGearNumbers) {
        if (gearNumber.startPos-1 <= pos && gearNumber.endPos+1 >= pos) {
            if (gearNumbers.first == -1)
                gearNumbers.first = gearNumber.number;
            else if (gearNumbers.second == -1)
                gearNumbers.second = gearNumber.number;
            else
                gearNumbers.first = gearNumbers.second = -2;
        }
    }
}

void solution() {
    std::ifstream file("inputs/3.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::vector<GearNumber> gearNumbersTop, gearNumbersMid, gearNumbersBot;
    std::string prevLine;
    int sum = 0;
    for (std::string line; getline(file, line);) {
        gearNumbersTop = gearNumbersMid;
        gearNumbersMid = gearNumbersBot;
        gearNumbersBot = getGearNumbersFromLine(line);

        for (int i = 0; i < prevLine.size(); ++i) {
            if (prevLine[i] == '*') {
                std::pair<int, int> gearNumbers{-1, -1};
                setAdjacentGearNumbers(gearNumbers, gearNumbersTop, i);
                setAdjacentGearNumbers(gearNumbers, gearNumbersMid, i);
                setAdjacentGearNumbers(gearNumbers, gearNumbersBot, i);
                if (gearNumbers.first > -1 && gearNumbers.second > -1) {
                    sum += gearNumbers.first * gearNumbers.second;
                }

            }
        }

        prevLine = line;
    }
    gearNumbersTop = gearNumbersMid;
    gearNumbersMid = gearNumbersBot;

    for (int i = 0; i < prevLine.size(); ++i) {
        if (prevLine[i] == '*') {
            std::pair<int, int> gearNumbers{-1, -1};
            setAdjacentGearNumbers(gearNumbers, gearNumbersTop, i);
            setAdjacentGearNumbers(gearNumbers, gearNumbersMid, i);
            setAdjacentGearNumbers(gearNumbers, gearNumbersBot, i);
            if (gearNumbers.first > -1 && gearNumbers.second > -1) {
                sum += gearNumbers.first * gearNumbers.second;
            }

        }
    }

    std::cout << "Sum: " << sum << std::endl;
}

#endif //AOC23_SOLUTION3_2_H
