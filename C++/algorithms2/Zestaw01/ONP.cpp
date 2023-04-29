#include <iostream>
#include "ArrayStack.hpp"
#define STACKSIZE 100

using namespace std;

int main(int argc, char const *argv[])
{
    //tworzenie stosu
    StackChar stos(STACKSIZE);

    string buf;
    int liczba;
    char chr;
    int licznik=0;

    do
    {
        cin >> buf;
        if (sscanf(buf.c_str(), "%d", &liczba) != 0) //czy liczba
        {
            cout << liczba << " ";
        }
        else if (buf == "(")
        {
            licznik++;
        }
        else if (buf == ")")
        {
            cout << stos.pop() << " ";
            licznik--;
        }
        else if (buf == "*" || buf == "/" || buf == "+" || buf == "-")
        {
            chr = buf[0];
            stos.push(chr);
        }
        else
        {
            break;
        }
    } while (licznik!=0);
    return 0;
}
