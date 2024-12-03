
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;

mutex m;
void threadFunction(const string& filename)
{
    m.lock();
    auto start = system_clock::now();
    ifstream fin;
    fin.open(filename);
    int right_triangle = 0;
    if (fin) {
        int count = 0;
        fin >> count;
        for (int i = 0; i < count; ++i) {
            int value1 = 0;
            int value2 = 0;
            int value3 = 0;
            fin >> value1 >> value2 >> value3;
            if ((value1 + value2) > value3 &&
                (value1 + value3) > value2 &&
                (value2 + value3) > value1) {
                right_triangle += 1;
            }
        }
    }
    else {
        cout << "Error in opening file" << filename << endl;
    }
    auto finish = system_clock::now();
    auto duration = duration_cast<microseconds>(finish - start).count();
    cout << "Right triangles: " << right_triangle << endl;
    cout << "Execution time for the file " << filename << ": " << duration << " microseconds" << endl;
    m.unlock();
}
    

int main(int argc, char* argv[]) {
    vector<thread> threads;
    threads.reserve(argc - 1);
    auto start = system_clock::now();
    for (int i = 1; i < argc; ++i) {
        threads.push_back(thread(threadFunction, argv[i]));
    }
    for (auto& th : threads) {
        th.join();
    }
    auto finish = system_clock::now();
    auto duration = duration_cast<microseconds>(finish - start).count();
    cout << "Execution time of the entire program: " << duration << " microseconds" << endl;
    return 0;
}
