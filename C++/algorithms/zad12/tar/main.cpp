//niby kruskala napisałem (jedynie na potrzeby tego zadania) ale nie działa zbyt dobrze
//jeszcze go wysłałem jako osobne zadanie ale mam nadzieję że nie będzie tu liczony jako wymagany


#include <iostream>
#include "Graph.h"
#include <fstream>
#include <string>
#include <chrono>

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
        g.v[v2pos].p = v2pos;
        g.v[v1pos].adj.push_back(Line(v1pos, v2pos, weight));
//
    }
    indata.close();
    return g;
}

int find_set(Graph g, int u) {
    while (true) {
        if (g.v[u].p < 0 || g.v[u].p == u)
            return u;
        else
            u = g.v[u].p;
    }
}

//Graph MST_kruskal(Graph g) {
//    Graph g2 = g;
//    for (int i = 0; i < g2.v.size(); ++i) {
//        g2.v[i].adj.clear();
//    }
//    vector<Line> lines;
//    for (int i = 0; i < g.v.size(); ++i) {
//        for (int j = 0; j < g.v[i].adj.size(); ++j) {
//            lines.push_back(g.v[i].adj[j]);
//        }
//    }
//    for (int i = 0; i < lines.size(); ++i) {
//        for (int j = i; j < lines.size(); ++j) {
//            if (i == j)
//                continue;
//            if (lines[i].weight > lines[j].weight)
//                swap(lines[i], lines[j]);
//        }
//    }
//
//    int ls = lines.size();
//    for (int i = 0; i < ls; ++i) {
//        if (find_set(g2, lines[i].from) != find_set(g2, lines[i].to)) {
//            g2.v[lines[i].from].adj.push_back(lines[i]);
//            g2.v[lines[i].to].p = lines[i].from;
//        }
//    }
//
//    return g2;
//}

pair<Graph,int> find_set_new(Graph g, int u) {
    pair<Graph,int> temp;
    temp.first = g;
    temp.second = u;
    if (g.v[u].p != u) {
        temp.second = find_set_new(g, g.v[u].p).second;
    }
    return temp;
}

Graph Link(Graph g, int x, int y) {
    if (g.v[x].rank > g.v[y].rank) {
        g.v[y].p = x;
    } else {
        g.v[x].p = y;
        if (g.v[x].rank == g.v[y].rank) {
            g.v[y].rank == g.v[y].rank + 1;
        }
    }
    return g;
}

Graph Union(Graph g, int u, int v) {
    pair<Graph,int> pair1 ,pair2;
    pair1 = find_set_new(g,u);
    pair2 = find_set_new(g,v);
    return Link(pair2.first,pair1.second,pair2.second );
}

Graph MST_kruskal_new(Graph g) {
    Graph g2 = g;
    for (int i = 0; i < g2.v.size(); ++i) {
        g2.v[i].adj.clear();
        g2.v[i].p = i;
    }
    vector<Line> lines;
    for (int i = 0; i < g.v.size(); ++i) {
        for (int j = 0; j < g.v[i].adj.size(); ++j) {
            lines.push_back(g.v[i].adj[j]);
        }
    }
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = i; j < lines.size(); ++j) {
            if (i == j)
                continue;
            if (lines[i].weight > lines[j].weight)
                swap(lines[i], lines[j]);
        }
    }

    int ls = lines.size();
    for (int i = 0; i < ls; ++i) {
        if (find_set(g2, lines[i].from) != find_set(g2, lines[i].to)) {
            g2.v[lines[i].from].adj.push_back(lines[i]);
            g2 = Union(g2, lines[i].from, lines[i].to);
        }
    }

    return g2;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cout << "podaj argumenty";
        return -1;
    }
    Graph g, g2;
    g = read_graph(argv, g);
    g2 = g;
    auto start = std::chrono::high_resolution_clock::now();
//    g = MST_kruskal(g);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
//    cout << "ORIGINAL: " << elapsed.count() << " WEIGHT: ";
    int sum=0;
//    for (int i = 0; i < g.v.size(); ++i) {
//        for (int j = 0; j < g.v[i].adj.size(); ++j) {
//            sum += g.v[i].adj[j].weight;
//        }
//    }
//    cout << sum << endl;


    start = std::chrono::high_resolution_clock::now();
    g2 = MST_kruskal_new(g2);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout << "FOREST: " << elapsed.count() << " WEIGHT: ";
    sum = 0;
    for (int i = 0; i < g2.v.size(); ++i) {
        for (int j = 0; j < g2.v[i].adj.size(); ++j) {
            sum += g2.v[i].adj[j].weight;
        }
    }
    cout << sum << endl;


    return 0;
}
