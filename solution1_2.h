#ifndef AOC23_SOLUTION1_2_H
#define AOC23_SOLUTION1_2_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>

const std::vector<std::string> numStrings = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const std::string digits = "123456789";

int stringToInt( const std::string &str) {
    return std::find(numStrings.begin(), numStrings.end(), str) - numStrings.begin() + 1;
}

std::pair<size_t, int> getFirstNumber(std::string &line) {
    auto view = numStrings
        | std::views::transform([&line](std::string const &numString) -> std::pair<size_t, int> {
            return {line.find(numString), stringToInt(numString)};
        })
        | std::views::filter([](auto const &pos) { return pos.first != std::string::npos; });
    if(view.empty())
        return {-1, 0};
    return std::ranges::min(view, [](auto const &a, auto const &b) {
        return a.first < b.first;
    });
}

std::pair<size_t, int> getLastNumber(std::string &line) {
    auto view = numStrings
        | std::views::transform([&line](std::string const &numString) -> std::pair<size_t, int> {
            return {line.rfind(numString), stringToInt(numString)};
        })
        | std::views::filter([](auto const &pos) { return pos.first != std::string::npos; });
    if(view.empty())
        return {-1, 0};
    return std::ranges::max(view, [](auto const &a, auto const &b) {
        return a.first < b.first;
    });
}

void solution() {
    std::ifstream file("inputs/1.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        int lineValue = 0;
        auto posOfFirstNum = line.find_first_of(digits);
        auto posOfLastNum = line.find_last_of(digits);
        auto firstStringNumber = getFirstNumber(line);
        auto lastStringNumber = getLastNumber(line);
        if (firstStringNumber.first != -1 && firstStringNumber.first < posOfFirstNum) {
            lineValue += firstStringNumber.second;
        } else {
            lineValue += line[posOfFirstNum] - '0';
        }
        lineValue *= 10;
        if (lastStringNumber.first != -1 && lastStringNumber.first > posOfLastNum) {
            lineValue += lastStringNumber.second;
        } else {
            lineValue += line[posOfLastNum] - '0';
        }
        sum += lineValue;
    }
    std::cout << "Sum: " << sum << std::endl;
}

#endif //AOC23_SOLUTION1_2_H
