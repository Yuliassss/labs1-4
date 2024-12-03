#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class KS
{
private:
    int id;
    string name;
    int number_ws;
    int number_ws_in_w;
    int effectiveness;
    

public:
    static int countID;
    
    KS(string n = "", int nw = 0, int ninw = 0, int e = 0)
        :id(countID++), name(n), number_ws(nw), number_ws_in_w(ninw), effectiveness(e) {};
        
    string GetName() const;
    int GetNumbersWs() const;
    int GetNumbersInWork() const;
    int GetEffectiveness() const;

    int GetId() const;

    int GetCountID();

    friend istream& operator >> (istream& in, KS& ks); //ввод

    friend ostream& operator << (ostream& out, const KS& ks); //вывод


    void editKS();



    void save_ks(ofstream& fout, const KS& ks) ;


    void load_ks(ifstream& fin);
   


};

   

