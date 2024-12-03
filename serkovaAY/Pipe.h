#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Pipe {
private:
    int id; // Уникальный ID для каждого объекта
    string name;
    double length;
    double diameter;
    bool status;
    
    
public:
    static int countID; // Статический счетчик для уникальных ID
    Pipe( string n = "", double len = 0.0, double diam = 0.0, bool stat = 0)
        :id(countID++), name(n), length(len), diameter(diam), status(stat)
    {
    };

    string GetName() const ;
    double GetDiameter() const ;
    double GetLength() const ;
    bool GetStatus() const;
    int GetId() const ;
    static int GetCountID() ;

    friend istream& operator >> (istream& in, Pipe& p); //ввод

    friend ostream& operator << (ostream& out, const Pipe& p); //вывод

    void save_pipe(ofstream& fout, const Pipe& p);

    Pipe load_pipe(ifstream& fin);

    void edit_pipe();
};