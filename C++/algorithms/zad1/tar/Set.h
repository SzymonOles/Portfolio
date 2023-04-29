#ifndef ZAD1_SET_H
#define ZAD1_SET_H

#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class Set {
public:

    vector<T> v;

    bool isMember(T x) {

        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == x) {
                return true;
            }
        }

        return false;
    }

    bool insert(T x) {
        if (!isMember(x)) {
            v.push_back(x);
            return true;
        }
        return false;
    }

    T pop(T x) {
        if (isMember(x)) {
            int j;
            for (int i = 0; i < v.size(); ++i) {
                if (v[i] == x) {
                    j = i;
                    break;
                }
            }
            T val = v[j];
            v.erase(v.begin() + j);
            return val;
        } else {
            T a;
            return a;
        }
    }

    void print() {
        for (int i = 0; i < v.size(); ++i) {
            cout << v[i] << " ";
        }
        cout << endl;
    }

    Set popAll(Set set2) {
        Set<T> newset;
        newset.v = v;
        for (int i = 0; i < newset.v.size(); i++) {
            if (set2.isMember(newset.v[i])) {
                newset.pop(newset.v[i]);
                i--;
            }
        }
        return newset;
    }

    Set Union(Set set2) {
        Set<T> newset;
        newset.v = v;
        for (int i = 0; i < set2.v.size(); ++i) {
            newset.insert(set2.v[i]);
        }
        return newset;
    }

    Set Intersection(Set set2) {
        Set<T> newset;
        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < set2.v.size(); ++j) {
                if (v[i] == set2.v[j]) {
                    newset.insert(v[i]);
                }
            }
        }
        return newset;
    }

    Set Difference(Set set2) {
        Set<T> newset;
        for (int i = 0; i < v.size(); ++i) {
            if (!set2.isMember(v[i]))
                newset.insert(v[i]);
        }
        for (int i = 0; i < set2.v.size(); ++i) {
            if (!isMember(set2.v[i]))
                newset.insert(set2.v[i]);
        }
        return newset;
    }
};

#endif //ZAD1_SET_H
