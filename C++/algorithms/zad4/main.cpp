#include <iostream>
#include "Graph.h"
#include "LinkedQueue.h"
#include <list>

using namespace std;

class Vertex {
public:
    string data;

    Vertex(const string &data) : data(data) {}
};

Graph read_graph(char const *argv[], Graph g) {
    ifstream indata;
    string word;
    string node1, node2;
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
        node1 = word.substr(0, pos);
        word = word.erase(0, pos + 1);
        pos = word.find(',');
        node2 = word.substr(0, pos);
        weight = stoi(word.substr(pos + 1));

        if (!g.contains(node1)) {
            g.list[g.size].guard->data = node1;
            g.list[g.size].push_back(node2, weight);
            g.size++;
        } else {
            int position = g.find(node1);
            g.list[position].push_back(node2, weight);
        }
//
        indata >> word;
    }
    indata.close();
    g.root = g.find(argv[2]);
    return g;
}

Graph format_graph(Graph g) {
    for (int i = 0; i < g.size; ++i) {
        while (g.list[i].movePointer()) {
            string dat = g.list[i].pointer->data;
            if (!g.contains(dat)) {
                g.list[g.size].guard->data = dat;
                g.size++;
            }
        }
    }
    for (int i = 0; i < g.size; ++i) {
        for (int j = 0; j < g.size; ++j) {
            if (i == j)
                continue;
            if (g.list[j].contains(g.list[i].guard->data)) {
                g.list[i].push_back(g.list[j].guard->data, g.list[j].guard->weight);
            }
        }
    }
    return g;
}


Graph BFS(Graph g, const Vertex &start) {
    LinkedQueue q;
    g.list[g.root].guard->color=GRAY;
    g.list[g.root].guard->distance=0;

    for (int i = 0; i < g.size; ++i) {
        g.list[i].resetPointer();
        while (g.list[i].movePointer()) {
            if (g.list[i].pointer->data == g.list[g.root].guard->data) {

                g.list[i].pointer->color = GRAY;
                g.list[i].pointer->distance = 0;
            }
        }
    }
    q.push(start.data);
    while (!q.empty()) {
        string u = q.pop();
        int pos = g.find(u);
        g.list[pos].resetPointer();
        while (g.list[pos].movePointer()) {
            if (g.list[pos].pointer->color == WHITE) {

                string ptr = g.list[pos].pointer->data;

                for (int i = 0; i < g.size; ++i) {
                    g.list[i].resetPointer();
                    do {
                        if (g.list[i].pointer->data == ptr) {
                            g.list[i].pointer->color = GRAY;
                            g.list[i].pointer->distance = g.list[pos].guard->distance + 1;
                        }
                    } while (g.list[i].movePointer());
                }

                q.push(ptr);
            }
        }
        g.list[pos].guard->color = BLACK;
        for (int i = 0; i < g.size; ++i) {
            g.list[i].resetPointer();
            while (g.list[i].movePointer()) {
                if (g.list[i].pointer->data == g.list[pos].guard->data) {
                    g.list[i].pointer->color = BLACK;
                }
            }
        }
    }
    return g;
}

list<Vertex> get_path(Graph g,Vertex end) {
    list<Vertex> l ;
    int pos = g.find(end.data);
    if (pos == -1) {
        l.push_back(Vertex("nie znaleziono"));
        return l;
    }
    else if(g.list[pos].guard->distance < 0){
        l.push_back(Vertex("nie ma sciezki"));
        return l;
    }
    else{
        int dist = g.list[pos].guard->distance;
        l.push_back(Vertex(g.list[pos].guard->data));
        while(dist>0){
            g.list[pos].resetPointer();
            while(g.list[pos].movePointer()){
                if (g.list[pos].pointer->distance == dist-1){
                    l.push_back(Vertex(g.list[pos].pointer->data));
                    pos = g.find(g.list[pos].pointer->data);
                    dist = g.list[pos].guard->distance;
                }
            }
        }
        l.reverse();
        return l;
    }
}

int get_hops(Graph g, Vertex end) {
    int pos = g.find(end.data);
    if (pos == -1)
        return -1;
    else{
        return g.list[pos].guard->distance;
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "za malo argumentow";
        return -1;
    }
    Graph g;
    g = read_graph(argv, g);
    g = format_graph(g);
    g = BFS(g, Vertex(argv[2]));

    for (int i = 3; i < argc; ++i) {
        cout << get_hops(g, Vertex(argv[i])) << " ";
    }
    cout << endl;

//  //============wyswietlanie path====================
//    for (int i = 3; i < argc; ++i) {
//        list<Vertex> l = get_path(g,Vertex(argv[i]));
//        for (auto const &j: l) {
//            cout << j.data << " ";
//        }
//        cout<<endl;
//    }
//    cout << endl;

    return 0;
}
