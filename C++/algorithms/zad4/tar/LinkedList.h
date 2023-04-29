#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <iostream>
#include <stdexcept>
#include <fstream>
using namespace std;

enum Color{
    WHITE,
    GRAY,
    BLACK
};

class LinkedList {
public:
    struct Node {
        string data;
        int weight=0;
        int distance=-1;
        Color color = WHITE;
        Node *prev;
        Node *next;
    };

    int size = 0;

    Node *guard = new Node();
    Node *pointer = guard;

    LinkedList() {
        guard->prev = guard;
        guard->next = guard;
        guard->data = "";
    }

    void resetPointer() {
        pointer = guard;
    }

    bool movePointer() {
        pointer = pointer->next;
        if (pointer == guard)
            return false;
        return true;
    }

    void push_back(string x,int wgh) {
        Node *komorka = new Node;
        komorka->data = x;
        komorka->weight=wgh;
        guard->prev->next = komorka;
        komorka->prev = guard->prev;
        guard->prev = komorka;
        komorka->next = guard;
        size++;
    }

    bool empty() {
        if (size == 0)
            return true;
        return false;
    }

    bool contains(string x) {
        Node *komorka = guard->next;
        while (komorka != guard) {
            if (komorka->data == x) {
                return true;
            }
            komorka = komorka->next;
        }
        return false;
    }
};

#endif