#include "GasSupplySystem.h"

using namespace std;

bool CheckByKmMark(const Pipe& p, string param)
{
	return (p.GetKmMark().find(param) != string::npos);
}

bool ChekByStatus(const Pipe& p, int param)
{
	return (p.status == param);
}

bool CheckByDiameters(const Pipe& p, int param)
{
	return p.GetDiameter() == param;
}

bool CheckByTitle(const Station& cs, string param)
{
	return (cs.GetTitle().find(param) != string::npos);
}

bool CheckByWorkshops(const Station& cs, double param)
{
	return (cs.GetPercentUnused() >= param);
}

void GasSupplySystem::AddPipe()
{
	Pipe p;
	p.InitPipe();
	pipe_objects.insert({ p.GetId(), p });
}

Pipe GasSupplySystem::AddPipe(int diameter)
{
	Pipe p;
	p.InitPipe(diameter);
	pipe_objects.insert({ p.GetId(), p });
	return p;
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
		cout << "��� ����!\n\n";
}

void GasSupplySystem::ShowCS()
{
	if (ObjectsExist(cs_objects)) {
		for (const auto& [id, station] : cs_objects)
		{
			cout << station;
		}
	}
	else
		cout << "��� �������!\n\n";
}

void GasSupplySystem::ShortShowPipes()
{
	cout << "\n~��� �����~\n\n";
	for (const auto& [id, pipe] : pipe_objects) {
		cout << "ID " << id << ": \"" << pipe.GetKmMark()
			<< " �������: " << pipe.GetDiameter() << " mm, \""
			<< pipe.PrintStatus() << "\"\n";
	}
	cout << "\n";
}

void GasSupplySystem::ShortShowCS()
{
	cout << "\n~��� �������~\n\n";
	for (const auto& [id, station] : cs_objects) {
		cout << "ID " << id << ": \"" << station.GetTitle()
			<< "\", " << "������� �������������� �����: "
			<< station.GetPercentUnused() << " %\n";
	}
	cout << "\n";
}

void GasSupplySystem::ShowFoundPipes(unordered_set<int>& id_pipes)
{
	cout << "\n~��������� �����~\n\n";
	for (const auto& id : id_pipes) {
		cout << "ID " << id << ": \"" << pipe_objects.at(id).GetKmMark()
			<< " �������: " << pipe_objects.at(id).GetDiameter() << " mm, \""
			<< pipe_objects.at(id).PrintStatus() << "\"\n";
	}
	cout << "\n";
}

void GasSupplySystem::ShowFoundCS(unordered_set<int>& id_cs)
{
	cout << "\n~��������� �������~\n\n";
	for (const auto& id : id_cs) {
		cout << "ID " << id << ": \"" << cs_objects.at(id).GetTitle()
			<< "\", " << "������� �������������� �����: "
			<< cs_objects.at(id).GetPercentUnused() << " %\n";
	}
	cout << "\n";
}

void GasSupplySystem::ShowConnections()
{
	if (ObjectsExist(connections)) {
		for (auto& [id_pipe, edge] : connections) {
			cout << "ID_PIPE: " << id_pipe << " | " << "ID_STATION(OUT): "
				<< cs_objects.at(edge.id_out).GetId() << "   --->   ID_STATION(IN): "
				<< cs_objects.at(edge.id_in).GetId() << "\n";
		}
		cout << "\n";
	}
	else
		cout << "���������� ���!\n\n";
}

void GasSupplySystem::Save(string filename)
{
	ofstream fout;
	fout.open("Data/" + filename);

	if (fout) {
		fout << pipe_objects.size() << " "
			<< cs_objects.size() << " "
			<< connections.size() << "\n";
		for (const auto& [key, pipe] : pipe_objects)
			fout << pipe;

		for (const auto& [key, cs] : cs_objects)
			fout << cs;

		for (const auto& [key, edge] : connections) {
			fout << key << "\n";
			fout << edge.id_out << "\n";
			fout << edge.id_in << "\n";
		}

		cout << "������ ���������!" << "\n";
	}
	else
		cout << "������ � �������� �����!\n";

	fout.close();
}

void GasSupplySystem::Load(string filename)
{
	ifstream fin;
	fin.open("Data/" + filename);
	if (fin) {
		int num_pipe;
		int num_cs;
		int num_edges;
		int id_pipe;
		Edge edge(0, 0);
		Pipe p;
		Station cs;
		ClearSystem();

		fin >> num_pipe >> num_cs >> num_edges;
		for (int i = 0; i < num_pipe; i++) {
			fin >> p;
			pipe_objects.insert({ p.GetId(), p });
		}

		for (int i = 0; i < num_cs; i++) {
			fin >> cs;
			cs_objects.insert({ cs.GetId(), cs });
		};

		for (int i = 0; i < num_edges; i++) {
			fin >> id_pipe;
			fin >> edge.id_out;
			fin >> edge.id_in;
			connections.insert({ id_pipe, edge });
		}

		cout << "������ ���������!" << "\n";
	}
	else
		cout << "������ � �������� �����!\n";
}

void GasSupplySystem::ClearSystem()
{
	Pipe::ResetMaxID();
	Station::ResetMaxID();
	pipe_objects.clear();
	cs_objects.clear();
	connections.clear();
}

unordered_set<int> GasSupplySystem::SearchPipesByKmMark(string km_mark)
{
	return FindByFilter(pipe_objects, CheckByKmMark, km_mark);
}

unordered_set<int> GasSupplySystem::SearchPipesByStatus(int status)
{
	return FindByFilter(pipe_objects, ChekByStatus, status);
}

unordered_set<int> GasSupplySystem::SearchFreePipesByDiameters(int diameter)
{
	unordered_set<int> found_pipes;
	for (auto& id_pipe : FindByFilter(pipe_objects, CheckByDiameters, diameter)) {
		if (!connections.contains(id_pipe))
			found_pipes.insert(id_pipe);
	}

	return found_pipes;
}

unordered_set<int> GasSupplySystem::SearchPipesByIDs()
{
	return SelectByIDs(pipe_objects);
}

void GasSupplySystem::EditOnePipe(int id_pipe)
{
	if (pipe_objects.contains(id_pipe)) {
		pipe_objects.at(id_pipe).ChangeStatus();
		cout << "������ �������d!\n";
	}
	else
		cout << "����� � ��������� ID �� �������!\n";
}

void GasSupplySystem::ChangeStatusToOpposite(unordered_set<int>& id_pipes)
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
			pipe_objects.at(id).ChangeStatus();
		cout << "������� ���� ��������!\n";
	}
	else
		cout << "����� �� �������!\n";
}

void GasSupplySystem::ChangeStatusToRepair(unordered_set<int>& id_pipes)
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
			if (!pipe_objects.at(id).status)
				pipe_objects.at(id).ChangeStatus();
		cout << "������� ���� ��������!\n";
	}
	else
		cout << "����� �� �������!\n";
}

void GasSupplySystem::ChangeStatusToWork(unordered_set<int>& id_pipes)
{
	if (ObjectsExist(id_pipes))
	{
		for (auto& id : id_pipes)
			if (pipe_objects.at(id).status)
				pipe_objects.at(id).ChangeStatus();
		cout << "������� ���� ��������!\n";
	}
	else
		cout << "����� �� �������!\n";
}

void GasSupplySystem::EditAllPipes()
{
	for (auto& [id, pipe] : pipe_objects)
		pipe.ChangeStatus();
	cout << "������� ���� ���� ��������!\n";
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
	if (cs_objects.contains(id_cs)) {
		cout << "\"1\" - ���������,\"0\" - ���������: ";
		GetCorrectNumber(0, 1) ? cs_objects.at(id_cs).IncreaseActiveWS() :
			cs_objects.at(id_cs).DecreaseActiveWS();
		cout << "�������� ���������� ����� � ������\n";
	}
	else
		cout << "������� � ��������� ID �� �������!\n";
}

void GasSupplySystem::EditCSPackage(
	unordered_set<int>& id_cs, int action)
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
	cout << "�������� ���������� �������������� �����!\n";
}

void GasSupplySystem::DeletePipe(int id_pipe)
{
	if (pipe_objects.contains(id_pipe)) {
		pipe_objects.erase(id_pipe);
		connections.erase(id_pipe);
		cout << "����� �������\n";
	}
	else
		cout << "����� � ��������� ID �� �������!\n";
}

void GasSupplySystem::DeleteCS(int id_cs)
{
	if (cs_objects.contains(id_cs)) {
		cs_objects.erase(id_cs);
		vector<int> id_pipes;
		for (auto& [id, edge] : connections) {
			if (edge.id_in == id_cs || edge.id_out == id_cs)
				id_pipes.push_back(id);
		}

		for (int i = 0; i < id_pipes.size(); ++i)
			connections.erase(id_pipes[i]);

		cout << "������� �������\n";
	}
	else
		cout << "������� � ��������� ID �� �������!\n";
}

void GasSupplySystem::DeleteConnection(int id_pipe)
{
	if (connections.contains(id_pipe)) {
		connections.erase(id_pipe);
		cout << "���������� �������\n";
	}
	else
		cout << "��������� � �� �������!\n";
}

void GasSupplySystem::ConnectStations(int id_out, int id_in, int id_pipe)
{
	if (cs_objects.contains(id_out) && cs_objects.contains(id_in))
	{
		Edge edge(id_out, id_in);
		connections.insert({ id_pipe, edge });
		cout << "������� ���������!\n";
	}
	else
		cout << "������� � ���������� ID �� �������!\n";
}

vector<int> GasSupplySystem::TopologicalSorting()
{
	Graph graph(cs_objects, pipe_objects, connections);
	vector<int> result;
	result.reserve(cs_objects.size());
	if (graph.isDAG())
		result = graph.TopologicalSorting();
	return result;
}

unordered_map<int, double> GasSupplySystem::ShortestDistance(int id_cs)
{
	Graph graph(cs_objects, pipe_objects, connections);
	return graph.Dijkstra(id_cs);
}

bool GasSupplySystem::IsPipeConnected(int id_pipe)
{
	if (connections.contains(id_pipe))
		return true;
	return false;
}

bool GasSupplySystem::IsCSConnected(int id_cs)
{
	for (auto& [id, edge] : connections) {
		if (edge.id_in == id_cs || edge.id_out == id_cs)
			return true;
	}
	return false;
}

bool GasSupplySystem::PipeExist(int id_pipe)
{
	if (pipe_objects.contains(id_pipe))
		return true;
	return false;
}

bool GasSupplySystem::CSExist(int id_cs)
{
	if (cs_objects.contains(id_cs))
		return true;
	return false;
}

bool GasSupplySystem::IsPipeObjectsEmpty()
{
	if (pipe_objects.size() == 0) {
		cout << "� ������� ��� ����!\n";
		return true;
	}
	return false;
}

bool GasSupplySystem::IsCSObjectsEmpty()
{
	if (cs_objects.size() == 0) {
		cout << "� ������� ��� �������!\n";
		return true;
	}
	return false;
}