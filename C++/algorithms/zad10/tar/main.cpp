#include <iostream>
#include "Graph.h"
#include "PrioQueue.h"
#include <fstream>

#define INF 999999
#define NIL -999999

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
        g.v[v2pos].adj.push_back(Line(v1pos, weight));
//
        indata >> word;
    }
    indata.close();
    return g;
}

int minPrio(Vertex v, Graph g) {
    int min = INT_MAX;
    for (int i = 0; i < v.adj.size(); ++i) {
        if (g.v[v.adj[i].id].color == BLACK) {
            if (v.adj[i].weight < min) {
                min = v.adj[i].weight;
            }
        }
    }
    return min;
}

bool QueCont(int u,int i, Graph g) {
    if (g.v[g.v[u].adj[i].id].color == BLACK)
        return true;
    return false;
}

bool isAdjToTree(int x, Graph g) {
    for (int i = 0; i < g.v[x].adj.size(); ++i) {
        if (g.v[x].color == WHITE) {
            if (g.v[g.v[x].adj[i].id].color == BLACK)
                return true;
        }
    }
    return false;
}

prioQueue<int> updateQ(prioQueue<int> Q, Graph g) {
    Q.v.clear();
    for (int i = 0; i < g.v.size(); ++i) {
        if (isAdjToTree(i, g)) {
            Q.InsertElement(Element<int>(i, minPrio(g.v[i], g)));
        }
    }
    return Q;
}

Graph MST_Prim(Graph g, string r) {

    for (int i = 0; i < g.v.size(); ++i) {
        g.v[i].key = INF;
        g.v[i].pi = NIL;
    }

    int pos = g.find(r);
    g.v[pos].key = 0;
    g.v[pos].color = BLACK;

    prioQueue<int> Q;

    Q = updateQ(Q, g);

    while (Q.v.size() > 0) {
        int u = Q.Pop().data.first;
        for (int i = 0; i < g.v[u].adj.size(); ++i) {
            if (QueCont(u,i, g) && g.v[u].adj[i].weight < g.v[u].key) {
                g.v[u].pi = g.v[u].adj[i].id;
                g.v[u].key = g.v[u].adj[i].weight;
                g.v[u].color = BLACK;
                Q = updateQ(Q, g);
            }
        }
    }

    return g;
}


int main(int argc, char const *argv[]) {
    if (argc != 3) {
        cout << "podaj argumenty";
        return -1;
    }
    Graph g;
    g = read_graph(argv, g);
    string r = argv[2];
    g = MST_Prim(g, r);
    int sum = 0;
    for (int i = 0; i < g.v.size(); ++i) {
        sum += g.v[i].key;
    }
    cout <<"weight of MST: "<< sum;
    return 0;
}
