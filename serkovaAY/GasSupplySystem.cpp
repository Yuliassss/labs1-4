#include "GasSupplySystem.h"

using namespace std;

void GasSupplySystem::AddPipe()
{
	Pipe p;
	cin >> p;
	pipe_objects.insert({ p.GetId(), p });
}

void GasSupplySystem::AddCS()
{
	Station cs;
	cin >> cs;
	cs_objects.insert({ cs.GetId(), cs });
}

void GasSupplySystem::ShowPipes()
{
	if (ObjectsExist(pipe_objects)) {
		for (const auto& [id, pipe] : pipe_objects)
		{
			cout << pipe;
		}
	}
	else
		cout << "Труб нет!\n\n";
}

void GasSupplySystem::ShowCS()
{
	if (cs_objects.size() != 0) {
		for (const auto& [id, station] : cs_objects)
		{
			cout << station;
		}
	}
	else
		cout << "Станций нет!\n\n";
}

void GasSupplySystem::ShortShowPipes()
{
	for (const auto& [id, pipe] : pipe_objects) {
		cout << "ID " << id << ": \"" << pipe.GetName()
			<< "\", " << pipe.PrintStatus() << "\n";
	}
	cout << "\n";
}

void GasSupplySystem::ShortShowCS()
{
	for (const auto& [id, station] : cs_objects) {
		cout << "ID " << id << ": \"" << station.GetTitle()
			<< "\", " << "Процент неиспользуемых цехов: "
			<< station.GetPercentUnused() << " %\n";
	}
	cout << "\n";
}

void GasSupplySystem::ShowFoundPipes(unordered_set<int>& id_pipes)
{
	for (const auto& id : id_pipes) {
		if (pipe_objects.contains(id))
			cout << pipe_objects.at(id) << endl;
	}
	cout << "\n";
}

void GasSupplySystem::ShowFoundCS(unordered_set<int>& id_cs)
{
	for (const auto& id : id_cs) {
		cout << "ID " << id << ": \"" << cs_objects.at(id).GetTitle()
			<< "\", " << "Процент неиспользуемых цехов: "
			<< cs_objects.at(id).GetPercentUnused() << " %\n";
	}
	cout << "\n";
}

void GasSupplySystem::Save(string filename)
{
	ofstream fout;
	fout.open("Data/" + filename);

	if (fout) {
		fout << pipe_objects.size() << " "
			<< cs_objects.size() << "\n";
		for (const auto& [key, pipe] : pipe_objects) {
			fout << pipe;
		}
		for (const auto& [key, cs] : cs_objects) {
			fout << cs;
		}
		cout << "Данные сохранены!" << "\n";
	}
	else
		cout << "Ошибка открытия файла!\n";

	fout.close();
}

void GasSupplySystem::Load(string filename)
{
	ifstream fin;
	fin.open("Data/" + filename);
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
		cout << "Данные загружены!" << "\n";
	}
	else
		cout << "Ошибка открытия файла!\n";
}

void GasSupplySystem::ClearSystem()
{
	Pipe::ResetMaxID();
	Station::ResetMaxID();
	pipe_objects.clear();
	cs_objects.clear();
}

bool CheckByName(const Pipe& p, string param)
{
	return (p.GetName().find(param) != string::npos);
}

bool ChekByStatus(const Pipe& p, int param)
{
	return (p.status == param);
}

bool CheckByTitle(const Station& cs, string param)
{
	return (cs.GetTitle().find(param) != string::npos);
}

bool CheckByWorkshops(const Station& cs, double param)
{
	return (cs.GetPercentUnused() >= param);
}

unordered_set<int> GasSupplySystem::SearchPipesByName(string name)
{
	return FindByFilter(pipe_objects, CheckByName, name);
}

unordered_set<int> GasSupplySystem::SearchPipesByStatus(int status)
{
	return FindByFilter(pipe_objects, ChekByStatus, status);
}

unordered_set<int> GasSupplySystem::SearchPipesByIDs()
{
	return SelectByIDs(pipe_objects);
}


std::unordered_set<int> GasSupplySystem::GetAllPipeIDs()
{
	return GetAllIDs(pipe_objects);
}

std::unordered_set<int> GasSupplySystem::GetAllCSIDs()
{
	return GetAllIDs(cs_objects);
}

void GasSupplySystem::EditOnePipe(int id_pipe)
{
	if (pipe_objects.contains(id_pipe)) {
		pipe_objects.at(id_pipe).ToggleStatus();
		cout << "Статус изменен!\n";
	}
	else
		cout << "Труба с введенным ID не найдена!\n";
}

void GasSupplySystem::ChangeStatusToOpposite(unordered_set<int>& id_pipes)
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
			if (pipe_objects.contains(id))
				pipe_objects.at(id).ToggleStatus();
		cout << "Статусы изменены!\n";
	}
	else
		cout << "Трубы не найдены!\n";
}

void GasSupplySystem::ChangeStatus(unordered_set<int>& id_pipes, bool new_status)
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
		{
			auto it = pipe_objects.find(id);
			if (it != pipe_objects.end())
				it->second.ChangeStatus(new_status);
		}
		cout << "Статусы изменены!\n";
	}
	else
		cout << "Трубы не найдены!\n";
}


void GasSupplySystem::EditAllPipes()
{
	for (auto& [id, pipe] : pipe_objects)
		pipe.ToggleStatus();
}

unordered_set<int> GasSupplySystem::SearchCSByTitle(std::string title)
{
	return FindByFilter(cs_objects, CheckByTitle, title);
}

unordered_set<int> GasSupplySystem::SearchCSByWorkshops(double percent)
{
	return FindByFilter(cs_objects, CheckByWorkshops, percent);
}

unordered_set<int> GasSupplySystem::SearchCSByIDs()
{
	return SelectByIDs(cs_objects);
}

void GasSupplySystem::EditOneCS(int id_cs)
{
	if (!cs_objects.contains(id_cs)) {
		cout << "\"1\" - Увеличить,\"0\" - Уменьшить: ";
		GetCorrectNumber(0, 1) ? cs_objects.at(id_cs).IncreaseActiveWS() :
			cs_objects.at(id_cs).DecreaseActiveWS();
		cout << "Колличество цехов в работе изменено\n";// << (action ? "increased" : "decreased") << "\n";
	}
	else
		cout << "Станция с указанным ID не найдена!\n";
}

void GasSupplySystem::EditCSPackage(
	std::unordered_set<int>& id_cs, int action)
{
	for (auto& id : id_cs) {
		action ? cs_objects.at(id).IncreaseActiveWS() :
			cs_objects.at(id).DecreaseActiveWS();
	}

}

void GasSupplySystem::EditAllCS(int action)
{
	for (auto& [id, cs] : cs_objects)
		action ? cs.IncreaseActiveWS() : cs.DecreaseActiveWS();
}

void GasSupplySystem::DeletePipe(int id_pipe)
{
	if (pipe_objects.contains(id_pipe)) {
		pipe_objects.erase(id_pipe);
		cout << "труба удалена\n";
	}
	else
		cout << "Труба с введенным ID не найдена!\n";
}

void GasSupplySystem::DeleteCS(int id_cs)
{
	if (cs_objects.contains(id_cs)) {
		cs_objects.erase(id_cs);
		cout << "Станция удалена\n";
	}
	else
		cout << "Станция с указанным ID не найдена!\n";
}

bool GasSupplySystem::IsPipeObjectsEmpty()
{
	if (pipe_objects.size() == 0)
		return true;
	return false;
}

bool GasSupplySystem::IsCSObjectsEmpty()
{
	if (cs_objects.size() == 0)
		return true;
	return false;
}