#pragma once
#include <iostream>
#include <fstream>
#include <string>


class Pipe
{
public:
	bool status;

	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);

	std::string PrintStatus() const;
	void ToggleStatus();
	void ChangeStatus(bool);
	static void ResetMaxID();

	std::string GetName() const;
	int GetId() const;

	Pipe();

private:
	static int max_id;
	std::string name;
	float length;
	int diameter;
	int id;

};
