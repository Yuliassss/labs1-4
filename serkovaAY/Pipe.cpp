#include "Pipe.h"
#include "Addition.h"

using namespace std;


istream& operator>>(istream& in, Pipe& p)
{
	cout << "Kilometer mark: ";
	p.km_mark = EnterLine();

	cout << "Length (0.1 - 5000 km): ";
	p.length = GetCorrectNumber(0.1, 5000.0);

	cout << "Diameter (700 - 1400 mm): ";
	p.diameter = GetCorrectNumber(700, 1400);

	cout << "Status (\"0\" - in working condition, \"1\" - in repair): ";
	p.status = GetCorrectNumber(0, 1);

	return in;
}


ostream& operator<<(ostream& out, const Pipe& p)
{
	char symbol = 249; // marker
	out << "Information about Pipe " <<
		"\"" << p.km_mark << "\":\n"
		<< symbol << " ID: " << p.id << "\n"
		<< symbol << " Kilometer mark: " << p.km_mark << "\n"
		<< symbol << " Length: " << p.length << " km" << "\n"
		<< symbol << " Diameter: " << p.diameter << " mm" << "\n"
		<< symbol << " " << p.PrintStatus() << "\n\n";

	return out;
}

std::ifstream& operator>>(ifstream& fin, Pipe& p)
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

std::ofstream& operator<<(ofstream& fout, const Pipe& p)
{
	fout << p.id << "\n"
		<< p.km_mark << "\n"
		<< p.length << "\n"
		<< p.diameter << "\n"
		<< p.status << "\n";
	return fout;
}


string Pipe::PrintStatus() const
{
	return status ? "In repair" : "In Working condition";

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


int Pipe::GetId() const
{
	return id;
}


int Pipe::max_id = 1;

Pipe::Pipe()
{
	id = max_id++;
}