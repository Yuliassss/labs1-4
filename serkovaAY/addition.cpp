#include "addition.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;




int print_menu() {
    int i = 0;
    i = get_correct_number(0, 7);
    cout << "введите число (0-7): " << endl
        << "1. Добавить трубу " << endl
        << "2. Добавить КС " << endl
        << "3. Просмотр всех объектов " << endl
        << "4. Редактировать трубу " << endl
        << "5. Редактировать КС " << endl
        << "6. Сохранить " << endl
        << "7. Загрузить " << endl
        << "0. Выход " << endl;
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