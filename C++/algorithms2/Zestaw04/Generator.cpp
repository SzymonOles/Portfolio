#include <iostream>
#include <cstdlib>
#include <time.h>

#define NUMSIZE 1000

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int size = 0;
    int temp, temp2;

    if (argc != 2)
    {
        cout << "nieodpowiednie argumenty\n";
        return 1;
    }

    // wczytywanie ilosci komend
    int cmds = atoi(argv[1]);
    cout << cmds << endl;

    for (int i = 0; i < cmds; i++)
    {
        temp = rand() % 6;
        switch (temp)
        {
            // F
        case 0:
            cout << "F ";
            temp2 = (rand() % NUMSIZE + 1);
            cout << temp2 << endl;
            size++;
            break;
            // B
        case 1:
            cout << "B ";
            temp2 = (rand() % NUMSIZE + 1);
            cout << temp2 << endl;
            size++;
            break;
            // f
        case 2:
            cout << "f" << endl;
            break;
            // b
        case 3:
            cout << "b" << endl;
            break;
            //R
        case 4:
            cout << "R ";
            temp2 = (rand() % NUMSIZE + 1);
            cout << temp2 << " ";
            temp2 = (rand() % NUMSIZE + 1);
            cout << temp2 << endl;
            break;
            //S
        case 5:
            cout << "S" << endl;
            break;

        default:
            cout << "error\n";
            break;
        }
    }

    return 0;
}
