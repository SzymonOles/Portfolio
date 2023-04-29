#ifndef ZAD2_PRIOQUEUE_H
#define ZAD2_PRIOQUEUE_H

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

template<typename T>
class Element {
public:
    pair<T, int> data;

    Element(T x, int prio) {
        data.first = x;
        data.second = prio;
    }
};

template<typename T>
class prioQueue {
public:
    vector<Element<T>> v;

//    funkcje pomocnicze    ================================

    prioQueue() {
        T temp;
        v.push_back(Element<T>(temp, -1));
    }

    int prio(int x) {
        if (x < v.size() && x != 0)
            return v[x].data.second;
        else
            return -1;
    }

    void swap(int a, int b) {
        std::swap(v[a], v[b]);
    }

    int left(int x) {
        return 2 * x;
    }

    int right(int x) {
        return 2 * x + 1;
    }

    int parent(int x) {
        if (x == 1)
            return 1;
        return x / 2;
    }

    void show() {
        for (int i = 1; i < v.size(); ++i) {
            cout << v[i].data.second << " " << v[i].data.first << " " << endl;
        }
        cout << endl;
    }

//    funkcje do operacji   ==============================

    void InsertElement(Element<T> e) {
        v.push_back(e);
        int pos = v.size() - 1;
        while (true) {
            if (pos == 1)
                break;
            if (prio(pos) < prio(parent(pos)))
                break;
            else {
                swap(pos, parent(pos));
                pos = parent(pos);
            }
        }
    }

    int getMaxPriority() {
        if (v.size() > 1)
            return v[1].data.second;
        return 0;
    }

    Element<T> Remove(int position) {
        Element<T> e = v[position];
        int pos = position;
        swap(position, v.size() - 1);
        v.erase(v.begin() + v.size() - 1);
        while (true) {
            if (prio(pos) >= prio(left(pos)) && prio(pos) >= prio(right(pos)))
                break;
            else {
                if (prio(left(pos)) > prio(right(pos))) {
                    swap(pos, left(pos));
                    pos = left(pos);
                } else {
                    swap(pos, right(pos));
                    pos = right(pos);
                }
            }
        }
        return e;
    }

    Element<T> Pop() {
        return Remove(1);
    }

    void IncreasePriority(Element<T> e, int priority) {
        vector<Element<T>> els;
        for (int i = 1; i < v.size(); ++i) {
            if (v[i].data == e.data) {
                els.push_back(Remove(i));
                i = 1;
            }
        }
        for (int i = 0; i < els.size(); ++i) {
            els[i].data.second = priority;
            InsertElement(els[i]);
        }
    }
};

#endif //ZAD2_PRIOQUEUE_H
