#include <iostream>
#include <fstream>
#include <vector>

//maks numer node'a
#define MAXSIZE 1001
//opcje do zapisu
bool WEIGHTED = true;
bool DIRECTED = true;

using namespace std;

class graph {
public:

    short arr[MAXSIZE][MAXSIZE]{};

//    pseudo set
    vector<int> nodes;

    graph() {
        for (int i = 0; i < MAXSIZE; ++i) {
            for (int j = 0; j < MAXSIZE; ++j) {
                arr[i][j] = 22222;
            }
        }
    }

    void read_graph(const string &filename) {
        ifstream indata;
        string word;
        int node1, node2, weight;
        int pos;
        bool found1, found2;
        indata.open(filename);
        indata >> word;
        if (!indata) {
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }
        while (!indata.eof()) {
//
            pos = word.find(',');
            node1 = stoi(word.substr(0, pos));
            word = word.erase(0, pos + 1);
            pos = word.find(',');
            node2 = stoi(word.substr(0, pos));
            weight = stoi(word.substr(pos + 1));

            arr[node1][node2] = weight;

            found1 = false;
            found2 = false;
            for (int i = 0; i < nodes.size(); ++i) {
                if (nodes[i] == node1)
                    found1 = true;
                if (nodes[i] == node2)
                    found2 = true;
            }
            if (!found1)
                nodes.push_back(node1);
            if (!found2 && node1 != node2) {
                nodes.push_back(node2);
            }
//
            indata >> word;
        }
        indata.close();
    }

    void to_dot(const string &filename) {
        ofstream myfile;
        myfile.open(filename);
//

        if (DIRECTED) {
            myfile << "digraph {\n";
        } else {
            myfile << "graph {\n";
        }

        for (int i = 0; i < MAXSIZE; ++i) {
            for (int j = 0; j < MAXSIZE; ++j) {

                if (arr[i][j] != 22222) {

                    myfile << "\t" << i;

                    if (DIRECTED) {
                        myfile << " -> ";
                    } else {
                        myfile << " -- ";
                    }

                    myfile << j;

                    if (WEIGHTED) {
                        myfile << "[label=\"" << arr[i][j] << "\"]";
                    }

                    myfile << ";\n";
                }

            }
        }
        myfile << "}";
//
        myfile.close();
    }

    void is_complete() {

        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = 0; j < nodes.size(); ++j) {
                if (i == j)
                    continue;
                if (arr[nodes[i]][nodes[j]] == 22222 && arr[nodes[j]][nodes[i]] == 22222) {
                    cout << "graph is not complete\n";
                    return;
                }
                if (arr[nodes[i]][nodes[j]] != 22222 && arr[nodes[j]][nodes[i]] != 22222) {
                    cout << "graph is not complete\n";
                    return;
                }
            }
        }
        cout << "graph is complete\n";
    }
};

int main(int argc, char const *argv[]) {
    if (argc != 2)
        return 1;
    string name = argv[1];
    name = name.substr(0,name.find('.'));
    name += ".dot";
    graph g;
    g.read_graph(argv[1]);
    g.to_dot(name);
    g.is_complete();
    return 0;
}
