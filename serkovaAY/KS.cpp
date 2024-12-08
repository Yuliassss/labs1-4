#include "KS.h"
#include "addition.h"

int KS::countID = 1;

string KS::GetName() const { return name; }
int KS::GetNumbersWs() const{ return number_ws;}
int KS::GetNumbersInWork() const {return number_ws_in_w;}
int KS::GetEffectiveness() const {    return effectiveness;}
int KS::GetId() const { return id; };
int KS::GetCountID() { return countID; };


std::istream& operator >> (istream& in, KS& ks) {

    cout << "������� ��������: ";
    in >> ws;
    getline(in, ks.name);

    cout << "������� ���������� �����(1-12): ";
    ks.number_ws = get_correct_number(1, 12);

    cout << "������� ���������� ����� � ������(1-12): ";
    ks.number_ws_in_w = get_correct_number(1, 12);

    cout << "������� �������������(1-100): ";
    ks.effectiveness = get_correct_number(1, 100);

    return in;
}

std::ostream& operator << (ostream& out, const  KS& ks)/* ����� */
{
    if ((ks.name) == "None")
    {
        out << "������� ����������� �����������" << endl;
        return out;
    }
    out << "KS"
        << "\nID: " << ks.id;
    out << "\n�������� ��: " << ks.name;
    out << "\n���������� �����: " << ks.number_ws;
    out << "\n���������� ����� � ������: " << ks.number_ws_in_w;
    out << "\n�������������: " << ks.effectiveness;
    return out;
}

void KS::editKS()
{
    cout << "��������� ��� ���������� ���" << endl << "0. ���������� " << endl << "1. ��������� " << endl;
    int i = 0;
    i = get_correct_number(0, 1);
    switch (i)
    {
    case 0: { number_ws_in_w--; break; }
    case 1: {
        if (number_ws_in_w == number_ws) { cout << "� ������ ������������ ���������� �����" << endl; }
        else { number_ws_in_w++; }  break;
    }
    }
}

void KS::save_ks(ofstream& fout, const KS& ks) const {    
    fout << "KS" << endl << ks.GetId() << endl << ks.name << endl << ks.number_ws << endl << ks.number_ws_in_w << endl << ks.effectiveness;}


void KS::load_ks(ifstream& fin) {///?????
    fin >> id;
    getline(fin, name);
    fin >> number_ws >> number_ws_in_w >> effectiveness;
    fin.ignore();
    
}
