#include "Pipe.h"
#include "addition.h"

int Pipe::max_id = 1;//

string Pipe::GetName() const { return name; };//
double Pipe::GetDiameter() const { return diameter; };//
double Pipe::GetLength() const { return length; };
bool Pipe::GetStatus() const { return status; }
int Pipe::GetId() const { return id; };//
int Pipe::GetCountID() { return countID; };


void Pipe::InitPipe(){

    cout << "������� ��������: ";
    cin >> ws;
    getline(cin, name);

    cout << "������� ����� (1-100000): ";
    length = get_correct_number(1.0, 100000.0);

    cout << "������� �������(1-100): ";
    diameter = get_correct_number(1.0, 100.0);

    cout << "�������� ���������:" << endl << "0. � ������� " << endl << "1. � ������� ��������� " << endl;
    int i = get_correct_number(0, 1);
    status = (i == 1);

};

std::ostream& operator << (ostream& out, const Pipe& p)//

{   char symbol = 249;
    out << "���������� � ����� " << endl <<
        "\"" << p.name << "\":\n"
        << symbol << "\nID: " << p.id
        << symbol << "\n�������� �����: " << p.name
        << symbol << "\n����� �����: " << p.length
        << symbol << "\n������� �����: " << p.diameter
        << symbol << "\n�������: " << p.status; //////////////////////////
    return out;
};


ifstream& operator>>(ifstream& fin, Pipe& p)
{
    fin >> p.id;
    fin >> ws;
    getline(fin, p.name);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.status;
    int id = p.id;
    p.max_id = p.max_id <= id ? p.max_id = ++id : p.max_id;
    return fin;
}





void Pipe::save_pipe(ofstream & fout, const Pipe & p) const {
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

void Pipe::ChangeStatus() //
{status = !status;} 