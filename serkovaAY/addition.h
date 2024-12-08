#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>


template <typename T1, typename T2>
using Filter = bool(*)(T1& object, T2 param);

template <typename T1, typename T2>
std::unordered_set<int> FindByFilter(std::unordered_map<int,
    T1>& map, Filter<const T1&, T2> f, T2 param)
{
    std::unordered_set<int> result_set;
    for (auto& [key, object] : map)
    {
        if (f(object, param))
            result_set.insert(key);
    }
    return result_set;
}

template <typename T>
T GetCorrectNumber(T min, T max) {
    T x;
    while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x < min || x > max) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "¬ведите число (" << min << "-" << max << "): ";
    };
    return x;
}



template <typename T>
std::unordered_set<int> SelectByIDs(std::unordered_map<int, T>& objects)
{
    std::unordered_set<int> id_set;
    std::string line = "";
    int id;
    std::cout << "Enter id (\"#\" - stop): ";
    while (std::getline(std::cin, line) and line != "#") {
        std::istringstream s{ line };
        while (!s.eof())
        {
            s >> id;
            if (!s.fail() and objects.count(id) != 0)
                id_set.insert(id);
            else {
                s.clear();
                s.ignore(10000, ' ');
            }
        }
    }
    return id_set;
}
template <typename T>
bool CheckByEmptySystem(const std::unordered_map<int, T>& pipe_objects)
{
    if (pipe_objects.size() == 0) {
        std::cout << "Not objects!\n";
        return false;
    }
    return true;
}
bool CheckByEmptySet(const std::unordered_set<int>& id_set);

std::string EnterLine();
void Menu(int param);



