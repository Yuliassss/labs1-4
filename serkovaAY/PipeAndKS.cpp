#include "PipeAndKS.h"








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

void PipeAndKS::ShortShowPipes()
{
	cout << "\n~ALL PIPES~\n\n";
	for (const auto& [id, pipe] : pipe_objects) {
		cout << "ID " << id << ": \"" << pipe.GetKmMark()
			<< ", D: " << pipe.GetDiameter() << " mm, \""
			<< pipe.PrintStatus() << "\"\n";
	}
	cout << "\n";
}





void PipeAndKS::Save()
{
	string filename;
	cout << "Введите имя файла ";
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
			ks.save_ks(fout, ks);
		}
	}
	else {
		cout << "Ошибка открытия файла" << "\n";
	}
	fout.close();
}

void PipeAndKS::Load()
{
	string filename;
	cout << "Введите имя файла ";
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
			p.load_pipe(fin);
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
		cout << "Ошибка открытия файла" << "\n";
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
