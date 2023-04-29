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
    if (!indata) {
        cerr << "Error: file could not be opened\n" << endl;
        exit(1);
    }
    indata >> word;
    indata >> word;
    while (true) {
//
        if (indata.eof())
            break;
        indata >> vert1;
        if (indata.eof())
            break;
        indata >> word;
        if (indata.eof())
            break;
        indata >> vert2;
        vert2 = vert2.substr(0, 1);

        ver1.push_back(vert1);
        ver2.push_back(vert2);
//
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
            g.v[v1position].adj.push_back(Line(v2position, 1));
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
            g.v[v1position].adj.push_back(Line(v2position, 1));
            g.v[v2position].p = v1position;
        }

    }
    return g;
}


int tim;

bool vcontains(vector<int> v, int x) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == x)
            return true;
    }
    return false;
}

Graph DFS_Visit(Graph g, int u) {
    tim++;
    g.v[u].d = tim;
    g.v[u].color = GRAY;

    int number;
    int position;
    vector<int> used;

    for (int i = 0; i < g.v[u].adj.size(); ++i) {
        number = -2;
        for (int j = 0; j < g.v[u].adj.size(); ++j) {
            if (vcontains(used, g.v[u].adj[j].id))
                continue;
            if (g.v[g.v[u].adj[j].id].f > number) {
                number = g.v[g.v[u].adj[j].id].f;
                position = g.v[u].adj[j].id;
            }
        }
        used.push_back(position);
        if (g.v[position].color == WHITE) {
            g.v[position].p = u;
            g = DFS_Visit(g, position);
        }

    }
    g.v[u].color = BLACK;
    tim++;
    g.v[u].f = tim;
    return g;
}

Graph DFS(Graph g, bool writelevel) {
    for (int i = 0; i < g.v.size(); ++i) {
        g.v[i].color = WHITE;
    }

    tim = 0;
    int level = 0;
    int number;
    int position;
    vector<int> used;

    for (int i = 0; i < g.v.size(); ++i) {
        number = -2;
        for (int j = 0; j < g.v.size(); ++j) {
            if (vcontains(used, j))
                continue;
            if (g.v[j].f > number) {
                number = g.v[j].f;
                position = j;
            }
        }
        used.push_back(position);
        if (g.v[position].color == WHITE) {
            g = DFS_Visit(g, position);
            level++;
        }

    }

//
    if (writelevel) {
        cout << level << endl;
    }
//
    return g;
}

Graph Transpose(Graph g) {
    Graph t = g;
    for (int i = 0; i < t.v.size(); ++i) {
        t.v[i].adj.clear();
    }
    for (int i = 0; i < g.v.size(); ++i) {
        for (int j = 0; j < g.v[i].adj.size(); ++j) {

            string nam = g.v[i].data;
            int connum = g.v[i].adj[j].id;
            string con = g.v[connum].data;

            t.v[t.find(con)].adj.push_back(Line(t.find(nam), 1));
        }
    }
    return t;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cout << "podaj sciezke do pliku";
        return -1;
    }
    Graph g;
    g = read_graph(argv, g);
    g = DFS(g, false);
    g = Transpose(g);
    DFS(g, true);

    return 0;
}
