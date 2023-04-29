#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    if (argc != 3)
    {
        cout << "nieodpowiednie argumenty - podaj n , max\n";
        return 1;
    }

    // wczytywanie argumentow
    int n = atoi(argv[1]);
    int max = atoi(argv[2]);

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            cout << ((rand() % max) + 1);
        }
        else
        {
            cout << ((rand() % max) + 1) << endl;
        }
    }

    return 0;
}
