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
		a = IsNumber(argv[1]);
		b = IsNumber(argv[2]);
		c = IsNumber(argv[3]);
	}
	catch (const invalid_argument &err)
	{
		cout << err.what() << endl;
		return 1;
	}
	if (Discriminant(a, b, c) < 0)
	{
		cout << "There is no real root" << endl;
		return 1;
	}
	else
	{
		PrintRoot(a, b, Discriminant(a, b, c));
	}
	return 0;
}