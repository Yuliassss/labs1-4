#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <unordered_map>

using namespace std;

class Pipe {
private:
    static int max_id; // 
    int id; // 
    string name;//
    double length;//
    double diameter;//
    
    
public:

    bool status;//

    Pipe( string n = "", double len = 0.0, double diam = 0.0, bool stat = 0)
        :id(max_id++), name(n), length(len), diameter(diam), status(stat)
    {
    };

    string GetName() const ;//
    double GetDiameter() const ;//
    double GetLength() const ;//
    int GetId() const ;//
    static int GetCountID() ;

    void InitPipe();////////////////
    friend ostream& operator << (ostream& out, const Pipe& p); //

    friend ifstream& operator >> (ifstream& fin, Pipe& p);//
    friend ofstream& operator << (ofstream& fout, const Pipe& p);//


    void ChangeStatus();//

    //friend void filter_pipes_by_name(std::unordered_map<int, Pipeline>& pipes);
    //friend void filter_pipes_by_repair(std::unordered_map<int, Pipeline>& pipes);
};