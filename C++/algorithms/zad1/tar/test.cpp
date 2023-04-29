#include <iostream>
#include <bits/stdc++.h>
#include "Set.h"
#include <chrono>
#include <fstream>

int main(int argc, char *argv[]) {
    Set<int> myset, myset2;

    ifstream indata;
    int num;
    indata.open("test_set.txt");
    indata >> num;
    if (!indata) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    cout << "working..." << endl;
    auto start = std::chrono::high_resolution_clock::now();
    while (!indata.eof()) {
        myset.insert(num);
        indata >> num;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout << "Dodawanie: " << elapsed.count() << " s\n";

    indata.close();
    myset2.v = myset.v;

    start = std::chrono::high_resolution_clock::now();
    myset.isMember(1000010);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << "isMember: " << elapsed.count() << " s\n";

    start = std::chrono::high_resolution_clock::now();
    myset.Union(myset2);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << "Union: " << elapsed.count() << " s\n";

    start = std::chrono::high_resolution_clock::now();
    myset.Intersection(myset2);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << "Intersection: " << elapsed.count() << " s\n";

    start = std::chrono::high_resolution_clock::now();
    myset.Difference(myset2);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << "Difference: " << elapsed.count() << " s\n";


    return 0;
}