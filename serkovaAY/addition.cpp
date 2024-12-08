#include "addition.h"

#include <iostream>
#include <fstream>
#include <string>
#include <format>
using namespace std;


int ChooseActionMenu(vector<string>& menu, bool with_exit = false)
{
	if (menu.size() < 1)
		return -1;
	int i = 1;
	for (auto& s : menu)
		cout << std::format("{}. {}", i++, s) << "\n";
	if (with_exit)
		cout << "0. Exit\n";

	cout << "Choose action: ";
	return GetCorrectNumber<int>(0, menu.size());
}



//void load(pipe& p, ks& k ) {
//    ifstream fin("data.txt");
//    if (fin.is_open()) {
//        string marker;
//        while (getline(fin, marker)) {
//            if (marker.find("PIPE") != string::npos)
//                p = load_pipe( fin);
//            if (marker.find("KS") != string::npos)
//                k = load_ks(fin);
//        }
//        fin.close();
//    }   
//}