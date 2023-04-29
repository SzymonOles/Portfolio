#include <iostream>

#define n 3

//{{2, -2, 3},{-1, 5, -1},{3, 1, 2}}
//{{2, -1, 5}, {2, 4, 6}, {4, 3, 11}}
//robie te zmienne globalne zeby bez zabawy wypisywac sobie cala macierz z funkcji
int i = 0, j = 0;
double dzielnik, wielo[n], temp[n], A[n][n];

void test()
{
    for (int g1 = 0; g1 < n; g1++)
    {
        std::cout << std::endl;
        for (int g23 = 0; g23 < n; g23++)
        {
            std::cout << A[g1][g23] << " ";
        }
    }
    std::cout << std::endl
              << "---------";
}

int main()
{
    //wpisywanie
    std::cout << "wpisz wektory\n";
    for (int y = 0; y < n; y++)
    {
        for (int z = 0; z < n; z++)
        {
            std::cout << "A[" << y << "," << z << "]=";
            std::cin >> A[y][z];
        }
    }

poczatek:
    if (A[i][i] == 0) //czy i i jest niezerowe
    {
        for (j = i; j < n; j++)
        {
            if (A[j][i] != 0) //czy w itej kolumnie w dol od i jest niezerowy
            {                 //jesli nie zamien miejscami
                for (int k = 0; k < n; k++)
                {
                    temp[k] = A[j][k];
                }
                for (int k = 0; k < n; k++)
                {
                    A[j][k] = A[i][k];
                }
                for (int k = 0; k < n; k++)
                {
                    A[i][k] = temp[k];
                }
                break;
            }
            else //jesli tak koniec
            {
                std::cout << "\nNIE\n";
                return 0;
            }
        }
    }
    //podziel ity wiersz
    dzielnik = A[i][i];
    for (int k = 0; k < n; k++)
    {
        A[i][k] /= dzielnik;
    }
    test();
    //odejmij
    for (int k = 0; k < n; k++)
    {
        if (k == i)
            continue;
        wielo[k] = (A[k][i]);
    }
    for (int k = 0; k < n; k++)
    {
        if (k == i)
            continue;
        for (int l = 0; l < n; l++)
        {
            A[k][l] -= (A[i][l] * wielo[k]);
        }
    }
    test();
    i++;       //inkrementuj i
    if (i < n) //sprawdz warunek
    {
        goto poczatek;
    }
    else
    {
        std::cout << "\nTAK\n";
        return 0;
    }

    std::cout << "to sie nie powinno pojawic\n";
    return 1;
}
