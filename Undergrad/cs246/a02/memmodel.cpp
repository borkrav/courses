#include <iostream>
using namespace std;

int j = 13;
int * p = & j;   // Find the address of j
double D2 = 1002;
long long L3 = 1003;

double sum (double a, double b)
{
	cout << "  Enter 'sum'" << endl;
	double c = a + b;
	cout << "    a  at " << & a << " = " << a << " " << sizeof(a) << endl;
	cout << "    b  at " << & b << " = " << b << " " << sizeof(b) << endl;
	cout << "    c  at " << & c << " = " << c << " " << sizeof(c) << endl;
	cout << "  Leave 'sum'" << endl;
	return c;
}

double twice (double d)
{
	cout << "Enter 'twice'" << endl;
	double * q;
	q = new double;
	*q = d;
	double e = sum(*q, *q);
	
	cout << "    d  at " << & d << " = " << d << endl;
	cout << "    q  at " << & q << " = " << q << endl;
	cout << "   *q  at " <<   q << " = " <<*q << endl;
	cout << "Leave 'twice'" << endl;
	return e;
}

int main(int argc, char* argv[])
{
	cout << "Enter 'main'" << endl;
	double f = 3.3;
	
	cout << "    j  at " << & j  << " = " << j  << " size "
	<< sizeof(j)   << endl;
	cout << "    p  at " << & p  << " = " << p  << " size "
	<< sizeof(p)   << endl;
	cout << "    D2 at " << & D2 << " = " << D2 << " size "
	<< sizeof(D2)  << endl;
	cout << "    L3 at " << & L3 << " = " << L3 << " size "
	<< sizeof(L3)  << endl;
	
	cout << "    f  at " << &  f << " = " << f << " " << sizeof(f)  << endl;
	
	double sumResult = sum(1.1, f);
	double twiceResult = twice (1.3);
	cout << "Sum of 1.1 and 3.3 = " << sumResult << endl;
	cout << "Twice 1.3 =          " << twiceResult << endl;
	cout << "Leave 'main'" << endl;
	return 0;
}

