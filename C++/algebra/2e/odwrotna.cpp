#include <iostream>
#include <iomanip>
using namespace std;

#define N 3

void wypisz(double detA[N][N])//testowe wypisanie macierzy
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            cout<<setw(15)<<detA[i][j];
        }
        cout << endl;
    }
}

//funkcja z mojego programu 2b do obliczania wyznacznika
int wyznacznik(int n, double A[N][N]) //rozmiar macierz
{
    double temp[N][N];
    int a, b, suma = 0, znak = 1;

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
    double A[N][N] = {{3, 5, 3}, {7, 9, 19}, {-4, 5, 11}}; //macierz
    //{{3, 5, 3}, {7, 9, 19}, {-4, 5, 11}};
    //{{-1,1,2}, {3,-9,1}, {2,-8,3}};
    double detA[N][N];
    double tempA[N][N];
    double temp;
    const int m = N - 1; //rozmiar temp
    int a, b;

    int det = wyznacznik(N, A);

    if (det == 0)
    {
        cout << "Macierz osobliwa";
        return 0;
    }

    int znak = 1;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) //dla kazdego elem macierzy
        {
            a = 0;
            b = 0;
            for (int x = 0; x < N; x++) //wypelnij podmacierz
            {
                if (x==i)
                {
                    continue;
                }
                for (int y = 0; y < N; y++)
                {
                    if (y == j)
                    {
                        continue;
                    }
                    tempA[a][b] = A[x][y];
                    b++;
                }
                a++;
                b = 0;
            }
            detA[i][j] = znak * wyznacznik(m, tempA); //wylicz element macierzy dopelnien
            znak *= -1;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) //macierz tranzpozytowa
        {
            if (i < j)
            {
                temp = detA[i][j];
                detA[i][j] = detA[j][i];
                detA[j][i] = temp;
            }
            else
            {
                continue;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) //dzielenie przez wyznacznik
        {
            detA[i][j] /= det;
        }
    }
    wypisz(detA);
    return 0;
}