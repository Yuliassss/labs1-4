#include "PipeAndKS.h"

void PipeAndKS::Save()
{
	string filename;
	cout << "������� ��� ����� ";
	cin >> ws;
	getline(cin, filename);
	ofstream fout;
	fout.open(filename);
	if (fout) {
		fout << pipe_map.size() << " " << ks_map.size() << "\n";
		for (const auto& [key, p] : pipe_map) {
			p.save_pipe(fout, p);
		}
		for (const auto& [key, ks] : ks_map) {
			fout << ks;
		}
	}
	else {
		cout << "������ �������� �����" << "\n";
	}
	fout.close();
}

void PipeAndKS::Load()
{
	string filename;
	cout << "������� ��� ����� ";
	cin >> ws;
	getline(cin, filename);
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
			pipe_map.insert({ p.GetId(), p });
			if (p.GetId() > temp_id_p)
				temp_id_p = p.GetId();
		}
		for (int i = 0; i < num_ks; i++) {
			fin >> ks;
			ks_map.insert({ ks.GetId(), ks });
			if (ks.GetId() > temp_id_ks)
				temp_id_ks = ks.GetId();
		}
		Pipe::countID = temp_id_p + 1;
		KS::countID = temp_id_ks + 1;
	}
	else
	{
		cout << "������ �������� �����" << "\n";
	}
	fin.close();
}

std::unordered_map<int, Pipe>& PipeAndKS::GetPipe()
{
	return pipe_map;
}

std::unordered_map<int, KS>& PipeAndKS::GetKS()
{
	return ks_map;
}
