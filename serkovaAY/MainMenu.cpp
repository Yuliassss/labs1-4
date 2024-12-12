#include "MainMenu.h"

using namespace std;

void MenuShowObjects(GasSupplySystem& gss)
{
	vector<string> menu = { "Показать трубы", "Показать станции", "Показать всё" };
	const string menu_information[2] =
	{ "-----------------------------------------------\n"
	"\tИНФОРМАЦИЯ О ВСЕХ ТРУБАХ\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\tИНФОРМАЦИЯ О ВСЕХ СТАНЦИЯХ\n"
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
		cout << menu_information[0];
		gss.ShowPipes();
		cout << menu_information[1];
		gss.ShowCS();
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

bool FoundPipesExist(GasSupplySystem& gss, unordered_set<int> found_pipes)
{
	if (ObjectsExist(found_pipes)) {
		cout << "\n~НАЙДЕННЫЕ ТРУБЫ~\n\n";
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

void MenuEditSelectedPipes(GasSupplySystem& gss,
	unordered_set<int>& id_pipes)
{
		vector<string> menu = {
		"Изменить статус на противоположный",
		"Измените статус на \"В ремонте\"",
		"Измените статус на \"В рабочем состоянии\"" };
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			gss.ChangeStatusToOpposite(id_pipes);
			break;
		}
		case 2:
		{
			//gss.ChangeStatusToOpposite(id_pipes);
			gss.ChangeStatus(id_pipes, false);
			break;
		}
		case 3:
		{
			//gss.ChangeStatusToOpposite(id_pipes);
			gss.ChangeStatus(id_pipes, true);
			break;
		}
		default:
			break;
		}
}

void MenuSelectionPipesByIDs(GasSupplySystem& gss,
	unordered_set<int>& id_pipes)
{
	cout << " (Редактировать трубы \"1\" - да, \"0\" - нет)?: ";
	if (GetCorrectNumber(0, 1)) {
		id_pipes = SelectByIDs(id_pipes);
	}
	if (FoundPipesExist(gss, id_pipes))
		MenuEditSelectedPipes(gss, id_pipes);
}

unordered_set<int> MenuEditPipePackage(GasSupplySystem& gss)
{
	unordered_set<int> found_pipes;
	vector<string> menu = {
		"Искать по имени", "Искать по статусу",
		"Искать трубу (id)" };

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "Введите имя: ";
		found_pipes = gss.SearchPipesByName(EnterLine());
		break;
	}
	case 2:
	{
		cout << "Введите статус (\"1\"-в ремонте, \"0\"-в рабочем состоянии): ";
		found_pipes = gss.SearchPipesByStatus(GetCorrectNumber(0, 1));
		break;
	}
	case 3:
	{
		found_pipes = gss.SearchPipesByIDs();
		MenuChangeStatusToOpposite(gss, found_pipes);
		return found_pipes; 
	}
	case 0:
	{
		return found_pipes; 
	}
	}

	if (FoundPipesExist(gss, found_pipes))
		MenuSelectionPipesByIDs(gss, found_pipes);

	return found_pipes; 
}

void MenuEditPipes(GasSupplySystem& gss)
{
	if (!gss.IsPipeObjectsEmpty()) {
		vector<string> menu = { "редактировать одну трубу",
			"Редактировать выбранные трубы", "Редактировать все трубы" };
		cout << "\n~ВСЕ ТРУБЫ~\n\n";
		gss.ShortShowPipes();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			cout << "Введиете ID трубы: ";
			gss.EditOnePipe(GetCorrectNumber(1, INT_MAX));
			break;
		}
		case 2:
		{
			MenuEditPipePackage(gss);
			//gss.ChangeStatus(MenuEditPipePackage(gss));
			break;
		}
		case 3:
		{
			auto all_id = gss.GetAllPipeIDs();
			MenuEditSelectedPipes(gss, all_id);
			cout << "Статусы всех труб изменены\n";
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
	else
		cout << "В системе нет труб!\n";}

bool FoundCSExist(GasSupplySystem& gss, unordered_set<int> found_stations)
{
	if (ObjectsExist(found_stations)) {
		cout << "\n~Найденные станции~\n\n";
		gss.ShowFoundCS(found_stations);
		return true;
	}
	else {
		cout << "Станции не найдены\n";
		return false;
	}
}

void MenuEditCSSubpackage(GasSupplySystem& gss,
	unordered_set<int>& id_stations)
{
	cout << "\"1\" - Увеличить ,\"0\" - Уменьшить: ";
	gss.EditCSPackage(id_stations, GetCorrectNumber(0, 1));
}

unordered_set<int> MenuSelectionCSByIDs(GasSupplySystem& gss, const unordered_set<int>& id_stations)
{
	cout << "Выберите объекты (\"1\" - да, \"0\" - нет)?: ";
	if (GetCorrectNumber(0, 1))
		return SelectByIDs(id_stations);
	return id_stations;
}

void MenuEditCSPackage(GasSupplySystem& gss)
{
	unordered_set<int> found_stations;
	vector<string> menu = {
		"Искать по названию", "Искать по проценту неиспользуемыхцехов",
		"Искать станцию(id)" };
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
		cout << "Введите процент неиспользуемых цехов: ";
		found_stations = gss.SearchCSByWorkshops(GetCorrectNumber(0.0, 100.0));
		break;
	}
	case 3:
	{
		found_stations = gss.SearchCSByIDs();
		MenuEditCSSubpackage(gss, found_stations);
		return;
	}
	case 0:
	{
		return;
	}
	}

	if (FoundCSExist(gss, found_stations))
		MenuEditCSSubpackage(gss, found_stations);

}

void MenuEditCS(GasSupplySystem& gss)
{
	if (!gss.IsCSObjectsEmpty()) {
		vector<string> menu = { "Редактировать одну станцию",
			"Редактировать выбранные станции", "Редактировать все станции" };
		cout << "\n~ВСЕ СТАНЦИИ~\n\n";
		gss.ShortShowCS();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			cout << "Введит ID станции: ";
			gss.EditOneCS(GetCorrectNumber(1, INT_MAX));
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
			cout << "Изменено количество неиспользуемых цехов!\n";
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
	else
		cout << "В системе нет станций!\n";
}



void MenuDeletePipePackage(GasSupplySystem& gss)
{
	unordered_set<int> found_pipes;
	vector<string> menu = {
		"Удалить трубу по имени",
		"Удалить трубу по статусу",
		"Удалить трубу по ID"
	};

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "Введите имя трубы для удаления: ";
		found_pipes = gss.SearchPipesByName(EnterLine());
		break;
	}
	case 2:
	{
		cout << "Введите статус трубы для удаления (\"1\"-в ремонте, \"0\"-в рабочем состоянии): ";
		found_pipes = gss.SearchPipesByStatus(GetCorrectNumber(0, 1));
		break;
	}
	case 3:
	{
		cout << "Введите ID трубы для удаления: ";
		int id = GetCorrectNumber(1, INT_MAX);
		found_pipes.insert(id);
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
		for (int pipe_id : found_pipes) {
			gss.DeletePipe(pipe_id);
		}
		cout << "Трубы успешно удалены." << endl;
	}
	else {
		cout << "Не найдено труб для удаления." << endl;
	}
}

void MenuDeleteCSPackage(GasSupplySystem& gss)
{
	unordered_set<int> found_stations;
	vector<string> menu = {
		"Удалить станцию по названию",
		"Удалить станцию по проценту неиспользуемых цехов",
		"Удалить станцию по ID"
	};

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "Введите название станции для удаления: ";
		found_stations = gss.SearchCSByTitle(EnterLine());
		break;
	}
	case 2:
	{
		cout << "Введите процент неиспользуемых цехов для удаления: ";
		found_stations = gss.SearchCSByWorkshops(GetCorrectNumber(0.0, 100.0));
		break;
	}
	case 3:
	{
		cout << "Введите ID станции для удаления: ";
		int id = GetCorrectNumber(1, INT_MAX);
		found_stations.insert(id);
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
		for (int station_id : found_stations) {
			gss.DeleteCS(station_id);
		}
		cout << "Станции успешно удалены." << endl;
	}
	else {
		cout << "Не найдено станций для удаления." << endl;
	}
}

void MenuDelete(GasSupplySystem& gss)
{
	vector<string> menu = { "Удалить трубу", "Удалить станцию", "Удалить выбранные трубы", "Удалить выбранные станции" };
	cout << "\n~ВСЕ ТРУБЫ~\n\n";
	gss.ShortShowPipes();
	cout << "\n~ВСЕ СТАНЦИИ~\n\n";
	gss.ShortShowCS();

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		if (!gss.IsPipeObjectsEmpty()) {
			cout << "Введите id трубы: ";
			gss.DeletePipe(GetCorrectNumber(1, INT_MAX));
		}
		else
			cout << "В системе нет труб!\n";
		break;
	}
	case 2:
	{
		if (!gss.IsCSObjectsEmpty()) {
			cout << "Введите id станции: ";
			gss.DeleteCS(GetCorrectNumber(1, INT_MAX));
		}
		else
			cout << "В системе нет станций!\n";
		break;
	}
	case 3:
	{
		MenuDeletePipePackage(gss);
		break;
	}
	case 4:
	{
		MenuDeleteCSPackage(gss);
		break;
	}
	default:
		break;
	}
}
