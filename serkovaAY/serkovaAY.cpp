// serkovaAY.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
//#include <chrono>
//#include <format>
//#include <stdio.h>
#include <fstream>
#include "PipeAndKS.h"
#include "addition.h"


using namespace std;

//using namespace chrono;


void print_menu() {
    cout << "введите число (0-7): " << endl
        << "1. Добавить трубу " << endl
        << "2. Добавить КС " << endl
        << "3. Просмотр всех объектов " << endl
        << "4. Редактировать трубу " << endl
        << "5. Редактировать КС " << endl
        << "6. Сохранить " << endl
        << "7. Загрузить " << endl
        << "0. Выход " << endl;
}

int StartProgram(PipeAndKS& piks) {
    while (1)
    {
        vector<string> menu = { "Добавить трубу",
                                "Добавить КС",
                                "Просмотр всех объектов",
                                "Редактировать трубу",
                                "Редактировать КС",
                                "Сохранить",
                                "Загрузить",
                                "Выход" };
        switch (ChooseActionMenu(menu, true))
        {
        case 1: {
            piks.AddPipe()
            break;
        }
        case 2: {
            cin >> ks;
            piKS.GetKS().insert({ ks.GetId(), ks });
            break;
        }
        case 3: {
            auto& pipe_map = piKS.GetPipe();
            auto& ks_map = piKS.GetKS();

            if (pipe_map.empty()) {
                cout << "\nНет объектов труба." << endl;
            }
            else {
                for (const auto& [key, p] : pipe_map) {
                    cout << p << endl;
                }
            }

            if (ks_map.empty()) {
                cout << "\nНет объектов КС." << endl;
            }
            else {
                for (const auto& [key, ks] : ks_map) {
                    cout << ks << endl;
                }
            }
            break;
        }
        case 4: {
            int id;
            cout << "Введите ID трубы для редактирования: ";
            cin >> id;
            auto& pipe_map = piKS.GetPipe();
            auto it = pipe_map.find(id);
            if (it != pipe_map.end()) {
                it->second.edit_pipe();  // Редактирование найденного объекта Pipe
            }
            else {
                cout << "Труба с таким ID не найдена." << endl;
            }
            break;
        }
        case 5: {
            int id;
            cout << "Введите ID КС для редактирования: ";
            cin >> id;
            auto& ks_map = piKS.GetKS();
            auto it = ks_map.find(id);
            if (it != ks_map.end()) {
                it->second.editKS();  // Редактирование найденного объекта KS
            }
            else {
                cout << "КС с таким ID не найдена." << endl;
            }
            break;
        }
        case 6:
        {
            piKS.Save();
            break;

        }
        case 7: {
            piKS.Load();


            break;
        }
        case 0: { return 0; }
        default: { cout << "произошла ошибка" << endl; break; }
        }
    }
    return 0;
}

int main(){
    PipeAndKS piks;

    setlocale(LC_ALL, "Russian");
    
    StartProgram(piks);

    
 }


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
