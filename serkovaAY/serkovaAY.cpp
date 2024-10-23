// serkovaAY.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int get_correct_number( int min, int max){
    int x;
    while ((cin >> x).fail() || x<min || x>max){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "введите число (" << min << "-" << max << "): ";
    }   
    return x;
}

struct pipe
{
    string name;
    double length;
    double diameter;
    bool status;
};

pipe input_pipe(){
    pipe p;

    cout << "введите название: ";
    cin >> ws;
    getline(cin, p.name);

    cout << "введите длину (1-100000): ";
    p.length = get_correct_number(1, 100000);
    
    cout << "введите диаметр(1-100): ";
    p.diameter = get_correct_number(1, 100);

    cout << "Выберете состояние:" << endl << "0. В ремонте " << endl << "1. В рабочем состоянии " << endl;
    int i = get_correct_number(0 , 1);
    switch (i)
    {
    case 0: { p.status = 0; break; }
    case 1: { p.status = 1;  break; }
    }
    return p;
}

void print_pipe(const pipe& p){
    cout << "\nназвание трубы: " << p.name;
    cout << "\nдлина трубы: " << p.length;
    cout << "\nдиаметр трубы: " << p.diameter;
    cout << "\nпризнак: " << p.status;
}





void edit_pipe(pipe& p)
{
    p.status = !p.status;
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
    ks ks;
    cout << "введите название: ";
    cin >> ws;
    getline(cin, ks.name);

    cout << "введите количество цехов(1-12): ";
    ks.number_ws = get_correct_number(1, 12);

    cout << "введите количество цехов в работе(1-12): ";
    ks.number_ws_in_w = get_correct_number(1, 12);

    cout << "введите эффективность(1-100): " ;
    ks.effectiveness = get_correct_number(1, 100);
    return ks;
}

void print_ks(const ks& k)
{
    cout << "\nназвание кс: " << k.name;
    cout << "\nколичество цехов: " << k.number_ws;
    cout << "\nколичество цехов в работе: " << k.number_ws_in_w;
    cout << "\nэффективность: " << k.effectiveness;
}









void edit_ks( ks& ks){
    cout << "Запустите или остановите цех" << endl << "0. остановить " << endl << "1. запустить " << endl;
    int i = 0;
    i = get_correct_number(0, 1);
    switch (i)
    {
    case 0: { ks.number_ws_in_w--; break; }
    case 1: { if (ks.number_ws_in_w == ks.number_ws) { cout << "В работе максимальное количество цехов" << endl; }
          else { ks.number_ws_in_w++; }  break;
    }
    }
}

void save_ks(ofstream& fout,const ks& k)
{
    fout << "\nKS" << endl << k.name << endl << k.number_ws << endl << k.number_ws_in_w << endl << k.effectiveness;
}
void save_pipe(ofstream& fout, const pipe& p) {
    fout << "\nPIPE" << endl << p.name << endl << p.length << endl << p.diameter << endl << p.status ;
}
void save(pipe& p, ks& k) {
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        if (p.name.empty()) { cout << "Объект труба не был добавлен \n"; }
        else { save_pipe(fout, p); }
        if (k.name.empty()) { cout << "Объект кс не был добавлен \n"; }
        else { save_ks(fout, k); }
        if (!p.name.empty() || !k.name.empty()) { cout << "\nОбъекты сохранены \n"; }
        
    }
    fout.close();

}


pipe load_pipe(ifstream& fin) {
    pipe p = {};
    {
        getline(fin, p.name);
        fin >> p.length >> p.diameter >> p.status;
        fin.ignore();
    }     
    return p;
}

ks load_ks(ifstream& fin){
    ks k = {};
    {
        getline(fin, k.name);
        fin >> k.number_ws >> k.number_ws_in_w >> k.effectiveness;
        fin.ignore();
    }
    return k;
}

void load(pipe& p, ks& k ) {
    ifstream fin("data.txt");
    if (fin.is_open()) {
        string marker;
        while (getline(fin, marker)) {
            if (marker.find("PIPE") != string::npos)
                p = load_pipe( fin);
            if (marker.find("KS") != string::npos)
                k = load_ks(fin);
        }
        fin.close();
    }   
}

void print_menu(){
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

int main(){
    setlocale(LC_ALL, "Russian");
    pipe p;
    ks k;
    
    while (true)
    {
        print_menu();
        int i = 0;
        i = get_correct_number(0, 7);
        switch (i)
        {
        case 1: { p = input_pipe(); break; }
        case 2: { k = input_ks();  break; }
        case 3: {
            if (p.name.empty()) { cout << "\nОбъект труба не был добавлен " << endl; }
            else {print_pipe(p);
            }
            if (k.name.empty()) { cout << "\nОбъект кс не был добавлен " << endl; }
            else {print_ks(k);}
            break;
        }
        case 4: {
            if (p.name.empty()) { cout << "Объект труба не был добавлен \n"; }
            else { edit_pipe(p); }
            break;
        }
        case 5: {
            if (k.name.empty()) { cout << "Объект кс не был добавлен \n"; }
            else { edit_ks(k); }
            break;
        }
        case 6:
        {
            save(p, k);

        }
        case 7: {
            load(p,k);           
            
             break; }
            case 0: { return 0; }
            default: { cout << "произошла ошибка" << endl; }
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
