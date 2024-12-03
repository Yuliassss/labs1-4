#include "Pipe.h"
#include "addition.h"

int Pipe::countID = 1;

string Pipe::GetName() const { return name; };
double Pipe::GetDiameter() const { return diameter; };
double Pipe::GetLength() const { return length; };
bool Pipe::GetStatus() const { return status; }
int Pipe::GetId() const { return id; };
int Pipe::GetCountID() { return countID; };


std::istream& operator >> (istream& in, Pipe& p){

    cout << "введите название: ";
    in >> ws;
    getline(in, p.name);

    cout << "введите длину (1-100000): ";
    p.length = get_correct_number(1.0, 100000.0);

    cout << "введите диаметр(1-100): ";
    p.diameter = get_correct_number(1.0, 100.0);

    cout << "Выберете состояние:" << endl << "0. В ремонте " << endl << "1. В рабочем состоянии " << endl;
    int i = get_correct_number(0, 1);
    p.status = (i == 1);

    return in;
};

std::ostream& operator << (ostream& out, const Pipe& p)/* вывод */

{  //char symbol = 249; // marker
    if ((p.name) == "None")
    {
        out << "трубы отсутствуют" << endl;
        return out;
    }
    out << "PIPE" 
        << "\nID: " << p.id
        << "\nназвание трубы: " << p.name
        << "\nдлина трубы: " << p.length
        << "\nдиаметр трубы: " << p.diameter
        << "\nпризнак: " << p.status;
    return out;
};

void Pipe::save_pipe(ofstream & fout, const Pipe & p) {
    fout << "\nPIPE" << endl << p.GetId() << endl << p.GetName() << endl << p.GetLength() << endl << p.GetDiameter() << endl << p.GetStatus();
}

Pipe Pipe::load_pipe(ifstream& fin) {// ???????????
    Pipe p = {};
    {
        fin >> p.id;
        getline(fin, p.name);
        fin >> p.length >> p.diameter >> p.status;
        fin.ignore();
        int id = p.id;
        p.countID = p.countID <= id ? p.countID = ++id : p.countID;
            
    }
    return p;
}

void Pipe::edit_pipe() {
    status = !status;
}