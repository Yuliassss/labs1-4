#pragma once
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "Pipe.h"
#include "KS.h"

using namespace std;

class PipeAndKS
{
public:
	template <typename T> void Add(std::unordered_map<int, T>& map);
	template <typename T> void Show(std::unordered_map<int, T>& map);
	void Save();
	void Load();

	std::unordered_map<int, Pipe>& GetPipe();
	std::unordered_map<int, KS>& GetKS();

private:
	std::unordered_map<int, Pipe> pipe_map;
	std::unordered_map<int, KS> ks_map;



};

template<typename T>
inline void PipeAndKS::Add(std::unordered_map<int, T>& map)
{
	T object;
	std::cin >> object;
	map.insert({ object.GetId(), object });
}
template<typename T>
inline void PipeAndKS::Show(std::unordered_map<int, T>& map)
{
	for (const auto& [key, object] : map)
	{
		std::cout << object << std::endl;
	}
}

