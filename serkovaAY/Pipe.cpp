#include "Pipe.h"
#include "Addition.h"

using namespace std;

int Pipe::max_id = 1;
int Pipe::pipe_diameters[] = { 500, 700, 1000, 1400 };

int Pipe::EnterCorrectDiameter()
{
	cout << "������� (500, 700, 1000, 1400 mm): ";
	int diameter = GetCorrectNumber(1, INT_MAX);
	while (!count(begin(pipe_diameters), end(pipe_diameters), diameter)) {
		cout << "�������� ������� (500, 700, 1000, 1400 mm): ";
		diameter = GetCorrectNumber(1, INT_MAX);
	}
	return diameter;
}

string Pipe::PrintStatus() const
{
	return status ? "� �������" : "� ������� ���������";

}

void Pipe::ChangeStatus()
{
	status = !status;
}

void Pipe::ResetMaxID()
{
	max_id = 1;
}

std::string Pipe::GetKmMark() const
{
	return km_mark;
}

int Pipe::GetDiameter() const
{
	return diameter;
}

double Pipe::GetLength() const
{
	return length;
}

int Pipe::GetId() const
{
	return id;
}

void Pipe::SetDiameter(int d)
{
	diameter = d;
}

Pipe::Pipe()
{
	id = max_id++;
}

//istream& operator>>(istream& in, Pipe& p)
//{
//
//	cout << "Kilometer mark: ";
//	p.km_mark = EnterLine();
//
//	cout << "Length (0.1 - 5000 km): ";
//	p.length = GetCorrectNumber(0.1, 5000.0);
//
//	p.diameter = p.EnterCorrectDiameter();
//
//	cout << "Status (\"1\" - in repair, \"0\" - in working condition): ";
//	p.status = GetCorrectNumber(0, 1);
//
//	return in;
//}

void Pipe::InitPipe(int diam)
{
	cout << "������� ��������: ";
	km_mark = EnterLine();

	cout << "������� ����� (0.1 - 5000 km): ";
	length = GetCorrectNumber(0.1, 5000.0);

	if (!diam)
		diameter = EnterCorrectDiameter();
	else
		diameter = diam;

	cout << "������ (\"1\" - � �������, \"0\" - � ������� ���������): ";
	status = GetCorrectNumber(0, 1);
}

ostream& operator<<(ostream& out, const Pipe& p)
{
	char symbol = 245; // marker
	out << "���������� � ����� " <<
		"\"" << p.km_mark << "\":\n"
		<< symbol << " ID: " << p.id << "\n"
		<< symbol << " ��������: " << p.km_mark << "\n"
		<< symbol << " �����: " << p.length << " km" << "\n"
		<< symbol << " �������: " << p.diameter << " mm" << "\n"
		<< symbol << " " << p.PrintStatus() << "\n\n";

	return out;
}

ifstream& operator>>(ifstream& fin, Pipe& p)
{
	fin >> p.id;
	fin >> ws;
	getline(fin, p.km_mark);
	fin >> p.length;
	fin >> p.diameter;
	fin >> p.status;
	int id = p.id;
	p.max_id = p.max_id <= id ? p.max_id = ++id : p.max_id;
	return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& p)
{
	fout << p.id << "\n"
		<< p.km_mark << "\n"
		<< p.length << "\n"
		<< p.diameter << "\n"
		<< p.status << "\n";
	return fout;
}