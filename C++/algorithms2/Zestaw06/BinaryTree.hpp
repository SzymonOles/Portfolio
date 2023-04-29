#ifndef __BINARY_TREE__
#define __BINARY_TREE__
#include <iostream>
#include <stdexcept>

using namespace std;

class BinaryTree
{
public:
    struct Node
    {
        int data = 0;
        Node *childL = NULL;
        Node *childR = NULL;
    };

    int siz = 0, min = 0, max = 0, dep = 0;
    Node *root;

    // wstawia elementxdo drzewa
    void insert(int x)
    {
        Node *temp = new Node();
        temp->data = x;
        Node *ptr = root;
        int tmpdep = 1;

        if (siz == 0)
        {
            root = temp;
            min = x;
            max = x;
        }
        else
        {
            while (true)
            {
                if (x < ptr->data)
                {
                    if (ptr->childL == NULL)
                    {
                        ptr->childL = temp;
                        break;
                    }
                    ptr = ptr->childL;
                }
                else
                {
                    if (ptr->childR == NULL)
                    {
                        ptr->childR = temp;
                        break;
                    }
                    ptr = ptr->childR;
                }
                tmpdep++;
            }
            tmpdep++;
            if (tmpdep > dep)
            {
                dep = tmpdep;
            }
            if (x < min)
            {
                min = x;
            }
            if (x > max)
            {
                max = x;
            }
        }
        siz++;
    }
    // sprawdza czy element należy do drzewa, zwraca wskaźnik do węzła lub nullptr.
    //Napisać wersję iteracyjną i rekurencyjną

    Node *search(int x)
    {
        Node *ptr = root;
        while (true)
        {
            if (ptr == NULL)
                return NULL;

            if (ptr->data == x)
                return ptr;

            if (x < ptr->data)
                ptr = ptr->childL;

            else
                ptr = ptr->childR;
        }
    }

    Node *pointer = NULL;
    Node *searchRecursive(int x, Node *ptr)
    {
        if (ptr == NULL)
            return NULL;

        if (ptr->data == x)
        {
            pointer = ptr;
            return NULL;
        }
        else
        {
            if (x < ptr->data)
                searchRecursive(x, ptr->childL);

            else
                searchRecursive(x, ptr->childR);
        }

        return pointer;
    }
    // zwraca liczbę węzłów
    int size()
    {
        return siz;
    }
    // zwraca wartość najmniejszego elementu
    int minimum()
    {
        return min;
    }
    // zwraca wartość największego elementu
    int maximum()
    {
        return max;
    }
    // zwraca wysokość drzewa
    int depth()
    {
        return dep;
    }
    int deprek(Node *N){
        return N ? max(deprek(N->childL),deprek(N->childR))+1 : 0;
    }
    // wypisuje zawartość wszystkich węzłów odpowiedniow porządku
    // inorder,preorder i postorder. Wykorzystać rekurencje.
    void inorder(Node *ptr)
    {
        if (ptr == NULL)
            return;

        inorder(ptr->childL);
        cout << ptr->data << endl;
        inorder(ptr->childR);
    }
    void preorder(Node *ptr)
    {
        if (ptr == NULL)
            return;

        cout << ptr->data << endl;
        preorder(ptr->childL);
        preorder(ptr->childR);
    }
    void postorder(Node *ptr)
    {
        if (ptr == NULL)
            return;

        postorder(ptr->childL);
        postorder(ptr->childR);
        cout << ptr->data << endl;
    }
};

#endif