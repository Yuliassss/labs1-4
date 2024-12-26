#include "MainMenu.h"

using namespace std;

void MenuShowObjects(GasSupplySystem& gss)
{
	vector<string> menu = { "Показать трубы", "Показать станции", "Показать соединения", "Показать все" };
	const string menu_information[3] =
	{ "-----------------------------------------------\n"
	"\tИНФОРМАЦИЯ О ВСЕХ ТРУБАХ\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\tИНФОРМАЦИЯ О ВСЕХ СТАНЦИЯХ\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\tИНФОРМАЦИЯ О СОЕДИНЕНИЯХ\n"
	"-----------------------------------------------\n\n" };
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << menu_information[0];
		gss.ShowPipes();
		break;
	}
	case 2:
	{
		cout << menu_information[1];
		gss.ShowCS();
		break;
	}
	case 3:
	{
		cout << menu_information[2];
		gss.ShowConnections();
		break;
	}
	case 4:
	{
		cout << menu_information[0];
		gss.ShowPipes();
		cout << menu_information[1];
		gss.ShowCS();
		cout << menu_information[2];
		gss.ShowConnections();
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

void MenuSave(GasSupplySystem& gss)
{
	cout << "Введите имя файла: ";
	gss.Save(EnterLine());
}

void MenuLoad(GasSupplySystem& gss)
{
	cout << "Введите имя файла: ";
	gss.Load(EnterLine());
}

int EnterPipesID()
{
	cout << "Введите ID трубы: ";
	return GetCorrectNumber(1, INT_MAX);
}

bool FoundPipesExist(GasSupplySystem& gss, unordered_set<int> found_pipes)
{
	if (ObjectsExist(found_pipes)) {
		gss.ShowFoundPipes(found_pipes);
		return true;
	}
	else {
		cout << "Трубы не найдены!\n";
		return false;
	}
}

void MenuChangeStatusToOpposite(GasSupplySystem& gss, unordered_set<int>& id_pipes)
{
	cout << "Изменить статус (\"1\" - да, \"0\" - нет)?: ";
	if (GetCorrectNumber(0, 1))
		gss.ChangeStatusToOpposite(id_pipes);
}

void MenuEditPipeSubpackage(GasSupplySystem& gss,
	unordered_set<int>& id_pipes, bool for_status)
{
	if (!for_status) {
		vector<string> menu = {
		"Изменить статус на противоположный",
		"Изменить статус на \"В ремонте\"",
		"Изменить статус на \"В рабочем состоянии\"" };
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			gss.ChangeStatusToOpposite(id_pipes);
			break;
		}
		case 2:
		{
			gss.ChangeStatusToRepair(id_pipes);
			break;
		}
		case 3:
		{
			gss.ChangeStatusToWork(id_pipes);
			break;
		}
		default:
			break;
		}
	}
	else
		MenuChangeStatusToOpposite(gss, id_pipes);
}

void MenuSelectionPipesByIDs(GasSupplySystem& gss,
	unordered_set<int>& id_pipes, bool for_status)
{
	cout << "Выбрать трубы (\"1\" - да, \"0\" - нет)?: ";
	if (GetCorrectNumber(0, 1)) {
		unordered_set<int> found_pipes = SelectByIDs(id_pipes);
		if (FoundPipesExist(gss, found_pipes))
			if (found_pipes.size() > 1)
				MenuEditPipeSubpackage(gss, found_pipes, for_status);
			else
				MenuChangeStatusToOpposite(gss, found_pipes);
	}
	else
		MenuEditPipeSubpackage(gss, id_pipes, for_status);
}

void MenuEditPipePackage(GasSupplySystem& gss)
{
	unordered_set<int> found_pipes;
	bool for_status = false;
	bool with_select = true;
	vector<string> menu = {
		"Поиск по километровой метке", "Поиск по статусу",
		"Выбрать трубы" };
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "Введите километровую метку: ";
		found_pipes = gss.SearchPipesByKmMark(EnterLine());
		break;
	}
	case 2:
	{
		cout << "Введите статус (\"1\"-в ремонте, \"0\"-в рабочем состоянии): ";
		found_pipes = gss.SearchPipesByStatus(GetCorrectNumber(0, 1));
		for_status = true;
		break;
	}
	case 3:
	{
		found_pipes = gss.SearchPipesByIDs();
		with_select = false;
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}

	if (FoundPipesExist(gss, found_pipes)) {
		if (with_select && found_pipes.size() > 1)
			MenuSelectionPipesByIDs(gss, found_pipes, for_status);
		else
			MenuChangeStatusToOpposite(gss, found_pipes);
	}
}

void MenuEditPipes(GasSupplySystem& gss)
{
	if (!gss.IsPipeObjectsEmpty()) {
		vector<string> menu = { "Редактировать одну трубу",
			"Редактировать пакет труб", "Редактировать все трубы" };
		gss.ShortShowPipes();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			gss.EditOnePipe(EnterPipesID());
			break;
		}
		case 2:
		{
			MenuEditPipePackage(gss);
			break;
		}
		case 3:
		{
			gss.EditAllPipes();
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

int EnterStationsID()
{
	cout << "Введите ID станции: ";
	return GetCorrectNumber(0, INT_MAX);
}

bool FoundCSExist(GasSupplySystem& gss, unordered_set<int> found_stations)
{
	if (ObjectsExist(found_stations)) {
		gss.ShowFoundCS(found_stations);
		return true;
	}
	else {
		cout << "Станции не найдены!\n";
		return false;
	}
}

void MenuEditCSSubpackage(GasSupplySystem& gss,
	unordered_set<int>& id_stations)
{
	cout << "\"1\" - Увеличить,\"0\" - Уменьшить: ";
	gss.EditCSPackage(id_stations, GetCorrectNumber(0, 1));
}

void MenuSelectionCSByIDs(GasSupplySystem& gss,
	unordered_set<int>& id_stations)
{
	cout << "Выбрать станции (\"1\" - да, \"0\" - нет)?: ";
	if (GetCorrectNumber(0, 1)) {
		unordered_set<int> found_stations = SelectByIDs(id_stations);
		if (FoundCSExist(gss, found_stations))
			MenuEditCSSubpackage(gss, found_stations);
	}
	else
		MenuEditCSSubpackage(gss, id_stations);
}

void MenuEditCSPackage(GasSupplySystem& gss)
{
	unordered_set<int> found_stations;
	vector<string> menu = {
		"Поиск по названию", "Поиск по проценту неиспользуемых мастерских",
		"Выбрать станции" };
	bool with_select = true;
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "Введите название: ";
		found_stations = gss.SearchCSByTitle(EnterLine());
		break;
	}
	case 2:
	{
		cout << "Введите процент неиспользуемых мастерских: ";
		found_stations = gss.SearchCSByWorkshops(GetCorrectNumber(0.0, 100.0));
		break;
	}
	case 3:
	{
		found_stations = gss.SearchCSByIDs();
		with_select = false;
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}

	if (FoundCSExist(gss, found_stations)) {
		if (with_select && found_stations.size() > 1)
			MenuSelectionCSByIDs(gss, found_stations);
		else
			MenuEditCSSubpackage(gss, found_stations);
	}
}

void MenuEditCS(GasSupplySystem& gss)
{
	if (!gss.IsCSObjectsEmpty()) {
		vector<string> menu = { "Редактировать одну станцию",
			"Редактировать пакет станций", "Редактировать все станции" };
		gss.ShortShowCS();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			gss.EditOneCS(EnterStationsID());
			break;
		}
		case 2:
		{
			MenuEditCSPackage(gss);
			break;
		}
		case 3:
		{
			cout << "\"1\" - Увеличить,\"0\" - Уменьшить: ";
			gss.EditAllCS(GetCorrectNumber(0, 1));
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

void MenuDeletePipe(GasSupplySystem& gss)
{
	if (!gss.IsPipeObjectsEmpty()) {
		int id_pipe = EnterPipesID();
		if (gss.IsPipeConnected(id_pipe)) {
			cout << "Труба является частью графа.\n"
				<< "Хотите удалить? (\"1\" - да, \"0\" - нет): ";
			if (GetCorrectNumber(0, 1))
				gss.DeletePipe(id_pipe);
		}
		else
			gss.DeletePipe(id_pipe);
	}
}

void MenuDeleteCS(GasSupplySystem& gss)
{
	if (!gss.IsCSObjectsEmpty()) {
		int id_cs = EnterStationsID();
		if (gss.IsCSConnected(id_cs)) {
			cout << "Станция является частью графа.\n"
				<< "Хотите удалить? (\"1\" - да, \"0\" - нет): ";
			if (GetCorrectNumber(0, 1))
				gss.DeleteCS(id_cs);
		}
		else
			gss.DeleteCS(id_cs);
	}
}

void MenuDelete(GasSupplySystem& gss)
{
	vector<string> menu = { "Удалить трубу", "Удалить станцию", "Удалить соединение" };
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		MenuDeletePipe(gss);
		break;
	}
	case 2:
	{
		MenuDeleteCS(gss);
		break;
	}
	case 3:
	{
		gss.DeleteConnection(EnterPipesID());
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

void EnteringIDs(int& id_out, int& id_in)
{
	cout << "Введите ID первой станции: ";
	id_out = GetCorrectNumber(1, INT_MAX);
	cout << "Введите ID второй станции: ";
	id_in = GetCorrectNumber(1, INT_MAX);

	while (id_out == id_in) {
		cout << "ID совпадают! Введите ID снова\n";
		cout << "Введите ID первой станции: ";
		id_out = GetCorrectNumber(1, INT_MAX);
		cout << "Введите ID второй станции: ";
		id_in = GetCorrectNumber(1, INT_MAX);
	}
}

void MenuConnectStations(GasSupplySystem& gss)
{
	gss.ShortShowPipes();
	gss.ShortShowCS();
	gss.ShowConnections();
	int id_out;
	int id_in;
	EnteringIDs(id_out, id_in);

	if (gss.CSExist(id_in) && gss.CSExist(id_out)) {
		int diameter = Pipe::EnterCorrectDiameter();
		unordered_set<int> found_pipes = gss.SearchFreePipesByDiameters(diameter);

		if (ObjectsExist(found_pipes)) {
			gss.ShowFoundPipes(found_pipes);
			int id_pipe = EnterPipesID();
			if (found_pipes.contains(id_pipe))
				gss.ConnectStations(id_out, id_in, id_pipe);
			else
				cout << "Труба с этим ID не найдена среди найденных труб!\n";
		}
		else {
			cout << "Нет свободных труб с этим диаметром!\n" <<
				"Хотите создать (\"1\" - да, \"0\" - нет)?: ";
			if (GetCorrectNumber(0, 1)) {
				Pipe p = gss.AddPipe(diameter);
				gss.ConnectStations(id_out, id_in, p.GetId());
			}
		}
	}
}

void MenuTopologicalSorting(GasSupplySystem& gss)
{
	Graph graph = gss.InitGraph();
	if (graph.isDAG()) {
		vector<int> result = graph.TopologicalSorting();
		cout << "ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА: ";
		for (auto& id_cs : result)
			cout << id_cs << " ";
		cout << "\n";
	}
	else
		cout << "Топологическая сортировка невозможна. Есть циклы!\n";
}

void OutputDistance(unordered_map<int, double>& distances, int id_second_cs)
{
	if (distances.at(id_second_cs) == DBL_MAX)
		cout << "нет пути\n";
	else
		cout << distances.at(id_second_cs) << "\n";
}

void MenuShortestDistance(GasSupplySystem& gss)
{
	Graph graph = gss.InitGraph();
	cout << "Введите ID станции, от которой хотите искать: ";
	int id_first_cs = GetCorrectNumber(1, INT_MAX);
	if (gss.IsCSConnected(id_first_cs)) {
		unordered_map<int, double> found_distances = graph.Dijkstra(id_first_cs);
		cout << "Расстояние до одной станции или ко всем? (\"1\" - одна, \"0\" - все): ";
		if (GetCorrectNumber(0, 1)) {
			int id_second_cs = EnterStationsID();
			if (gss.IsCSConnected(id_second_cs)) {
				cout << "Расстояние до станции " << id_second_cs
					<< ": ";
				OutputDistance(found_distances, id_second_cs);
			}
		}
		else {
			for (auto& [id_second_cs, dist] : found_distances) {
				cout << "Расстояние до станции " << id_second_cs
					<< ": ";
				OutputDistance(found_distances, id_second_cs);
			}
		}
	}
	else
		cout << "Станция не в графе!\n";
}

void MenuMaxFlow(GasSupplySystem& gss)
{
	Graph graph = gss.InitGraph();
	int id_out, id_in;
	EnteringIDs(id_out, id_in);
	if (gss.IsCSConnected(id_out) && gss.IsPipeConnected(id_in))
	{
		cout << "Максимальный поток от станции " << id_out << " до "
			<< "станции " << id_in << ": " << graph.FordFulkerson(id_out, id_in) << "\n";
	}
}

void MenuNetwork(GasSupplySystem& gss)
{
	vector<string> menu = { "Соединить станции", "Топологическая сортировка",
	"Кратчайшее расстояние", "Максимальный поток" };
	if (!gss.IsCSObjectsEmpty() && !gss.IsPipeObjectsEmpty()) {
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			MenuConnectStations(gss);
			break;
		}
		case 2:
		{
			MenuTopologicalSorting(gss);
			break;
		}
		case 3:
		{
			MenuShortestDistance(gss);
			break;
		}
		case 4:
		{
			MenuMaxFlow(gss);
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
