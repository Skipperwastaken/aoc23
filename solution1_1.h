#ifndef AOC23_SOLUTION1_1_H
#define AOC23_SOLUTION1_1_H
#include <iostream>
#include <fstream>
#include <string>

void solution() {
    std::ifstream file("inputs/1.txt");
    if(!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return;
    }
    char ch;
    std::string num;
    int sum = 0;
    while(file.good()) {
        file.get(ch);
        if(isdigit(ch)) {
            if (num.empty()) {
                (num+=ch)+=ch;
            } else {
                num[1] = ch;
            }
        } else if (ch == '\n') {
            sum += std::stoi(num);
            std::cout << "line value: " << num << '\n';
            num = "";
        }
    }
    if(ch != '\n') {
        sum += std::stoi(num);
        std::cout << "line value: " << num << '\n';
    }
    std::cout << "Sum: " << sum << std::endl;
}

#endif //AOC23_SOLUTION1_1_H
