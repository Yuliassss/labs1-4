// serkovaAY.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int get_correct_number( int min, int max)
{
    int x;
    while ((cin >> x).fail() || x<min || x>max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "введите число (" << min << "-" << max << "): ";
    }   
    return x;
}

struct pipe
{
    string name;
    int lenght;
    int diametr;
    string status;
};

pipe input_pipe(){
    pipe p;

    cout << "введите название: ";
    cin >> ws;
    getline(cin, p.name);

    cout << "введите длину (1-100000): ";
    p.lenght = get_correct_number(1, 100000);
    
    cout << "введите диаметр(1-100): ";
    p.diametr = get_correct_number(1, 100);
    
   /* p.status = "В_ремонте";
    cout << p.status << endl;*/

    cout << "Выберете состояние:" << endl << "1. В_ремонте " << endl << "2. В_рабочем_состоянии " << endl;
    int i = 0;
    i = get_correct_number(0, 7);
    switch (i)
    {
    case 1: { p.status = "В_ремонте"; break; }
    case 2: { p.status = " В_рабочем_состоянии";  break; }
    }
    return p;
}

void print_pipe(const pipe& p1)
{
    cout << "\nназвание трубы: " << p1.name;
    cout << "\nдлина трубы: " << p1.lenght;
    cout << "\nдиаметр трубы: " << p1.diametr;
    cout << "\nпризнак: " << p1.status;
}

void save_pipe(const pipe& p1)
{
    ofstream fout;
    fout.open("data.txt", ios::app);
    if (fout.is_open())
    {
        fout << "\n PIPE" << endl << p1.name << endl << p1.lenght << endl << p1.diametr << endl << p1.status;
        fout.close();
    }
}

pipe load_pipe()
{
    pipe p;
    ifstream fin;
    string marker;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        do
        {
            fin >> marker;
        } while (!(marker == "\n PIPE"));
        fin >> marker;
        fin >> p.name;
        fin >> p.lenght;
        fin >> p.diametr;
        fin >> p.status;
        fin.close();
        return p;
    }
}

void edit_pipe(pipe& p)
{
    if (p.status == "В_ремонте")
    {
        p.status = "В_рабочем_состоянии";
    }
    else
    {
        p.status = "В_ремонте";
    }
}



struct ks
{
    string name;
    int number_ws;
    int number_ws_in_w;
    int effectiveness;
    string status;
};

ks input_ks()
{
    ks z;
    cout << "введите название: ";
    cin >> ws;
    getline(cin, z.name);

    cout << "введите количество цехов(1-12): ";
    z.number_ws = get_correct_number(1, 12);

    cout << "введите количество цехов в работе(1-5): ";
    z.number_ws_in_w = get_correct_number(1, 5);

    cout << "введите эффективность(1-100): ";
    z.effectiveness = get_correct_number(1, 100);

    z.status = "Цех_остановлен";
    cout << z.status << endl;

    return z;
}

void print_ks(const ks& z1)
{
    cout << "\nназвание кс: " << z1.name;
    cout << "\nколичество цехов: " << z1.number_ws;
    cout << "\nколичество цехов в работе: " << z1.number_ws_in_w;
    cout << "\nэффективность: " << z1.effectiveness;
    cout << "\nпризнак: " << z1.status;

}

void save_ks(const ks& z1)
{
    ofstream fout;
    fout.open("data.txt", ios::app);
    if (fout.is_open())
    {
        fout << "\n KS" << endl << z1.name << endl << z1.number_ws << endl << z1.number_ws_in_w << endl << z1.effectiveness << endl << z1.status;
        fout.close();
    }
}

ks load_ks()
{
    ks lu;
    ifstream fin;
    string marker;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {       
        do
        {
           fin >> marker;
        } while (!(marker == "\n KS"));
        fin >> lu.name;
        fin >> lu.number_ws;
        fin >> lu.number_ws_in_w;
        fin >> lu.effectiveness;
        fin >> lu.status;
        fin.close();



    }
    return lu;
}

void edit_ks(ks& z1)
{
    if (z1.status == "Цех_остановлен")
    {
        z1.status = "Цех_запущен";
    }
    else
    {
        z1.status = "Цех_остановлен";
    }
}

void print_menu()
{
    cout << "введите число (0-7): " << endl
        << "1. Добавить трубу " << endl
        << "2. Добавить КС " << endl
        << "3. Просмотр всех объектов " << endl
        << "4. Редактировать трубу " << endl
        << "5. Редактировать КС " << endl
        << "6. Сохранить " << endl
        << "7. Загрузить " << endl
        << "0. Выход " << endl;
        //<< "введите число (1-7): " << endl;

}





int main()
{
    setlocale(LC_ALL, "Russian");
    pipe pu;
    ks lu;
    while (true)
    {
        print_menu();
        int i =0 ;
        i = get_correct_number(0, 7);
        switch (i)
        {
        case 1: { pu = input_pipe(); break; }
        case 2: { lu = input_ks();  break; }
        case 3: 
        { 
            if (pu.name.empty()) { cout << "\nОбъект труба не был добавлен " << endl; }
            else { print_pipe(pu);}
            if (lu.name.empty()) { cout << "\nОбъект кс не был добавлен " << endl; }
            else {print_ks(lu); }
            //if (!pu.name.empty() || !lu.name.empty()) { cout << "Объекты сохранены " << endl; }
            /*print_pipe(pu);
            print_ks(lu);*/

            break; 
        }
        case 4: {
            if (pu.name.empty()) { cout << "Объект труба не был добавлен \n"; }
            else{ edit_pipe(pu);}
            break; }
        case 5: { 
            if (lu.name.empty()) { cout << "Объект кс не был добавлен \n"; }
            else { edit_ks(lu); }
            break; }
        case 6: 
        {
            if (pu.name.empty()) { cout << "Объект труба не был добавлен \n"; }
            else { save_pipe(pu); }
            if (lu.name.empty()) { cout << "Объект кс не был добавлен \n"; }
            else { save_ks(lu); }
            if (!pu.name.empty() || !lu.name.empty()) { cout << "\n Объекты сохранены \n"; }

            
           
            

            break; 
        }
        case 7: {
            /*if (pu.name.empty()) { cout << "Объект труба не был добавлен \n"; }
            else { load_pipe(); }
            if (lu.name.empty()) { cout << "Объект кс не был добавлен \n"; }
            else { load_ks(); }*/
            ifstream fin;
            string marker;
            fin.open("data.txt", ios::in);
            while (fin >> marker)
            {
                if (marker == "PIPE")
                {
                    pu = load_pipe();
                }
                else if (marker == "KS")
                {
                    lu=load_ks();
                }
            }
            


            break; }
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
