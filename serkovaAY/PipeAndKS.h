#pragma once
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pipe.h"
#include "KS.h"
#include "Addition.h"



using namespace std;

class PipeAndKS
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
	std::unordered_map<int, KS>& GetCS();
private:
	std::unordered_map<int, Pipe> pipe_objects;
	std::unordered_map<int, KS> ks_objects;
	};



template<typename T>
inline void PipeAndKS::Add(std::unordered_map<int, T>& objects)
{
	T object;
	std::cin >> object;
	objects.insert({ object.GetId(), object });
}

template<typename T>
inline void PipeAndKS::Show(const std::unordered_map<int, T>& objects)
{
	if (objects.size() != 0) {
		for (const auto& [key, object] : objects)
		{
			std::cout << object;
		}
	}
	else
		std::cout << "Нет объектов\n\n";
}






