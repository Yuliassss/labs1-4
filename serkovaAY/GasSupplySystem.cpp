#include "GasSupplySystem.h"

using namespace std;

void GasSupplySystem::ShowObjects()
{
	Menu(2);
	const string menu_array[2] =
	{ "-----------------------------------------------\n"
	"\tINFORMATION ABOUT ALL PIPES\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\tINFORMATION ABOUT ALL CS\n"
	"-----------------------------------------------\n\n" };
	switch (GetCorrectNumber(0, 3))
	{
	case 1:
	{
		cout << menu_array[0];
		Show(pipe_objects);
		break;
	}
	case 2:
	{
		cout << menu_array[1];
		Show(cs_objects);
		break;
	}
	case 3:
	{
		cout << menu_array[0];
		Show(pipe_objects);

		cout << menu_array[1];
		Show(cs_objects);
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void GasSupplySystem::Save()
{
	cout << "Enter the file name: ";

	ofstream fout;
	fout.open("Data/" + EnterLine());

	if (fout) {
		fout << pipe_objects.size() << " "
			<< cs_objects.size() << "\n";
		for (const auto& [key, pipe] : pipe_objects) {
			fout << pipe;
		}
		for (const auto& [key, cs] : cs_objects) {
			fout << cs;
		}
		cout << "Data is saved!" << "\n";
	}
	else {
		cout << "Error in the opening file!\n";
	}

	fout.close();
}

void GasSupplySystem::Load()
{
	cout << "Enter the file name: ";
	ifstream fin;
	fin.open("Data/" + EnterLine());
	if (fin) {
		int num_pipe;
		int num_cs;
		Pipe p;
		Station cs;
		ClearSystem();

		fin >> num_pipe >> num_cs;
		for (int i = 0; i < num_pipe; i++) {
			fin >> p;
			pipe_objects.insert({ p.GetId(), p });
		}

		for (int i = 0; i < num_cs; i++) {
			fin >> cs;
			cs_objects.insert({ cs.GetId(), cs });
		};
		cout << "Data is load!" << "\n";
	}
	else
	{
		cout << "Error in the opening file!\n";
	}
}

void GasSupplySystem::ClearSystem()
{
	Pipe::ResetMaxID();
	Station::ResetMaxID();
	pipe_objects.clear();
	cs_objects.clear();
}

bool CheckByKmMark(const Pipe& p, string param)
{
	return (p.GetKmMark().find(param) != string::npos);
}

bool ChekByStatus(const Pipe& p, int param)
{
	return (p.status == param);
}

bool CheckByTitle(const Station& cs, string param)
{
	return (cs.GetTitle().find(param) != string::npos);
}

bool CheckByWorkshop(const Station& cs, double param)
{
	return (cs.GetPercentUnused() >= param);
}

void ShortShowPipes(const std::unordered_map<int, Pipe>& pipe_objects) {
	cout << "\n~ALL PIPES~\n\n";
	if (pipe_objects.size() != 0) {
		for (const auto& [id, pipe] : pipe_objects) {
			cout << "ID " << id << ": \"" << pipe.GetKmMark()
				<< "\", " << pipe.PrintStatus() << "\n";
		}
	}
	else
		cout << "Not pipes!\n";
}

void ShowFoundPipes(unordered_map<int, Pipe>& pipe_objects,
	unordered_set<int>& id_set) {
	cout << "\n\t~FOUND PIPES~\n\n";
	for (auto& id : id_set) {
		cout << "ID " << id << ": \""
			<< pipe_objects.at(id).GetKmMark() << "\", "
			<< pipe_objects.at(id).PrintStatus() << "\n";
	}
	cout << "\n";
}

void EditOnePipe(unordered_map<int, Pipe>& pipe_objects) {
	ShortShowPipes(pipe_objects);
	cout << "\nEnter ID of pipe: ";
	int id = GetCorrectNumber(0, INT_MAX);
	if (pipe_objects.count(id) != 0) {
		pipe_objects.at(id).ChangeStatus();
		cout << "Status was changed!\n";
	}
	else
		cout << "Pipe with this ID has not found!\n";
}

void EditPipes(unordered_map<int, Pipe>& pipe_objects,
	unordered_set<int>& id_set)
{
	ShowFoundPipes(pipe_objects, id_set);
	Menu(5);
	switch (GetCorrectNumber(0, 3))
	{
	case 1:
	{
		for (auto& id : id_set) {
			pipe_objects.at(id).ChangeStatus();
		}
		cout << "Status was changed!\n";
		break;
	}
	case 2:
	{
		for (auto& id : id_set) {
			if (!pipe_objects.at(id).status)
				pipe_objects.at(id).ChangeStatus();
		}
		cout << "Status was changed!\n";
		break;
	}
	case 3:
	{
		for (auto& id : id_set) {
			if (pipe_objects.at(id).status)
				pipe_objects.at(id).ChangeStatus();
		}
		cout << "Status was changed!\n";
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void EditPipeByStatus(unordered_map<int, Pipe>& pipe_objects,
	unordered_set<int>& id_set)
{
	ShowFoundPipes(pipe_objects, id_set);
	cout << "Change status? (0 - No, 1 - Yes): ";
	if (GetCorrectNumber(0, 1)) {
		for (auto& id : id_set) {
			pipe_objects.at(id).ChangeStatus();
		}
		cout << "Status was changed!\n";
	}
}

void EditAllPipes(unordered_map<int, Pipe>& pipe_objects)
{
	unordered_set<int> id_set;
	for (auto& [id, pipe] : pipe_objects) {
		id_set.insert(id);
	}
	if (CheckByEmptySet(id_set))
		EditPipes(pipe_objects, id_set);
}

void EditPackagePipe(unordered_map<int, Pipe>& pipe_objects) {
	Menu(4);
	switch (GetCorrectNumber(0, 4))
	{
	case 1:
	{
		ShortShowPipes(pipe_objects);
		cout << "\nEnter the kilometer mark: ";
		unordered_set id_set = FindByFilter(pipe_objects, CheckByKmMark, EnterLine());
		if (CheckByEmptySet(id_set))
			EditPipes(pipe_objects, id_set);
		break;
	}
	case 2:
	{
		ShortShowPipes(pipe_objects);
		cout << "\nStatus (\"0\"-in working condition, \"1\"-in repair): ";
		unordered_set id_set = FindByFilter(pipe_objects, ChekByStatus, GetCorrectNumber(0, 1));
		if (CheckByEmptySet(id_set))
			EditPipeByStatus(pipe_objects, id_set);
		break;
	}
	case 3:
	{
		ShortShowPipes(pipe_objects);
		unordered_set<int> id_set = SelectByIDs(pipe_objects);
		if (CheckByEmptySet(id_set))
			EditPipes(pipe_objects, id_set);
		break;
	}
	case 4:
	{
		EditAllPipes(pipe_objects);
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void DeletePipe(unordered_map<int, Pipe>& pipe_objects) {
	ShortShowPipes(pipe_objects);
	cout << "\nEnter ID of pipe: ";
	int id = GetCorrectNumber(0, INT_MAX);
	if (pipe_objects.count(id) != 0) {
		pipe_objects.erase(id);
		cout << "Pipe was deleted!\n";
	}
	else
		cout << "Pipe with this ID has not found\n";
}

void GasSupplySystem::EditPipe()
{
	if (CheckByEmptySystem(pipe_objects)) {
		Menu(3);
		switch (GetCorrectNumber(0, 3))
		{
		case 1:
		{
			EditOnePipe(pipe_objects);
			break;
		}
		case 2:
		{
			EditPackagePipe(pipe_objects);
			break;
		}
		case 3:
		{
			DeletePipe(pipe_objects);
			break;
		}
		case 0:
		{
			break;
		}
		default:
			break;
		}
	}
}

void ShortShowStations(const std::unordered_map<int, Station>& cs_objects) {
	cout << "\n~ALL STATIONS~\n\n";
	if (cs_objects.size() != 0) {
		for (const auto& [id, station] : cs_objects) {
			cout << "ID " << id << ": \"" << station.GetTitle()
				<< "\", " << "Percent of unused workshops: "
				<< station.GetPercentUnused() << " %\n";
		}
	}
	else
		cout << "Not stations!\n";
}

void ShowFoundStations(unordered_map<int, Station>& cs_objects,
	unordered_set<int>& id_set) {
	cout << "\n\t~FOUND STATIONS~\n\n";
	for (auto& id : id_set) {
		cout << "ID " << id << ": \""
			<< cs_objects.at(id).GetTitle() << "\", "
			<< "Percent of unused workshops: "
			<< cs_objects.at(id).GetPercentUnused() << "% \n";
	}
	cout << "\n";
}

void EditOneStation(unordered_map<int, Station>& cs_objects) {
	ShortShowStations(cs_objects);
	cout << "\nEnter ID of station: ";
	int id = GetCorrectNumber(0, INT_MAX);
	if (cs_objects.count(id) != 0) {
		cout << "\"0\" - Decrease,\"1\" - Increase: ";
		GetCorrectNumber(0, 1) ? cs_objects.at(id).IncreaseActiveWS() :
			cs_objects.at(id).DecreaseActiveWS();
		cout << "The number of active workshops is changed\n";
	}
	else
		cout << "Station with this ID has not found!\n";
}

void EditStations(unordered_map<int, Station>& cs_objects,
	unordered_set<int>& id_set)
{
	ShowFoundStations(cs_objects, id_set);
	Menu(8);
	switch (GetCorrectNumber(0, 3))
	{
	case 1:
	{
		for (auto& id : id_set) {
			cs_objects.at(id).IncreaseActiveWS();
		}
		cout << "The number of active workshops is changed\n";
		break;
	}
	case 2:
	{
		for (auto& id : id_set) {
			cs_objects.at(id).DecreaseActiveWS();
		}
		cout << "The number of active workshops is changed\n";
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void EditAllStations(unordered_map<int, Station>& cs_objects)
{
	unordered_set<int> id_set;
	for (auto& [id, stations] : cs_objects) {
		id_set.insert(id);
	}
	if (CheckByEmptySet(id_set))
		EditStations(cs_objects, id_set);
}

void EditPackageStation(unordered_map<int, Station>& cs_objects)
{
	Menu(7);
	switch (GetCorrectNumber(0, 4))
	{
	case 1:
	{
		ShortShowStations(cs_objects);
		cout << "\nEnter the title: ";
		unordered_set id_set = FindByFilter(cs_objects, CheckByTitle, EnterLine());
		if (CheckByEmptySet(id_set))
			EditStations(cs_objects, id_set);
		break;
	}
	case 2:
	{
		ShortShowStations(cs_objects);
		cout << "\nPercent of unused workshops: ";
		unordered_set id_set = FindByFilter(cs_objects, CheckByWorkshop, GetCorrectNumber(0.0, 100.0));
		if (CheckByEmptySet(id_set))
			EditStations(cs_objects, id_set);
		break;
	}
	case 3:
	{
		ShortShowStations(cs_objects);
		unordered_set<int> id_set = SelectByIDs(cs_objects);
		if (CheckByEmptySet(id_set))
			EditStations(cs_objects, id_set);
		break;
	}
	case 4:
	{
		EditAllStations(cs_objects);
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void DeleteStation(unordered_map<int, Station>& cs_objects) {
	ShortShowStations(cs_objects);
	cout << "\nEnter ID of station: ";
	int id = GetCorrectNumber(0, INT_MAX);
	if (cs_objects.count(id) != 0) {
		cs_objects.erase(id);
		cout << "Statoin was deleted!\n";
	}
	else
		cout << "Station with this ID has not found\n";
}

void GasSupplySystem::EditCS()
{
	if (CheckByEmptySystem(cs_objects))
	{
		Menu(6);
		switch (GetCorrectNumber(0, 3))
		{
		case 1:
		{
			EditOneStation(cs_objects);
			break;
		}
		case 2:
		{
			EditPackageStation(cs_objects);
			break;
		}
		case 3:
		{
			DeleteStation(cs_objects);
			break;
		}
		case 0:
		{

			break;
		}
		default:
			break;
		}
	}
}

std::unordered_map<int, Pipe>& GasSupplySystem::GetPipes()
{
	return pipe_objects;
}

std::unordered_map<int, Station>& GasSupplySystem::GetCS()
{
	return cs_objects;
}