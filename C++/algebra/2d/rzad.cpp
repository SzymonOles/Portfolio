#include <iostream>
using namespace std;

#define M 4 //wyskosc
#define N 4  //szerokosc

//funkcja z mojego programu 2b do obliczania wyznacznika
int wyznacznik(int n, int A[M][N]) //rozmiar macierz
{
    int temp[M][N], a, b, suma = 0, znak = 1;

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

int main()
{
    int A[M][N] ={{1, 3, -2, 4}, {1, -1, 3, 5}, {0, 1, 4, -2}, {10, -2, 5, 1}}; //macierz
    //{{1, 2, 3}}
    //{{4, 6, 2}, {3, 1, 4}, {1, -2, 3}, {2, 5, 1}};
    //{{2, 8, 3, -4}, {1, 4, 1, -2}, {5, 20, 0, -10}, {-3, -12, -2, 6}};
    int subA[M][N];
    int rzad = M < N ? M : N;

    while (rzad > 0)
    {
        for (int i = 0; i <= M; i++)
        {
            for (int j = 0; j <= N; j++) //dla kazdej liczby w macierzy
            {
                for (int x = 0; x < rzad; x++)
                {
                    for (int y = 0; y < rzad; y++) //wypelnij podmacierz o rozmiarze rzad x rzad zaczynajac od danej liczby(przechodzi przez sciany)
                    {
                        subA[x][y] = A[(i + x) % M][(j + y) % N];
                    }
                }
                if (wyznacznik(rzad, subA))//jesli wyznacznik rozny od zera koniec zadania
                {
                    cout << "rzad: " << rzad;
                    return 0;
                }
            }
        } //jesli dla zadnej kombinacji macierzy nie znaleziono liczby innej niz zero zmiejsz rzad
        rzad--; //dla rzedu 1 zawsze bedzie rozwiazanie chyba ze maciez to same zera
    }
    cout<<"macierz zerowa";
    return 1;
}