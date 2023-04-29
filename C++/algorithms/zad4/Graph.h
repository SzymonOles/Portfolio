#ifndef ZAD4_GRAPH_H
#define ZAD4_GRAPH_H

#include "LinkedList.h"
#define MAXSIZE 9999

class Graph{
public:
    int root;
    int size = 0;
    LinkedList list[MAXSIZE];
    
    bool contains(string s){
        for (int i = 0; i < size; ++i) {
            if (list[i].guard->data==s)
                return true;
        }
        return false;
    }

    int find(string s){
        for (int i = 0; i < size; ++i) {
            if (list[i].guard->data==s)
                return i;
        }
        return -1;
    }
};
#endif //ZAD4_GRAPH_H
