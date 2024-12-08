#pragma once
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pipe.h"
#include "KS.h"
#include "Addition.h"


class GasSupplySystem
{
public:
	template <typename T>
	void Add(std::unordered_map<int, T>& objects);

	template <typename T>
	void Show(const std::unordered_map<int, T>& objects);
	void ShowObjects();

	void Save();
	void Load();
	void ClearSystem();
	void EditPipe();
	void EditCS();


	std::unordered_map<int, Pipe>& GetPipes();
	std::unordered_map<int, Station>& GetCS();


private:
	std::unordered_map<int, Pipe> pipe_objects;
	std::unordered_map<int, Station> cs_objects;

};

template<typename T>
inline void GasSupplySystem::Add(std::unordered_map<int, T>& objects)
{
	T object;
	std::cin >> object;
	objects.insert({ object.GetId(), object });
}

template<typename T>
inline void GasSupplySystem::Show(const std::unordered_map<int, T>& objects)
{
	if (objects.size() != 0) {
		for (const auto& [key, object] : objects)
		{
			std::cout << object;
		}
	}
	else
		std::cout << "Not objects!\n\n";
}