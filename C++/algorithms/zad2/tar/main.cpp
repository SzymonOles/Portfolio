#include "PrioQueue.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>

using namespace std;

//program defaultowo działa na stringach ale można zmienić typ danych na dowolny tylko trzeba w mainie przekonwertowac stringi
int main(int argc, char *argv[]) {
    prioQueue<string> queue;
    string data, word, w1;
    int pos,w2;

    for (int i = 1 ; i < argc; ++i) {
        data+= argv[i];
        data+= " ";
    }

    stringstream ss(data);

    while (ss >> word) {
//        wywalanie nawiasów i '
        word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
        word.erase(std::remove(word.begin(), word.end(), '('), word.end());
        word.erase(std::remove(word.begin(), word.end(), ')'), word.end());
//        rozdzielanie wzgledem przecinka
        pos = word.find(',');
        w1= word.substr(0,pos);
        w2 = stoi(word.substr(pos+1));

        queue.InsertElement(Element<string>(w1, w2));
    }
//    sciaganie z drzewa
    {
        while (queue.v.size() > 1){
            cout << queue.Pop().data.first << " ";
        }
    }

    return 0;
}