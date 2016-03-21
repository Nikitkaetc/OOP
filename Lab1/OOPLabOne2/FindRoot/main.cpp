#include "stdafx.h"
#include "FindRoot.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <iterator>
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
		a = stof(argv[1]);
		b = stof(argv[2]);
		c = stof(argv[3]);
	}
	catch (const invalid_argument &err)
	{
		cout << "It isnt number"<< endl;
		return 1;
	}
	auto roots = SolveEquation(a, b, c);
	if (roots.empty())
	{
		cout << "There is no real root" << endl;;
		return 1;
	}
	else
	{
		copy(roots.begin(), roots.end(), ostream_iterator<float>(cout, " "));
	}
	return 0;
}