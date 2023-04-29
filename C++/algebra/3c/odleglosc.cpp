#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    char n1[] = {"odleglosc punktu P1 od linii punktow P2 P3"};
    char n2[] = {"odleglosc punktu P2 od linii punktow P1 P3"};
    char n3[] = {"odleglosc punktu P3 od linii punktow P1 P2"};
    double d1, d2, d3;
    double vector[3], PP[3], PPxV[3];
    //wpisywanie wartosci
    double P0[3] = {1, 4, 5};
    double P1[3] = {-3, 2.1, 4};
    double P2[3] = {0, 0, -2};

    //znajdowanie odleglosci punkt P0 linia P1 P2
    vector[0] = P2[0] - P1[0];
    vector[1] = P2[1] - P1[1];
    vector[2] = P2[2] - P1[2];

    PP[0] = P1[0] - P0[0];
    PP[1] = P1[1] - P0[1];
    PP[2] = P1[2] - P0[2];

    PPxV[0] = (PP[1] * vector[2]) - (PP[2] * vector[1]);
    PPxV[1] = (PP[0] * vector[2]) - (PP[2] * vector[0]);
    PPxV[2] = (PP[0] * vector[1]) - (PP[1] * vector[0]);

    d1 = (sqrt((PPxV[0] * PPxV[0]) + (PPxV[1] * PPxV[1]) + (PPxV[2] * PPxV[2]))) / (sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2])));

    //znajdowanie odleglosci punkt P1 linia P0 P2
    vector[0] = P2[0] - P0[0];
    vector[1] = P2[1] - P0[1];
    vector[2] = P2[2] - P0[2];

    PP[0] = P0[0] - P1[0];
    PP[1] = P0[1] - P1[1];
    PP[2] = P0[2] - P1[2];

    PPxV[0] = (PP[1] * vector[2]) - (PP[2] * vector[1]);
    PPxV[1] = (PP[0] * vector[2]) - (PP[2] * vector[0]);
    PPxV[2] = (PP[0] * vector[1]) - (PP[1] * vector[0]);

    d2 = (sqrt((PPxV[0] * PPxV[0]) + (PPxV[1] * PPxV[1]) + (PPxV[2] * PPxV[2]))) / (sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2])));

    //znajdowanie odleglosci punkt P2 linia P0 P1
    vector[0] = P1[0] - P0[0];
    vector[1] = P1[1] - P0[1];
    vector[2] = P1[2] - P0[2];

    PP[0] = P0[0] - P2[0];
    PP[1] = P0[1] - P2[1];
    PP[2] = P0[2] - P2[2];

    PPxV[0] = (PP[1] * vector[2]) - (PP[2] * vector[1]);
    PPxV[1] = (PP[0] * vector[2]) - (PP[2] * vector[0]);
    PPxV[2] = (PP[0] * vector[1]) - (PP[1] * vector[0]);

    d3 = (sqrt((PPxV[0] * PPxV[0]) + (PPxV[1] * PPxV[1]) + (PPxV[2] * PPxV[2]))) / (sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2])));

    cout << n1 << ": " << d1 << endl;
    cout << n2 << ": " << d2 << endl;
    cout << n3 << ": " << d3 << endl
         << endl;

    if (d1 > d2 && d1 > d3)
    {
        cout << "najwieksza jest " << n1 << endl
             << "1";
    }
    else if (d2 > d1 && d2 > d3)
    {
        cout << "najwieksza jest " << n2 << endl
             << "2";
    }
    else if (d3 > d1 && d3 > d2)
    {
        cout << "najwieksza jest " << n3 << endl
             << "3";
    }
    else
    {
        cout << "blad";
    }

    return 0;
}
