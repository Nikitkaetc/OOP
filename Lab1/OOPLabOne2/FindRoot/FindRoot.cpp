#include "stdafx.h"
#include "FindRoot.h"
using namespace std;

float Discriminant(float a, float b, float c)
{
	return b*b - 4 * a*c;
}

vector<float> SolveEquation(float a, float b, float c)
{
	float discr = Discriminant(a, b, c);
	vector<float> roots;
	if (discr > 0)
	{
		roots.push_back((-b + sqrt(discr)) / (2 * a));
		roots.push_back((-b - sqrt(discr)) / (2 * a));
	}
	else if (discr == 0)
	{
		roots.push_back(-b / (2 * a));
	}
	return roots;
}
