#ifndef GRAPH_H
#define GRAPH_H

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
    Line(int from, int to, int weight) : from(from), to(to), weight(weight) {}

    int from;
    int to ;
    int weight ;
};

struct Vertex {
public:
    Vertex(const string &data) : data(data) {}

    string data;
    int p = -1;
    int rank = 0;
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
            if (v[i].data == s) {
                return i;
            }
        }
    }
};

#endif //GRAPH_H
