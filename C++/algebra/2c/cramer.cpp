#include <iostream>
#define N 3 //zmienic N dla większych układów (N/N+1)
using namespace std;

int wyznacznik(int n, double A[N][N + 1]) //liczenie wyznacznika macierzy z poprzedniego programu (troche zmodyfikowane zeby przyjmowal n+1 zamiast n)
{
    double temp[N][N + 1], suma = 0;
    int a, b, znak = 1;

    if (n == 1)
    {
        return (A[0][0]);
    }
    for (int i = 0; i < n; i++)
    {
        a = 0;
        b = 0;

        for (int j = 1; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (k == i)
                    continue;
                temp[a][b] = A[j][k];
                b++;
            }
            a++;
            b = 0;
        }
        suma += znak * A[0][i] * wyznacznik(n - 1, temp);
        znak *= -1;
    }
    return suma;
}

int main(int argc, char const *argv[])
{
    //{{1,1,1,3}, {-2,1,2,1}, {-1,2,3,4}}
    //{{3,5,3,25}, {7,9,19,65}, {-4,5,11,5}}
    double A[N][N + 1] = {{3,5,3,25}, {7,9,19,65}, {-4,5,11,5}}; //wpisz układ równań
    //nazwy dla zmiennych
    char zmienna[] = {'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w'};
    double temp[N][N + 1];
    double Wz[N];//wyznacznik zmiennej
    double W;//wyznacznik ogolny

    W = wyznacznik(N, A);
    cout << "W: " << W << endl;

    if (W == 0) //sprawdzanie wyznacznika ogolnego
    {
        cout << "wyznacznik ogólny = 0, nie mozna uzyc metody cramera" << endl;
        return 1;
    }

    for (int i = 0; i < N; i++) //liczenie wyznacznikow dla zmiennych
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N + 1; k++) //wypelnianie tymczasowej tablicy wyznacznika zmiennej
            {
                if (k == i)
                {
                    temp[j][k] = A[j][N];
                }
                else
                {
                    temp[j][k] = A[j][k];
                }
            }
        }

        Wz[i] = wyznacznik(N, temp); //zapisywanie wynikow do tablicy
    }
    for (int i = 0; i < N; i++) //obliczanie wartosci zmiennych
    {
        cout << zmienna[i] << " = " << (Wz[i] / W) << endl;
    }
    return 0;
}
