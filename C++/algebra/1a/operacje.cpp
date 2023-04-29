#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;

int main()
{
    //wpisywanie
    double a,b,c,d;
    cout<<"podaj Re(w) :\n";
    cin>>a;
    cout<<"podaj Im(w) :\n";
    cin>>b;
    cout<<"podaj Re(z) :\n";
    cin>>c;
    cout<<"podaj Im(z) :\n";
    cin>>d;
    cout<<"================\n";
    //obliczenia i wypisanie
    cout.setf( ios::showpos ); //format cout
    cout<<"w+z= "<<a+c<<" "<<b+d<<"i\n";
    cout<<"w-z= "<<a-c<<" "<<b-d<<"i\n";
    cout<<"w*z= "<<(a*c)-(b*d)<<" "<<(a*d)+(b*c)<<"i\n";
    cout<<"w/z= "<<((a*c)+(b*d))/((c*c)+(d*d))<<" "<<((b*c)-(a*d))/((c*c)+(d*d))<<"i\n";
    cout<<"|w|= "<<sqrt((a*a)+(b*b))<<"\n";
    cout<<"z* = "<<c<<" "<<-d<<"i\n";
    getch();
    return 0;
}
