#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;

int main()
{
    //wpisywanie
    double a,b,r,theta;
    int n;
    cout<<"podaj Re(z) :\n";
    cin>>a;
    cout<<"podaj Im(z) :\n";
    cin>>b;
    cout<<"podaj n :\n";
    cin>>n;
    cout<<"================\n";
    //obliczenia i wypisanie
    cout.setf(ios::showpos); //format cout
    //szukanie r
    r=sqrt((a*a)+(b*b));
    //szukanie thety
    if (b>=0 && r!=0)
    {
        theta=acos(a/r);
    }
    else if (b<0)
    {
        theta=acos(a/r)*(-1);
    }
    else
    {
        cout<<"theta niezdefiniowana, koniec programu";
        getch();
        return 1;
    }
    //liczenie wartosci i wypisanie
    cout<<"z^n = "<<pow(r,n)*cos(n*theta)<<" "<<pow(r,n)*sin(n*theta)<<" i\n";
    getch();
    return 0;
}
