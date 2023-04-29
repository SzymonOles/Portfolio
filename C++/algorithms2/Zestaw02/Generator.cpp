#include <iostream>
#include <cstdlib>
#include <time.h>

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

    //wczytywanie ilosci komend
    int cmds = atoi(argv[1]);
    cout << cmds << endl;

    for (int i = 0; i < cmds; i++)
    {
        temp = rand() % 3;
        switch (temp)
        {
            //A
        case 0:
            cout << "A ";
            temp2 = (rand() % 99 + 1);
            cout << temp2 << endl;
            size++;
            break;
            //S
        case 1:
            cout << "S" << endl;
            break;
            //D
        case 2:
            //  if (size == 0)
            //  {
            //   i--;
            //   continue;
            //  }
            //  else
            //  {
            cout << "D" << endl;
            //  size--;
            //  }
            break;

        default:
            cout << "error\n";
            break;
        }
    }

    return 0;
}
