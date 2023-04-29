#ifndef ZAD4_GRAPH_H
#define ZAD4_GRAPH_H

#include <iostream>
#include <vector>

using namespace std;

enum Color {
    WHITE,
    GRAY,
    BLACK
};

struct Line {
public:
    Line(int id, int weight) : id(id), weight(weight) {}

    int id = -1;
    int weight = -1;
};

struct Vertex {
public:
    Vertex(const string &data) : data(data) {}

    string data;
    int p = -1;
    int d = -1;
    int f = -1;
    Color color = WHITE;
    vector<Line> adj;
};

class Graph {
public:
    vector<Vertex> v;

    bool contains(string s) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i].data == s)
                return true;
        }
        return false;
    }

    int find(string s) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i].data == s)
                return i;
        }
        return -1;
    }
};

#endif //ZAD4_GRAPH_H
