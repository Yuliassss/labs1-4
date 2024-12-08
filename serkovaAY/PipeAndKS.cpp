#include "PipeAndKS.h"

using namespace std;

void PipeAndKS::ShowObjects()
{
	Menu(2);
	const string menu_array[2] =
	{ "-----------------------------------------------\n"
	"\tИНФОРМАЦИЯ О ВСЕХ ТРУБАХ\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\tИНФОРМАЦИЯ О ВВСЕХ СТАНЦИЯ\n"
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
		Show(ks_objects);
		break;
	}
	case 3:
	{
		cout << menu_array[0];
		Show(pipe_objects);
		cout << menu_array[1];
		Show(ks_objects);
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

void PipeAndKS::Save()
{
	cout << " ";
	ofstream fout;
	fout.open(EnterLine());

	if (fout) {
		fout << pipe_objects.size() << " "
			<< ks_objects.size() << "\n";
		for (const auto& [key, pipe] : pipe_objects) {
			fout << pipe;
		}
		for (const auto& [key, cs] : ks_objects) {
			fout << cs;
		}
		cout << "" << "Данные сохранены\n";
	}
	else {
		cout << "Ошибка открытия файла\n";
	}

	fout.close();
}



void PipeAndKS::Load()
{
	string filename;
	cout << "Введите название файла: ";
	cin >> ws;
	getline(cin, filename);

	ifstream fin;
	fin.open(filename);
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




































void PipeAndKS::AddPipe()//
{
	Pipe p;
	p.InitPipe();
	pipe_objects.insert({ p.GetId(), p });
}

void GasSupplySystem::AddCS()
{
	KS ks;
	cin >> ks;
	ks_objects.insert({ ks.GetId(), ks });
}


void PipeAndKS::ShowPipes()
{
	if (ObjectsExist(pipe_objects)) {
		for (const auto& [id, pipe] : pipe_objects)
		{
			cout << pipe;
		}
	}
	else
		cout << "Not pipes!\n\n";
}


void PipeAndKS::ShowCS()
{
	if (ObjectsExist(ks_objects)) {
		for (const auto& [id, ks] : ks_objects)
		{
			cout << ks;
		}
	}
	else
		cout << "Not staions!\n\n";
}

void PipeAndKS::ShortShowPipes()//
{
	cout << "\n~ALL PIPES~\n\n";
	for (const auto& [id, pipe] : pipe_objects) {
		cout << "ID " << id << ": \"" << pipe.GetKmMark()
			<< ", D: " << pipe.GetDiameter() << " mm, \""
			<< pipe.PrintStatus() << "\"\n";
	}
	cout << "\n";
}

void PipeAndKS::ShortShowCS()//
{
	cout << "\n~ALL STATIONS~\n\n";
	for (const auto& [id, station] : ks_objects) {
		cout << "ID " << id << ": \"" << station.GetName()
			<< "\", " << "Percent of unused workshops: "
			<< station.GetPercentUnused() << " %\n";
	}
	cout << "\n";
}



void PipeAndKS::ShowFoundPipes(unordered_set<int>& id_pipes)//
{
	cout << "\n~FOUND PIPES~\n\n";
	for (const auto& id : id_pipes) {
		cout << "ID " << id << ": \"" << pipe_objects.at(id).GetKmMark()
			<< ", D: " << pipe_objects.at(id).GetDiameter() << " mm, \""
			<< pipe_objects.at(id).PrintStatus() << "\"\n";
	}
	cout << "\n";
}

void PipeAndKS::ShowFoundCS(unordered_set<int>& id_ks)//
{
	cout << "\n~FOUND STATIONS~\n\n";
	for (const auto& id : id_ks) {
		cout << "ID " << id << ": \"" << ks_objects.at(id).GetTitle()
			<< "\", " << "Percent of unused workshops: "
			<< ks_objects.at(id).GetPercentUnused() << " %\n";
	}
	cout << "\n";
}











void PipeAndKS::Save(string filename)
{
	ofstream fout;
	fout.open(filename);
	if (fout) {
		fout << pipe_objects.size() << " "
			<< cs_objects.size() << " " << "\n";
		for (const auto& [key, p] : pipe_objects) {
			fout << pipe;
		}
		for (const auto& [key, ks] : ks_objects) {
			fout << cs;
		}

		cout << "Объекты сохранены" << "\n";
	}
	else {
		cout << "Ошибка открытия файла" << "\n";
	}
	fout.close();
}

void PipeAndKS::Load(string filename)
{/*
	string filename;
	cout << "Введите имя файла ";
	cin >> ws;
	getline(cin, filename);*/
	ifstream fin;

	fin.open(filename);
	if (fin) {
		int num_pipe, num_ks;
		int temp_id_p = 0, temp_id_ks = 0;
		Pipe p;
		KS ks;

		fin >> num_pipe >> num_ks;
		for (int i = 0; i < num_pipe; i++) {
			fin >> p;
			pipe_objects.insert({ p.GetId(), p });
		}
		for (int i = 0; i < num_ks; i++) {
			fin >> ks;
			cs_objects.insert({ cs.GetId(), cs });
		}

		cout << "Объекты загружены" << "\n";
	
	}
	else
	{
		cout << "Ошибка открытия файла" << "\n";
	}
	fin.close();
}

unordered_set<int> PipeAndKSm::SearchPipesByName(string name)//
{
	return FindByFilter(pipe_objects, CheckByName, name);
}

unordered_set<int> PipeAndKS::SearchPipesByStatus(int status)//
{
	return FindByFilter(pipe_objects, ChekByStatus, status);
}


unordered_set<int> PipeAndKS::SearchFreePipesByDiameters(int diameter)//
{
	unordered_set<int> found_pipes;
	for (auto& id_pipe : FindByFilter(pipe_objects, CheckByDiameters, diameter)) {
		if (!connections.contains(id_pipe))
			found_pipes.insert(id_pipe);
	}

	return found_pipes;
}

unordered_set<int> PipeAndKS::SearchPipesByIDs()//
{
	return SelectByIDs(pipe_objects);
}

void PipeAndKS::EditOnePipe(int id_pipe)//
{
	if (pipe_objects.contains(id_pipe)) {
		pipe_objects.at(id_pipe).ChangeStatus();
		cout << "Статус изменен\n";
	}
	else
		cout << "Труба с введенным ID не найдена\n";
}

void PipeAndKS::ChangeStatusToOpposite(unordered_set<int>& id_pipes)//
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
			pipe_objects.at(id).ChangeStatus();
		cout << "Изменены статусы труб\n";
	}
	else
		cout << "Трубы не найдены\n";
}

void PipeAndKS::ChangeStatusToRepair(unordered_set<int>& id_pipes)//
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
			if (!pipe_objects.at(id).status)
				pipe_objects.at(id).ChangeStatus();
		cout << "Изменены статусы труб\n";
	}
	else
		cout << "Трубы не найдены\n";
}

void PipeAndKS::ChangeStatusToWork(unordered_set<int>& id_pipes)//
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
			if (pipe_objects.at(id).status)
				pipe_objects.at(id).ChangeStatus();
		cout <<  "Изменены статусы труб\n";
	}
	else
		cout << "Трубы не найдены\n";
}

void PipeAndKS::EditAllPipes()//
{
	for (auto& [id, pipe] : pipe_objects)
		pipe.ChangeStatus();
	cout << "Изменены статусы всех труб\n";
}

unordered_set<int> PipeAndKS::SearchKSByName(std::string name)//
{
	return FindByFilter(cs_objects, CheckByTitle, name);
}

unordered_set<int> PipeAndKS::SearchKSByWorkshops(double percent)
{
	return FindByFilter(cs_objects, CheckByWorkshops, percent);
}

unordered_set<int> PipeAndKS::SearchKSByIDs()
{
	return SelectByIDs(cs_objects);
}

void PipeAndKS::EditOneKS(int id_cs)
{
	if (cs_objects.contains(id_cs)) {
		cout << "\"1\" - Increase,\"0\" - Decrease: ";
		GetCorrectNumber(0, 1) ? cs_objects.at(id_cs).IncreaseActiveWS() :
			cs_objects.at(id_cs).DecreaseActiveWS();
		cout << "Number of WS is changed\n";
	}
	else
		cout << "Station with entered ID not found!\n";
}

void PipeAndKS::EditKSPackage(
	unordered_set<int>& id_cs, int action)
{
	for (auto& id : id_cs) {
		action ? cs_objects.at(id).IncreaseActiveWS() :
			cs_objects.at(id).DecreaseActiveWS();
	}

}

void PipeAndKS::EditAllKS(int action)
{
	for (auto& [id, cs] : cs_objects)
		action ? cs.IncreaseActiveWS() : cs.DecreaseActiveWS();
	cout << "The number of unused workshops is changed!\n";
}
