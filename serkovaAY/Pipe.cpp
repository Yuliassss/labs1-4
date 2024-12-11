#include "Pipe.h"
#include "Addition.h"

using namespace std;


istream& operator>>(istream& in, Pipe& p)
{
	cout << "������� ���: ";
	p.name = EnterLine();

	cout << "����� (0.1 - 5000 km): ";
	p.length = GetCorrectNumber(0.1, 5000.0);

	cout << "������� (700 - 1400 mm): ";
	p.diameter = GetCorrectNumber(700, 1400);

	cout << "������ (\"1\" - � �������, \"0\" - � ������� ���������): ";
	p.status = GetCorrectNumber(0, 1);

	return in;
}


ostream& operator<<(ostream& out, const Pipe& p)
{
	char symbol = 245; // marker
	out << "���������� � ����� " <<
		"\"" << p.name << "\":\n"
		<< symbol << " ID: " << p.id << "\n"
		<< symbol << " ��������k: " << p.name << "\n"
		<< symbol << " �����: " << p.length << " km" << "\n"
		<< symbol << " �������: " << p.diameter << " mm" << "\n"
		<< symbol << " " << p.PrintStatus() << "\n\n";

	return out;
}

std::ifstream& operator>>(ifstream& fin, Pipe& p)
{
	fin >> p.id;
	fin >> ws;
	getline(fin, p.name);
	fin >> p.length;
	fin >> p.diameter;
	fin >> p.status;
	int id = p.id;
	p.max_id = p.max_id <= id ? p.max_id = ++id : p.max_id;
	return fin;
}

std::ofstream& operator<<(ofstream& fout, const Pipe& p)
{
	fout << p.id << "\n"
		<< p.name << "\n"
		<< p.length << "\n"
		<< p.diameter << "\n"
		<< p.status << "\n";
	return fout;
}


string Pipe::PrintStatus() const
{
	return status ? "� �������" : "� ������� ���������";

}

void Pipe::ChangeStatus(bool new_status)
{
	status = new_status;
}
void Pipe::ToggleStatus()
{
	status = !status;
}

void Pipe::ResetMaxID()
{
	max_id = 1;
}


std::string Pipe::GetName() const
{
	return  name;
}


int Pipe::GetId() const
{
	return id;
}


int Pipe::max_id = 1;

Pipe::Pipe()
{
	id = max_id++;
}