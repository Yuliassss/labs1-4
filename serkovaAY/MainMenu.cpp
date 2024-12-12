#include "MainMenu.h"

using namespace std;

void MenuShowObjects(GasSupplySystem& gss)
{
	vector<string> menu = { "�������� �����", "�������� �������", "�������� ��" };
	const string menu_information[2] =
	{ "-----------------------------------------------\n"
	"\t���������� � ���� ������\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\t���������� � ���� ��������\n"
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
	cout << "������� ��� �����: ";
	gss.Save(EnterLine());
}

void MenuLoad(GasSupplySystem& gss)
{
	cout << "������� ��� �����: ";
	gss.Load(EnterLine());
}

bool FoundPipesExist(GasSupplySystem& gss, unordered_set<int> found_pipes)
{
	if (ObjectsExist(found_pipes)) {
		cout << "\n~��������� �����~\n\n";
		gss.ShowFoundPipes(found_pipes);
		return true;
	}
	else {
		cout << "����� �� �������!\n";
		return false;
	}
}

void MenuChangeStatusToOpposite(GasSupplySystem& gss, unordered_set<int>& id_pipes)
{
	cout << "�������� ������ (\"1\" - ��, \"0\" - ���)?: ";
	if (GetCorrectNumber(0, 1))
		gss.ChangeStatusToOpposite(id_pipes);
}

void MenuEditSelectedPipes(GasSupplySystem& gss,
	unordered_set<int>& id_pipes)
{
		vector<string> menu = {
		"�������� ������ �� ���������������",
		"�������� ������ �� \"� �������\"",
		"�������� ������ �� \"� ������� ���������\"" };
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
	cout << " (������������� ����� \"1\" - ��, \"0\" - ���)?: ";
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
		"������ �� �����", "������ �� �������",
		"������ ����� (id)" };

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "������� ���: ";
		found_pipes = gss.SearchPipesByName(EnterLine());
		break;
	}
	case 2:
	{
		cout << "������� ������ (\"1\"-� �������, \"0\"-� ������� ���������): ";
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
		vector<string> menu = { "������������� ���� �����",
			"������������� ��������� �����", "������������� ��� �����" };
		cout << "\n~��� �����~\n\n";
		gss.ShortShowPipes();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			cout << "�������� ID �����: ";
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
			cout << "������� ���� ���� ��������\n";
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
	else
		cout << "� ������� ��� ����!\n";}

bool FoundCSExist(GasSupplySystem& gss, unordered_set<int> found_stations)
{
	if (ObjectsExist(found_stations)) {
		cout << "\n~��������� �������~\n\n";
		gss.ShowFoundCS(found_stations);
		return true;
	}
	else {
		cout << "������� �� �������\n";
		return false;
	}
}

void MenuEditCSSubpackage(GasSupplySystem& gss,
	unordered_set<int>& id_stations)
{
	cout << "\"1\" - ��������� ,\"0\" - ���������: ";
	gss.EditCSPackage(id_stations, GetCorrectNumber(0, 1));
}

unordered_set<int> MenuSelectionCSByIDs(GasSupplySystem& gss, const unordered_set<int>& id_stations)
{
	cout << "�������� ������� (\"1\" - ��, \"0\" - ���)?: ";
	if (GetCorrectNumber(0, 1))
		return SelectByIDs(id_stations);
	return id_stations;
}

void MenuEditCSPackage(GasSupplySystem& gss)
{
	unordered_set<int> found_stations;
	vector<string> menu = {
		"������ �� ��������", "������ �� �������� �������������������",
		"������ �������(id)" };
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "������� ��������: ";
		found_stations = gss.SearchCSByTitle(EnterLine());
		break;
	}
	case 2:
	{
		cout << "������� ������� �������������� �����: ";
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
		vector<string> menu = { "������������� ���� �������",
			"������������� ��������� �������", "������������� ��� �������" };
		cout << "\n~��� �������~\n\n";
		gss.ShortShowCS();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			cout << "������ ID �������: ";
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

			cout << "\"1\" - ���������,\"0\" - ���������: ";
			gss.EditAllCS(GetCorrectNumber(0, 1));
			cout << "�������� ���������� �������������� �����!\n";
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
	else
		cout << "� ������� ��� �������!\n";
}



void MenuDeletePipePackage(GasSupplySystem& gss)
{
	unordered_set<int> found_pipes;
	vector<string> menu = {
		"������� ����� �� �����",
		"������� ����� �� �������",
		"������� ����� �� ID"
	};

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "������� ��� ����� ��� ��������: ";
		found_pipes = gss.SearchPipesByName(EnterLine());
		break;
	}
	case 2:
	{
		cout << "������� ������ ����� ��� �������� (\"1\"-� �������, \"0\"-� ������� ���������): ";
		found_pipes = gss.SearchPipesByStatus(GetCorrectNumber(0, 1));
		break;
	}
	case 3:
	{
		cout << "������� ID ����� ��� ��������: ";
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
		cout << "����� ������� �������." << endl;
	}
	else {
		cout << "�� ������� ���� ��� ��������." << endl;
	}
}

void MenuDeleteCSPackage(GasSupplySystem& gss)
{
	unordered_set<int> found_stations;
	vector<string> menu = {
		"������� ������� �� ��������",
		"������� ������� �� �������� �������������� �����",
		"������� ������� �� ID"
	};

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "������� �������� ������� ��� ��������: ";
		found_stations = gss.SearchCSByTitle(EnterLine());
		break;
	}
	case 2:
	{
		cout << "������� ������� �������������� ����� ��� ��������: ";
		found_stations = gss.SearchCSByWorkshops(GetCorrectNumber(0.0, 100.0));
		break;
	}
	case 3:
	{
		cout << "������� ID ������� ��� ��������: ";
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
		cout << "������� ������� �������." << endl;
	}
	else {
		cout << "�� ������� ������� ��� ��������." << endl;
	}
}

void MenuDelete(GasSupplySystem& gss)
{
	vector<string> menu = { "������� �����", "������� �������", "������� ��������� �����", "������� ��������� �������" };
	cout << "\n~��� �����~\n\n";
	gss.ShortShowPipes();
	cout << "\n~��� �������~\n\n";
	gss.ShortShowCS();

	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		if (!gss.IsPipeObjectsEmpty()) {
			cout << "������� id �����: ";
			gss.DeletePipe(GetCorrectNumber(1, INT_MAX));
		}
		else
			cout << "� ������� ��� ����!\n";
		break;
	}
	case 2:
	{
		if (!gss.IsCSObjectsEmpty()) {
			cout << "������� id �������: ";
			gss.DeleteCS(GetCorrectNumber(1, INT_MAX));
		}
		else
			cout << "� ������� ��� �������!\n";
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
