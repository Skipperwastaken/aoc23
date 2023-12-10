#ifndef AOC23_SOLUTION10_2_H
#define AOC23_SOLUTION10_2_H

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
    y--;
    do {
        current = step(current, map[y][x]);
        switch (map[y][x]) {
            case '|':
                map[y][x] = '*'; break;
            case 'L':
            case 'J':
                map[y][x] = 'U'; break;
            case '7':
            case 'F':
                map[y][x] = 'D'; break;
            case '-':
                map[y][x] = '='; break;
        }

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
    } while (map[y][x] != 'S');
    map[y][x] = 'U';

    int enclosedArea = 0;

    for (int i = 0; i < 140; ++i) {
        bool inside = false;
        char lastSideWaysWall = '0';
        for (int j = 0; j < 140; ++j) {
            if (map[i][j] == '*')
                inside = !inside;
            else if (map[i][j] == 'U') {
                if (lastSideWaysWall == 'U')
                    lastSideWaysWall = '0';
                else if (lastSideWaysWall == 'D') {
                    lastSideWaysWall = '0';
                    inside = !inside;
                } else {
                    lastSideWaysWall = 'U';
                }
            }
            else if (map[i][j] == 'D') {
                if (lastSideWaysWall == 'D')
                    lastSideWaysWall = '0';
                else if (lastSideWaysWall == 'U') {
                    lastSideWaysWall = '0';
                    inside = !inside;
                } else {
                    lastSideWaysWall = 'D';
                }
            }
            else if (inside && map[i][j] != '=')
                ++enclosedArea;
        }
    }

    std::cout << "enclosedArea: " << enclosedArea << std::endl;
}

#endif //AOC23_SOLUTION10_2_H
