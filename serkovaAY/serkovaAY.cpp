// serkovaAY.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "pipe.h"
#include "KS.h"
#include "PipeAndKS.h"
#include "addition.cpp"


#include <unordered_map>
using namespace std;



int main(){
    PipeAndKS piKS;
    Pipe p;
    KS ks;
    setlocale(LC_ALL, "Russian");

    while (true)
    {
        print_menu();
        int i = 0;
        i = get_correct_number(0, 7);
        switch (i)
        {
        case 1: {
            cin >> p; 
            piKS.GetPipe().insert({ p.GetId(), p });
            break; }
        case 2: {   
            cin >> ks;
            piKS.GetKS().insert({ ks.GetId(), ks }); 
            break; }
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
                 
            
             break; }
        case 0: { return 0; }
        default: { cout << "произошла ошибка" << endl; break; }
        }
     }
    return 0;
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
