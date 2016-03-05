#include "stdafx.h"
#include "FindRoot.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

float Discriminant(float a, float b, float c)
{
	return b*b - 4 * a*c;
}

float Root(float a, float b, float discr)
{
	return ((-b + discr) / (2 * a));
}

void PrintRoot(float a, float b, float discr)
{
	if (discr > 0)
	{
		cout << setprecision(4) << Root(a, b, sqrt(discr)) << endl;
		cout << setprecision(4) << Root(a, b, -sqrt(discr)) << endl;
	}
	else
	{
		cout << setprecision(4) << Root(a, b, 0) << endl;
	}
}