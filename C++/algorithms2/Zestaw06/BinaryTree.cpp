#include <iostream>
#include "BinaryTree.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    BinaryTree B;

    int rep;
    int val;

    cin >> rep;

    for (int i = 0; i < rep; i++)
    {
        cin >> val;
        B.insert(val);
    }

    cout << B.size() << " ";
    cout << B.depth() << " ";
    cout << B.minimum() << " ";
    cout << B.maximum() << endl;
    B.preorder(B.root);
    for (int i = 1; i <= 9; i++)
    {
        if (B.search(i) != NULL)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}
