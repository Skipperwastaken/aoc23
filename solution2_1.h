#ifndef AOC23_SOLUTION2_1_H
#define AOC23_SOLUTION2_1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>

class Game {
public:
    int red, green, blue, id;
    Game(): red(0), green(0), blue(0) { }
    friend std::istream &operator>>(std::istream &input, Game &game) {
        std::string inputString;
        int inputInt;
        input >> inputString;
        if (inputString != "Game") {
            std::cerr << "Expected: 'Game', got: " << inputString << std::endl;
            return input;
        }
        input >> game.id;
        input >> inputString;
        if (inputString != ":") {
            std::cerr << "Expected: ':', got: " << inputString << std::endl;
            return input;
        }
        while ((input.peek()!='\n') && input.good()) {
            input >> inputInt >> inputString;
            if (inputString[0] == 'r')
                game.red = std::max(game.red, inputInt);
            if (inputString[0] == 'g')
                game.green = std::max(game.green, inputInt);
            if (inputString[0] == 'b')
                game.blue = std::max(game.blue, inputInt);
        }
        return input;
    }
};

void solution() {
    std::ifstream file("inputs/2.txt");
    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    std::vector<Game> games;
    while (file.good() && !file.eof()) {
        Game inputGame;
        file >> inputGame;
        games.push_back(inputGame);
    }
    const int maxReds = 12, maxGreens = 13, maxBlues = 14;
    auto impossibleGames = games
        | std::views::filter([](const Game &game) {
            return !(game.red > maxReds || game.green > maxGreens || game.blue > maxBlues);
        });
    int summedIdOfImpossibleGames = std::ranges::fold_left(impossibleGames, 0, [](int acc, const Game &curr) {
        return acc + curr.id;
    });
    std::cout << "Sum of ids: " << summedIdOfImpossibleGames << std::endl;
}

#endif //AOC23_SOLUTION2_1_H
