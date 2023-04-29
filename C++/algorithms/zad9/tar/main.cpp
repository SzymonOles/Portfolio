#include <iostream>
#include "Graph.h"
#include <fstream>
#include <string>
#define INF 999999

using namespace std;

Graph read_graph(char const *argv[], Graph g) {
    ifstream indata;
    string word;
    string vert1, vert2;
    int weight;
    int pos;
    indata.open(argv[1]);

    while (!indata.eof()) {
        indata >> word;
//
        pos = word.find(',');
        vert1 = word.substr(0, pos);
        word = word.erase(0, pos + 1);
        pos = word.find(',');
        vert2 = word.substr(0, pos);
        weight = stoi(word.substr(pos + 1));

        if (!g.contains(vert1)) {
            g.v.push_back(Vertex(vert1));
        }
        if (!g.contains(vert2)) {
            g.v.push_back(Vertex(vert2));
        }
        int v1pos = g.find(vert1);
        int v2pos = g.find(vert2);
        g.v[v1pos].adj.push_back(Line(v2pos, weight));
//
    }
    indata.close();
    return g;
}

int **floydWarshall(Graph g) {
    int n = g.v.size();
    int **D;
    D = new int *[n];
    for (int i = 0; i < n; ++i) {
        D[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i==j){
                D[i][j]=0;
            }
            else{
                D[i][j] = INF;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < g.v[i].adj.size(); ++j) {
            D[i][g.v[i].adj[j].id] = g.v[i].adj[j].weight;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }

    return D;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cout << "podaj argumenty";
        return -1;
    }
    Graph g;
    g = read_graph(argv, g);
    int **D;
    D = floydWarshall(g);

    for (int i = 2; i < argc; ++i) {
        int pos;
        string vert1,vert2;
        string word = argv[i];
        pos = word.find(',');
        vert1 = word.substr(1, pos-1);
        word = word.erase(0, pos + 1);
        pos = word.find('\'');
        vert2 = word.substr(0, pos);

        int v1,v2;
        v1 = g.find(vert1);
        v2 = g.find(vert2);

        cout<<D[v1][v2]<<" ";
    }
    return 0;
}
