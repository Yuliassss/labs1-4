// serkovaAY.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct pipe
{
    string name;
    int lenght;
    int diametr;
};

pipe input_pipe()
{
    pipe p;
    cout << "введите название: ";
    cin >> p.name;
    do
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "введите длину (1-100000): ";
        cin >> p.lenght;
    } while (cin.fail() || p.lenght < 1 || p.lenght>100000);

    do
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "введите диаметр(1-100): ";
        cin >> p.diametr;
    } while (cin.fail() || p.diametr < 1 || p.diametr > 100);

    return p;
}

void print_pipe(const pipe& p1)
{
    cout << "\nназвание трубы: " << p1.name;
    cout << "\nдлина трубы: " << p1.lenght;
    cout << "\nдиаметр трубы: " << p1.diametr;
}

void save_pipe(const pipe& p1)
{
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << p1.name << endl << p1.lenght << endl << p1.diametr;
        fout.close();
    }
}

pipe load_pipe()
{
    pipe pu;
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        fin >> pu.name;
        fin >> pu.lenght;
        fin >> pu.diametr;
        fin.close();
    }
    return pu;
}

void edit_pipe(pipe& p1)
{
    p1.diametr += 5;
}

struct ks
{
    string name;
    int number_ws;
    int number_ws_in_w;
    int effectiveness;
};

ks input_ks()
{
    ks z;
    cout << "введите название: ";
    cin >> z.name;
    do
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "введите количество цехов(1-12): ";
        cin >> z.number_ws;
    } while (cin.fail() || z.number_ws < 1 || z.number_ws > 12);

    do
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "введите количество цехов в работе(1-5): ";
        cin >> z.number_ws_in_w;
    } while (cin.fail() || z.number_ws_in_w < 1 || z.number_ws_in_w > 5);

    do
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "введите эффективность(1-100): ";
        cin >> z.effectiveness;
    } while (cin.fail() || z.effectiveness < 1 || z.effectiveness > 100);

    return z;
}

void print_ks(const ks& z1)
{
    cout << "\nназвание кс: " << z1.name;
    cout << "\nколичество цехов: " << z1.number_ws;
    cout << "\nколичество цехов в работе: " << z1.number_ws_in_w;
    cout << "\nэффективность: " << z1.effectiveness;

}

void save_ks(const ks& z1)
{
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << z1.name << endl << z1.number_ws << endl << z1.number_ws_in_w << endl << z1.effectiveness;
        fout.close();
    }
}

ks load_ks()
{
    ks lu;
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        fin >> lu.name;
        fin >> lu.number_ws;
        fin >> lu.number_ws_in_w;
        fin >> lu.effectiveness;
        fin.close();
    }
    return lu;
}

void edit_ks(ks& z1)
{
    z1.number_ws_in_w += 50;
}

void print_menu()
{
    cout << "1. Добавить трубу " << endl
        << "2. Добавить КС " << endl
        << "3. Просмотр всех объектов " << endl
        << "4. Редактировать трубу " << endl
        << "5. Редактировать КС " << endl
        << "6. Сохранить " << endl
        << "7. Загрузить " << endl
        << "0. Выход " << endl;
}

//int get_correct_number(int min, int max)
//{
//    int x;
//    while ((cin >> x).fail() || x<min || x>max);
//    {
//        cin.clear();
//        cin.ignore(1000, '\n');
//        cout << "введите число (" << min << "-" << max << "):";
//        cin >> x;
//    }
//    return x;
//}

int main()
{
    setlocale(LC_ALL, "Russian");
    pipe pu;
    ks lu;
    while (1)
    {
        print_menu();
        int i=0;
        cin >> i;
        //get_correct_number(0, 7)
        switch (i)
        {
        case 1: { pu = input_pipe(); break; }
        case 2: { lu = input_ks();  break; }
        case 3: { print_pipe(pu); print_ks(lu); break; }
        case 4: { edit_pipe(pu);  break; }
        case 5: { edit_ks(lu);  break; }
        case 6: { save_pipe(pu); save_ks(lu);  break; }
        case 7: { pu = load_pipe(); lu = load_ks();  break; }
        case 0: { return 0; }
        default: {
            cout << "произошла ошибка" << endl;
        }
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
