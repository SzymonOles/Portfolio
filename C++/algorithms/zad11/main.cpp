#include <iostream>
#include "Graph.h"
#include <fstream>
#include <string>


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

Graph MST_kruskal(Graph g) {


    Graph g2 = g;
    for (int i = 0; i < g2.v.size(); ++i) {
        g2.v[i].adj.clear();
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
            g2.v[lines[i].to].p = lines[i].from;
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
    g = MST_kruskal(g);
    vector<Line> lines;
    for (int i = 0; i < g.v.size(); ++i) {
        for (int j = 0; j < g.v[i].adj.size(); ++j) {
            lines.push_back(g.v[i].adj[j]);
        }
    }
    int ls = lines.size();
    ofstream myfile;
    myfile.open("output_file");
    for (int i = 0; i < ls; ++i) {
        myfile << g.v[lines[i].from].data << "," << g.v[lines[i].to].data << "," << lines[i].weight;

        if (i + 1 != ls)
            myfile << endl;
    }
    myfile.close();
    return 0;
}
