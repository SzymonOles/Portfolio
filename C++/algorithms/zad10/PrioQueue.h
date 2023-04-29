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

    void swap(int a, int b) {
        std::swap(v[a], v[b]);
    }

    int left(int x) {
        return 2 * x + 1;
    }

    int right(int x) {
        return 2 * x + 2;
    }

    int parent(int x) {
        return (x-1) / 2;
    }

//    funkcje do operacji   ==============================

    void InsertElement(Element<T> e) {
        v.push_back(e);
        int pos = v.size() - 1;
        while (pos != 0 && v[parent(pos)].data.second > v[pos].data.second)
        {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }

    void MinHeapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < v.size() && v[l].data.second < v[i].data.second)
            smallest = l;
        if (r < v.size() && v[r].data.second < v[smallest].data.second)
            smallest = r;
        if (smallest != i)
        {
            swap(i, smallest);
            MinHeapify(smallest);
        }
    }

    Element<T> Remove(int position) {
        if (v.size() == 1)
        {
            Element<T> e = v[0];
            v.erase(v.begin());
            return e;
        }

        Element<T> root = v[0];
        v[0] = v[v.size()-1];
        v.erase(v.begin() + v.size());
        MinHeapify(0);

        return root;
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
