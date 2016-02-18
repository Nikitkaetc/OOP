#include "stdafx.h"
#include "FindRoot.h"
#include <iostream>
#include <iomanip>
using namespace std;


int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "Usage : <A> <B> <C>" << endl;
		return 1;
	}
	if (argv[1] == 0)
	{
		cout << "Not quadratic equation" << endl;
		return 1;
	}
	float a, b, c;
	try
	{
		a = CheckOnCorrect(argv[1]);
		b = CheckOnCorrect(argv[2]);
		c = CheckOnCorrect(argv[3]);
	}
	catch (const invalid_argument &err)
	{
		cout << err.what() << endl;
		return 1;
	}
	float discr = Discriminant(a, b, c);
	if (discr > 0)
	{
		cout << setprecision(4) << Root(a, b, sqrt(discr)) << endl;
		cout << setprecision(4) << Root(a, b, -sqrt(discr)) << endl;
	}
	else if (discr == 0)
	{
		cout << setprecision(4) << Root(a, b, 0) << endl;
	}
	else
	{
		cout << "There is no real root" << endl;
		return 1;
	}
	return 0;
}