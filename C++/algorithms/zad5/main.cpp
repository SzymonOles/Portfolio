#include <iostream>
#include "Graph.h"
#include <fstream>
#include <algorithm>

using namespace std;

Graph read_graph(char const *argv[], Graph g) {
    vector<string> ver1, ver2, ver3;
    vector<int> iver3;
    vector<int> wght;

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

        ver1.push_back(vert1);
        ver2.push_back(vert2);
        wght.push_back(weight);
//
        indata >> word;
    }
    indata.close();

    try {
        for (int i = 0; i < ver1.size(); ++i) {
            if (count(iver3.begin(), iver3.end(), stoi(ver1[i])) == 0) {
                iver3.push_back(stoi(ver1[i]));
            }
            if (count(iver3.begin(), iver3.end(), stoi(ver2[i])) == 0) {
                iver3.push_back(stoi(ver2[i]));
            }
        }
        sort(iver3.begin(), iver3.end());
        for (int i = 0; i < iver3.size(); ++i) {
            g.v.push_back(Vertex(to_string(iver3[i])));
        }

        for (int i = 0; i < ver1.size(); ++i) {
            int v1position = g.find(ver1[i]);
            int v2position = g.find(ver2[i]);
            g.v[v1position].adj.push_back(Line(v2position, wght[i]));
            g.v[v2position].p = v1position;
        }
    }
    catch (exception e) {
        for (int i = 0; i < ver1.size(); ++i) {
            if (count(ver3.begin(), ver3.end(), ver1[i]) == 0) {
                ver3.push_back(ver1[i]);
            }
            if (count(ver3.begin(), ver3.end(), ver2[i]) == 0) {
                ver3.push_back(ver2[i]);
            }
        }
        for (int i = 0; i < ver3.size(); ++i) {
            g.v.push_back(Vertex(ver3[i]));
        }

        for (int i = 0; i < ver1.size(); ++i) {
            int v1position = g.find(ver1[i]);
            int v2position = g.find(ver2[i]);
            g.v[v1position].adj.push_back(Line(v2position, wght[i]));
            g.v[v2position].p = v1position;
        }

    }
    return g;
}


int tim;
vector<string> list;

Graph DFS_Visit(Graph g, int u) {
    tim++;
    g.v[u].d = tim;
    g.v[u].color = GRAY;
    for (int i = 0; i < g.v[u].adj.size(); ++i) {
        if (g.v[g.v[u].adj[i].id].color == WHITE) {
            g.v[g.v[u].adj[i].id].p = u;
            g = DFS_Visit(g, g.v[u].adj[i].id);
        }
    }
    g.v[u].color = BLACK;
    tim++;
    g.v[u].f = tim;
//    
    list.push_back(g.v[u].data);
//    
    return g;
}

Graph DFS(Graph g) {
    tim = 0;
    for (int i = 0; i < g.v.size(); ++i) {
        if (g.v[i].color == WHITE) {
            g = DFS_Visit(g, i);
        }
    }
    return g;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cout << "podaj nazwe pliku";
        return -1;
    }
    Graph g;
    g = read_graph(argv, g);
    g = DFS(g);
    reverse(list.begin(), list.end());

    for (int i = 0; i < list.size(); ++i) {
        if (i % 10 == 0)
            cout << endl;
        cout << list[i] << " ";
    }
    cout << endl;
    return 0;
}
