#include <cstdio>
#include <cmath>

double NWD(double a, double b)
{
    a=abs(a);
    b=abs(b);
    if (a == 0 || b == 0)
    {
        return 1;
    }
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    return a;
}

int main()
{
    double A[2][2] = {{5, -4}, {2, -1}}; //wpisywanie
    double temp1[2][2], temp2[2][2];
    double a, b, c;
    double del, sqdel;
    double x1, x2;
    double v11, v12, v21, v22;
    double nwd1, nwd2;

    //wartosci przy rownaniu wyznacznika
    a = 1;
    b = (-1) * (A[0][0] + A[1][1]);
    c = (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);

    //delta i wartosci wlasne
    del = (b * b) - (4 * (a * c));
    sqdel = sqrt(del);
    x1 = (((-1) * (b)) - (sqdel)) / (2 * a);
    x2 = (((-1) * (b)) + (sqdel)) / (2 * a);

    //podstawianie wartosci wlasnych
    temp1[0][0] = A[0][0] - (x1);
    temp1[0][1] = A[0][1];
    temp1[1][0] = A[1][0];
    temp1[1][1] = A[1][1] - (x1);

    temp2[0][0] = A[0][0] - (x2);
    temp2[0][1] = A[0][1];
    temp2[1][0] = A[1][0];
    temp2[1][1] = A[1][1] - (x2);

    //szukanie wektorow wlasnych
    v11 = (temp1[0][1]) * (-1);
    v12 = temp1[0][0];

    v21 = (temp2[0][1]) * (-1);
    v22 = temp2[0][0];

    //dla macierzy gdzie zera poza diagonala
    if (A[0][1] == 0 && A[1][0] == 0)
    {
        v11 = 1;
        v12 = 0;

        v21 = 0;
        v22 = 1;
    }

    //skracanie
    nwd1 = NWD(v11, v12);
    nwd2 = NWD(v21, v22);

    v11 /= nwd1;
    v12 /= nwd1;
    v21 /= nwd2;
    v22 /= nwd2;

    printf("dla lambda1: %.0f : { %.0f , %.0f }\n", x1, v11, v12);
    printf("dla lambda2: %.0f : { %.0f , %.0f }\n", x2, v21, v22);

    return 0;
}
