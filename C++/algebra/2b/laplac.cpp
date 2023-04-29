#include <iostream>
#define N 3                                         //wpisanie rozmiaru macierzy
using namespace std;

int wyznacznik(int n, int A[N][N])
{
    int temp[N][N], a, b, suma = 0, znak = 1; //dla wygody robie wieksze macierze ale ich nie uzywam calych

    if (n == 1)
    {
        return (A[0][0]); //dla macierzy 1x1 zwraca jedyny element ktory jest wyznacznikem
    }
    for (int i = 0; i < n; i++)
    {
        a = 0;
        b = 0;

        for (int j = 1; j < n; j++) //wypelnianie podmacierzy
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
    int A[N][N] = {{1, 2, 3},                       //wpisanie macierzy
                   {6, 5, 4},
                   {3, 7, 2}};
    cout << wyznacznik(N, A) << endl;
    return 0;
}
