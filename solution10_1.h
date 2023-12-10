#ifndef AOC23_SOLUTION10_1_H
#define AOC23_SOLUTION10_1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <map>
#include <cstring>

enum direction {
    N, E, S, W
};

direction step(direction current, char pipe) {
    switch (current) {
        case N:
            switch (pipe) {
                case '|': return N;
                case '7': return W;
                case 'F': return E;
            }
        case E:
            switch (pipe) {
                case '-': return E;
                case 'J': return N;
                case '7': return S;
            }
        case S:
            switch (pipe) {
                case '|': return S;
                case 'L': return E;
                case 'J': return W;
            }
        case W:
            switch (pipe) {
                case '-': return W;
                case 'L': return N;
                case 'F': return S;
            }
    }
}

void solution() {
    std::ifstream file("inputs/10.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    char map[140][140];
    int x, y;
    std::string line;
    for(int i = 0; getline( file, line );++i) {
        for (int j = 0; j < line.size(); ++j) {
            if (line[j] == 'S') {
                x = j;
                y = i;
            }
        }
        std::strncpy(map[i], line.c_str(), 140);
    }
    direction current = N;
    int steps = 1;
    y--;
    do {
        current = step(current, map[y][x]);
        switch (current) {
            case N:
                --y; break;
            case E:
                ++x; break;
            case S:
                ++y; break;
            case W:
                --x; break;
        }
        ++steps;
    } while (map[y][x] != 'S');

    std::cout << "sum: " << steps/2 << std::endl;
}


#endif //AOC23_SOLUTION10_1_H
