#ifndef AOC23_SOLUTION3_1_H
#define AOC23_SOLUTION3_1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>

std::vector<int> getSymbolsFromLine(const std::string &line) {
    std::vector<int> symbols;
    for (int i = 0; i < line.size(); ++i)
        if (line[i] != '.' && line[i] != '\n' && !isdigit(line[i])) {
            symbols.push_back(i);
        }
    return symbols;
}

bool isNextToSymbol(int startPos, int endPos, const std::vector<int> &symbols) {
    for (auto &symbolPos: symbols)
        if (symbolPos >= startPos - 1 && symbolPos <= endPos + 1 )
            return true;
    return false;
}

void solution() {
    std::ifstream file("inputs/3.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::vector<int> symbolsTop, symbolsMid, symbolsBot;
    std::string prevLine;
    int sum = 0;
    for( std::string line; getline( file, line ); )
    {
        symbolsTop = symbolsMid;
        symbolsMid = symbolsBot;
        symbolsBot = getSymbolsFromLine(line);

        std::string numString;
        int startNumPos;
        for (int i = 0; i < prevLine.size(); ++i) {
            if (isdigit(prevLine[i])) {
                if (numString.empty())
                    startNumPos = i;
                numString += prevLine[i];
            }
            if (!isdigit(prevLine[i]) || i == prevLine.size()-1){
                if (numString.empty())
                    continue;
                if (isNextToSymbol(startNumPos, i-1, symbolsTop) ||
                    isNextToSymbol(startNumPos, i-1, symbolsMid) ||
                    isNextToSymbol(startNumPos, i-1, symbolsBot)) {
                    sum += std::stoi(numString);
                }
                numString = "";
            }
        }

        prevLine = line;
    }
    symbolsTop = symbolsMid;
    symbolsMid = symbolsBot;

    std::string numString;
    int startNumPos;
    for (int i = 0; i < prevLine.size(); ++i) {
        if (isdigit(prevLine[i])) {
            if (numString.empty())
                startNumPos = i;
            numString += prevLine[i];
        } else {
            if (numString.empty())
                continue;
            if (isNextToSymbol(startNumPos, i, symbolsTop) ||
                isNextToSymbol(startNumPos, i, symbolsMid)) {
                sum += std::stoi(numString);
            }
            numString = "";
        }
    }
    std::cout << "Sum: " << sum << std::endl;
}

#endif //AOC23_SOLUTION3_1_H
