// serkovaAY.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <chrono>
#include <format>
#include <stdio.h>
#include <fstream>
#include "GasSupplySystem.h"
#include "Addition.h"


using namespace std;
using namespace chrono;


int StartProgram(GasSupplySystem& GSS) {

    while (1)
    {
        Menu(1);
        switch (GetCorrectNumber(0, 7))
        {
        case 1:
        {

            GSS.Add(GSS.GetPipes());
            break;
        }
        case 2:
        {
            GSS.Add(GSS.GetCS());
            break;
        }
        case 3:
        {
            GSS.ShowObjects();

            break;
        }
        case 4:
        {
            GSS.EditPipe();

            break;
        }
        case 5:
        {
            GSS.EditCS();
            break;
        }
        case 6:
        {
            GSS.Save();
            break;
        }
        case 7:
        {
            GSS.Load();
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action" << "\n";
        }
        }
        //return 0;
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    GasSupplySystem GSS;

    redirect_output_wrapper cerr_out(cerr);
    string time = std::format("{:%d.%m.%Y_%H_%M_%OS}", system_clock::now() + std::chrono::hours(3));
    ofstream out_logfile("Logging/log_" + time);
    if (out_logfile)
        cerr_out.redirect(out_logfile);

    /*redirect_output_wrapper logg_in(cin);
    ifstream in_logfile;
    in_logfile.open("Logging/log_08_11_2023_21_46_41");
    if (in_logfile)
        logg_in.redirect(in_logfile);*/
    StartProgram(GSS);
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
