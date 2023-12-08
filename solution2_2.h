#ifndef AOC23_SOLUTION2_2_H
#define AOC23_SOLUTION2_2_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>

class Game2 {
public:
    int red, green, blue, id;
    Game2(): red(0), green(0), blue(0) { }

    [[nodiscard]] int getPower() const {
        return red*green*blue;
    }

    friend std::istream &operator>>(std::istream &input, Game2 &game) {
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
    std::vector<Game2> games;
    while (file.good() && !file.eof()) {
        Game2 inputGame;
        file >> inputGame;
        games.push_back(inputGame);
    }
    auto powers = games
            | std::views::transform([](const Game2 &game) {
                return game.getPower();
            });
    int sumOfPowers = std::ranges::fold_left(powers, 0, std::plus());
    std::cout << "Sum of ids: " << sumOfPowers << std::endl;
}

#endif //AOC23_SOLUTION2_2_H
