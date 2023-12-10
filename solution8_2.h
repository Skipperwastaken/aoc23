#ifndef AOC23_SOLUTION8_2_H
#define AOC23_SOLUTION8_2_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <map>
#include <numeric>

typedef std::pair<std::string, std::string> Node;
typedef std::map<std::string, Node> NodeMap;

void solution() {
    std::ifstream file("inputs/8.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::string route;
    std::string line;
    getline( file, route );
    getline( file, line );
    NodeMap nodeMap;
    std::vector<std::string> startPositions;
    for(; getline( file, line );) {
        std::string start = line.substr(0, 3);
        std::string left = line.substr(7, 3);
        std::string right = line.substr(12, 3);
        nodeMap.emplace(start, Node(left, right));
        if (start[2] == 'A')
            startPositions.push_back(start);
    }

    std::vector<unsigned long long> stepsToCircle;
    for (const auto& startPosition : startPositions) {
        auto current = startPosition;
        unsigned long long steps = 0;
        int routeI = 0;
        do {
            if (routeI == route.size())
                routeI = 0;
            if (route[routeI] == 'L')
                current = nodeMap[current].first;
            else
                current = nodeMap[current].second;
            ++steps;
            ++routeI;
        } while(current[2] != 'Z');
        stepsToCircle.push_back(steps);
    }

    auto lcm = std::ranges::fold_left(stepsToCircle, 1, [](auto a, auto b) {
        return std::lcm(a, b);
    });


    std::cout << "steps: " << lcm << std::endl;
}

#endif //AOC23_SOLUTION8_2_H
