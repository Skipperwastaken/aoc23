#ifndef AOC23_SOLUTION8_1_H
#define AOC23_SOLUTION8_1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <map>

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
    }

    std::string current = "AAA";
    int steps = 0;
    int routeI = 0;
    while(current != "ZZZ") {
        if (routeI == route.size())
            routeI = 0;
        if (route[routeI] == 'L')
            current = nodeMap[current].first;
        else
            current = nodeMap[current].second;
        ++steps;
        ++routeI;
    }
    std::cout << "steps: " << steps << std::endl;
}

#endif //AOC23_SOLUTION8_1_H
