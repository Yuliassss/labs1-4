#pragma once
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pipe.h"
#include "Station.h"
#include "Addition.h"


class GasSupplySystem
{
public:
	void AddPipe();
	void AddCS();

	void ShowPipes();
	void ShowCS();
	void ShortShowPipes();
	void ShortShowCS();
	void ShowFoundPipes(std::unordered_set<int>& id_pipes);
	void ShowFoundCS(std::unordered_set<int>& id_cs);

	void Save(std::string filename);
	void Load(std::string filename);
	void ClearSystem();

	std::unordered_set<int> SearchPipesByName(std::string name);
	std::unordered_set<int> SearchPipesByStatus(int status);
	std::unordered_set<int> SearchPipesByIDs();

	template <typename T>
	std::unordered_set<int> GetAllIDs(std::unordered_map<int, T> objs)
	{
		std::unordered_set<int> res;
		for (auto& [id, obj] : objs)
			res.emplace(id);
		return res;
	}
	std::unordered_set<int> GetAllPipeIDs();
	std::unordered_set<int> GetAllCSIDs();

	void EditOnePipe(int id_pipe);
	void ChangeStatusToOpposite(std::unordered_set<int>& id_pipes);
	void ChangeStatus(std::unordered_set<int>& id_pipes, bool new_status);
	void EditAllPipes();

	std::unordered_set<int> SearchCSByTitle(std::string title);
	std::unordered_set<int> SearchCSByWorkshops(double percent);
	std::unordered_set<int> SearchCSByIDs();

	void EditOneCS(int id_cs);
	void EditCSPackage(std::unordered_set<int>& id_cs, int action);
	void EditAllCS(int action);

	void DeletePipe(int id_pipe);
	void DeleteCS(int id_cs);

	bool IsPipeObjectsEmpty();
	bool IsCSObjectsEmpty();

private:
	std::unordered_map<int, Pipe> pipe_objects;
	std::unordered_map<int, Station> cs_objects;
};
