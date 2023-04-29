#include <iostream>
#include "ArrayStack.hpp"
#define STACKSIZE 1000

using namespace std;

int main(int argc, char const *argv[])
{
    //tworzenie stosu
    Stack s(STACKSIZE);

    int rep;
    char znak;
    int liczba;
    int dummy;

    //obsluga wejscia i komendy na stosie
    scanf("%d", &rep);

    for (int i = 0; i < rep; i++) //ilosc powtorzen
    {
        scanf("%d", &dummy);
        scanf("%c", &znak); //skan znaku
        if (znak == 'A')
        {
            scanf("%d", &liczba);
            try
            {
                s.push(liczba);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (znak == 'D')
        {
            if (s.empty() == 1)
            {
                cout << "EMPTY\n";
            }
            else
            {
                try
                {
                    cout << s.pop() << endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        else if (znak == 'S')
        {
            cout<< s.size() << endl;
        }
        else
        {
            cout << "nie wykryto znaku\n";
        }
    }

    return 0;
}
