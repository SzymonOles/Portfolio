#include <iostream>
#include "Graph.h"
#include <fstream>

using namespace std;

Graph read_graph(char const *argv[], Graph g) {
    ifstream indata;
    string word;
    string vert1, vert2;
    int weight;
    int pos;
    indata.open(argv[1]);
    indata >> word;
    if (!indata) {
        cerr << "Error: file could not be opened\n" << endl;
        exit(1);
    }
    while (!indata.eof()) {
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
        indata >> word;
    }
    indata.close();
    return g;
}

struct Gb {
public:
    Gb(const Graph &g, bool b) : g(g), b(b) {}

    Graph g;
    bool b;
};

Graph ISS(Graph g, string s) {
    for (int i = 0; i < g.v.size(); ++i) {
        g.v[i].d = 999999999;
        g.v[i].p = -1;
    }
    g.v[g.find(s)].d = 0;
    return g;
}

Graph Relax(Graph g, int u, int v, int w) {
    if (g.v[v].d > g.v[u].d + w && g.v[u].d != 999999999) {
        g.v[v].d = g.v[u].d + w;
        g.v[v].p = u;
    }
    return g;
}

Gb BellmanFord(Graph g, string s) {
    g = ISS(g, s);
    for (int i = 1; i <= g.v.size() - 1; ++i) {
        for (int i = 0; i < g.v.size(); ++i) {
            for (int j = 0; j < g.v[i].adj.size(); ++j) {
                g = Relax(g, i, g.v[i].adj[j].id, g.v[i].adj[j].weight);
            }
        }
    }
    for (int i = 0; i < g.v.size(); ++i) {
        for (int j = 0; j < g.v[i].adj.size(); ++j) {
            int v = g.v[i].adj[j].id;
            int u = i;
            int w = g.v[i].adj[j].weight;
            if (g.v[v].d > g.v[u].d + w) {
                return Gb(g, false);
            }
        }
    }
    return Gb(g, true);
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "podaj argumenty";
        return -1;
    }
    Graph g;
    g = read_graph(argv, g);
    Gb wynik = BellmanFord(g, argv[2]);
    g = wynik.g;

    if (wynik.b) {
        cout << "TRUE";
    } else {
        cout << "FALSE";
    }
    cout << endl << endl;
    for (int i = 0; i < g.v.size(); ++i) {
        cout << "(" << g.v[i].data << ",";
        if (g.v[i].p < 0) {
            cout << "NULL";
        } else {
            cout << g.v[g.v[i].p].data;
        }
        cout << "), ";
    }
    cout << endl << endl;
    for (int i = 0; i < g.v.size(); ++i) {
        cout << "(" << g.v[i].data << ",";
        if ( g.v[i].d == 999999999){
            cout<<"inf";
        }
        else{
            cout<< g.v[i].d;
        }
        cout<< "), ";
    }
    cout << endl;
    return 0;
}
