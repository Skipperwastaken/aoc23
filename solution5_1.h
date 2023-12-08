#ifndef AOC23_SOLUTION5_1_H
#define AOC23_SOLUTION5_1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <set>

class GardenRule {
public:
    unsigned long destination, source, length;

    GardenRule(const std::string &line) {
        std::stringstream ss;
        ss << line;
        ss >> destination >> source >> length;
    }

    [[nodiscard]] bool isInRange(unsigned long num) const {
        return num >= source && num <= source+length;
    }

    [[nodiscard]] unsigned long convert(unsigned long num) const {
        return num - source + destination;
    }
};

std::vector<unsigned long> getSeeds(std::string line) {
    std::vector<unsigned long> seeds;
    unsigned long inputLong;
    std::stringstream ss;

    line = line.substr(7);
    ss << line;
    while(ss >> inputLong) {
        seeds.push_back(inputLong);
    }
    return seeds;
}

unsigned long getLocation(const std::vector<std::vector<GardenRule>> &ruleMaps, unsigned long seed) {
    for (const auto &ruleMap: ruleMaps) {
        auto rule = std::ranges::find_if(ruleMap, [&seed](const GardenRule &rule) {return rule.isInRange(seed);});
        if (rule != ruleMap.end())
            seed = rule->convert(seed);
    }
    return seed;
}

void solution() {
    std::ifstream file("inputs/5.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);
    auto seeds = getSeeds(line);

    std::vector<std::vector<GardenRule>> ruleMaps;
    int currentMap = -1;

    while(getline(file, line)) {
        if (std::isdigit(line[0])) {
            ruleMaps[currentMap].emplace_back(line);
        } else if (std::isalpha(line[0])) {
            currentMap++;
            ruleMaps.emplace_back();
        }
    }

    auto locations = seeds | std::views::transform([&ruleMaps](auto &seed) {return getLocation(ruleMaps, seed);});
    auto smallestLocation = std::ranges::min(locations);

    std::cout << "Closest location: " << smallestLocation << std::endl;
}

#endif //AOC23_SOLUTION5_1_H
