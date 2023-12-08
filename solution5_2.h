#ifndef AOC23_SOLUTION5_2_H
#define AOC23_SOLUTION5_2_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <set>

class SeedRange {
public:
    unsigned long start, length;
    SeedRange(unsigned long start, unsigned long length) : start(start), length(length) {}

    [[nodiscard]] unsigned long getEnd() const {
        return start + length;
    }
};

class GardenRule {
public:
    unsigned long destination, sourceStart, length;

    GardenRule(const std::string &line) {
        std::stringstream ss;
        ss << line;
        ss >> destination >> sourceStart >> length;
    }

    [[nodiscard]] unsigned long getSourceEnd() const {
        return sourceStart + length;
    }

    void convertSeed(SeedRange& seedRange) const {
        seedRange.start = seedRange.start - sourceStart + destination;
    }

    void applyRule(std::vector<SeedRange> &currentSeeds, std::vector<SeedRange> &nextSeeds) const {
        std::vector<SeedRange> remainingSeeds;
        remainingSeeds.reserve(currentSeeds.capacity());
        for (auto &currentSeed:currentSeeds) {
            if (currentSeed.getEnd() < sourceStart || currentSeed.start > getSourceEnd()) {
                remainingSeeds.push_back(currentSeed);
                continue;
            }
            if(currentSeed.start < sourceStart) {
                remainingSeeds.emplace_back(currentSeed.start, sourceStart-currentSeed.start);
                currentSeed.start = sourceStart;
            }
            if(currentSeed.getEnd() > getSourceEnd()) {
                remainingSeeds.emplace_back(getSourceEnd(), currentSeed.getEnd()-getSourceEnd());
                currentSeed.length = getSourceEnd()-currentSeed.start;
            }
            convertSeed(currentSeed);
            nextSeeds.push_back(currentSeed);
        }
        currentSeeds = remainingSeeds;
    }
};

std::vector<SeedRange> getSeeds(std::string line) {
    std::vector<SeedRange> seeds;
    unsigned long rangeStart, rangeLength;
    std::stringstream ss;

    line = line.substr(7);
    ss << line;
    while(ss >> rangeStart >> rangeLength) {
        seeds.emplace_back(rangeStart, rangeLength);
    }
    return seeds;
}

void solution() {
    std::ifstream file("inputs/5.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);
    auto currentSeeds = getSeeds(line);
    std::vector<SeedRange> nextSeeds;
    nextSeeds.reserve(currentSeeds.capacity());

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

    for (const auto &ruleMap: ruleMaps) {
        for (const auto &gardenRule:ruleMap) {
            gardenRule.applyRule(currentSeeds, nextSeeds);
        }
        currentSeeds.insert(currentSeeds.end(), nextSeeds.begin(), nextSeeds.end());
        nextSeeds = {};
        nextSeeds.reserve(currentSeeds.capacity());
    }

    auto smallestLocation = std::ranges::min(currentSeeds, [](const SeedRange &a, const SeedRange &b) {return a.start < b.start;});

    std::cout << "Closest location: " << smallestLocation.start << std::endl;
}

#endif //AOC23_SOLUTION5_2_H
