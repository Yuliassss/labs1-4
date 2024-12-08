#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

template <typename T>
T get_correct_number(T min, T max) {
    T x;
    while ((std::cin >> x).fail() || x < min || x > max) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "¬ведите число (" << min << "-" << max << "): ";
    };
    return x;
}


int ChooseActionMenu(std::vector<std::string>& menu, bool with_exit);