#include "addition.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;




int print_menu() {
    int i = 0;
    i = get_correct_number(0, 7);
    cout << "������� ����� (0-7): " << endl
        << "1. �������� ����� " << endl
        << "2. �������� �� " << endl
        << "3. �������� ���� �������� " << endl
        << "4. ������������� ����� " << endl
        << "5. ������������� �� " << endl
        << "6. ��������� " << endl
        << "7. ��������� " << endl
        << "0. ����� " << endl;
    return i;
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