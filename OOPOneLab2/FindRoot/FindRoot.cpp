#include "stdafx.h"
#include "FindRoot.h"
#include <iomanip>
#include <iostream>
using namespace std;

float Discriminant(float a, float b, float c)
{
	return b*b - 4 * a*c;
}

float Root(float a, float b, float discr)
{
	return ((-b + discr) / (2 * a));
}

float CheckOnCorrect(char argument[])
{
	if (atof(argument) || argument[0] == '0')
	{
		return atof(argument);
	}
	else
	{
		throw invalid_argument("Not correct input");
	}
}