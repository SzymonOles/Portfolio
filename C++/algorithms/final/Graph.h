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
    Line(int id, int weight) : id(id), weight(weight) {}

    int id ;
    int weight ;
};

struct Vertex {
public:
    Vertex(const string &data) : data(data) {}

    string data;
    int value = 0;
    int p = -1;
    int d = -9999;
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
