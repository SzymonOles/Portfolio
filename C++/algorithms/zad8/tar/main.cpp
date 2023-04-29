#include <iostream>
#include "Graph.h"
#include "PrioQueue.h"
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

prioQueue<string> Dijkstra(Graph g, string s) {
    g = ISS(g, s);
    prioQueue<string> S;
    int rozmiar = g.v.size();
    while (rozmiar != 0) {
        int min = 1000000000;
        int u;
        for (int i = 0; i < g.v.size(); ++i) {
            if (g.v[i].color != BLACK) {
                if (g.v[i].d < min) {
                    min = g.v[i].d;
                    u = i;
                }
            }
        }
        g.v[u].color = BLACK;
        rozmiar--;
        S.InsertElement(Element<string>(g.v[u].data, g.v[u].d));
        for (int i = 0; i < g.v[u].adj.size(); ++i) {
            g = Relax(g, u, g.v[u].adj[i].id, g.v[u].adj[i].weight);
        }
    }
    return S;
}

int main(int argc, char const *argv[]) {
    if (argc < 5) {
        cout << "podaj argumenty";
        return -1;
    }
    Graph g;
    g = read_graph(argv, g);
    prioQueue<string> S,S2;
    S = Dijkstra(g, argv[2]);
    S2 = S;
    while (S.v.size() > 1){
        pair<string, int> pr = S.Pop().data;
        if (pr.first == argv[3]){
            cout<<pr.second<<" ";
        }
    }
    while (S2.v.size() > 1){
        pair<string, int> pr = S2.Pop().data;
        if (pr.first == argv[4]){
            cout<<pr.second<<" ";
        }
    }
    return 0;
}
