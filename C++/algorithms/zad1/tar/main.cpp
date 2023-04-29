#include <iostream>
#include <bits/stdc++.h>
#include "Set.h"

using namespace std;

void getdatastr(const string &s,const string &data) {
    Set<string> myset, myset2;
    string word;
    stringstream ss(data);
    bool second = false;

    //wczytywanie
    while (ss >> word) {

        if (word == "|") {
            second = true;
            continue;
        }
        //pierwsza czesc
        if (!second) {
            myset.insert(word);
        }
            //druga czesc
        else {
            myset2.insert(word);
        }
    }
    //odpalanie funkcji
    if (!second) {
        myset.print();
    } else {
//        myset.print();
//        myset2.print();
        myset.Difference(myset2).print();
        myset.Intersection(myset2).print();
        myset.Union(myset2).print();
        myset.popAll(myset2).print();
    }

}

void getdataint(const string &s,const string &data) {
    Set<int> myset, myset2;
    string  word;
    stringstream ss(data);
    bool second = false;

    //wczytywanie
    while (ss >> word) {
        int iword = stoi(word);

        if (word == "|") {
            second = true;
            continue;
        }
        //pierwsza czesc
        if (!second) {
            myset.insert(iword);
        }
            //druga czesc
        else {
            myset2.insert(iword);
        }
    }
    //odpalanie funkcji
    if (!second) {
        myset.print();
    } else {
//        myset.print();
//        myset2.print();
        myset.Difference(myset2).print();
        myset.Intersection(myset2).print();
        myset.Union(myset2).print();
        myset.popAll(myset2).print();
    }

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "w argumentach podaj typ danych";
        return 1;
    }

    string s = argv[1];
    string data;
    for (int i = 2; i < argc; ++i) {
        data+= argv[i];
        data += " ";
    }

    if (s == "integer") {
        getdataint(s,data);
    } else if (s == "string") {
        getdatastr(s,data);
    } else {
        cout << "nieodpowiedni typ danych w argumencie";
        return 1;
    }
    return 0;
}