#include <iostream>
#include "Graph.h"
#include "PrioQueue.h"
#include <string>
#include <fstream>

using namespace std;

//w projekcie odwzoruję łańcuch przemian za pomocą grafu, następnie uruchomię dijkstrę aby znaleźć najktótszą ścieżkę od złota do danego metalu
//następnie aby uniknąć wielokrotnego uruchamiania dijkstry dla każdego metalu, stworzę nowy graf gdzie będą odwrócone krawędzie
//i uruchomię algorytm dla złota co zwróci nam najkrótszą ścieżkę od danego metalu do złota
//potem w pętli obliczę końcowe koszty dla wszystkich metali i zwrócę ostateczny wynik

Graph read_graph(char const *argv[], Graph g, bool reverse) {
    ifstream indata;
    string word;
    int vert1, vert2;
    int weight;

    indata.open(argv[1]);
    if (!indata) {
        cerr << "Error: file could not be opened\n" << endl;
        exit(1);
    }

    indata >> word;
    int num;
    num = stoi(word);
    for (int i = 0; i < num; ++i) {
        indata >> word;
        string nazwa = "metal" + std::to_string(i + 1);
        Vertex temp = Vertex(nazwa);
        temp.value = stoi(word);
        g.v.push_back(temp);
    }

    indata >> word;
    num = stoi(word);


    for (int i = 0; i < num; ++i) {
        indata >> word;
        vert1 = stoi(word)-1;
        indata >> word;
        vert2 = stoi(word)-1;
        indata >> word;
        weight = stoi(word);
        if (!reverse){
            g.v[vert1].adj.push_back(Line(vert2,weight));
        } else{
            g.v[vert2].adj.push_back(Line(vert1,weight));
        }
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

Graph Dijkstra(Graph g, string s) {
    g = ISS(g, s);
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
        for (int i = 0; i < g.v[u].adj.size(); ++i) {
            g = Relax(g, u, g.v[u].adj[i].id, g.v[u].adj[i].weight);
        }
    }
    return g;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cout << "podaj ścieżkę do pliku";
        return -1;
    }
    Graph g, g2;
    g = read_graph(argv, g, false);
    g2 = read_graph(argv, g2,true);
    g = Dijkstra(g, "metal1");
    g2 = Dijkstra(g2, "metal1");
    vector<int> result;
    for (int i = 0; i < g.v.size(); ++i) {
        result.push_back(g.v[i].d + g.v[i].value/2 + g2.v[i].d);
    }
    cout<< *std::min_element(result.begin(), result.end());
    return 0;
}