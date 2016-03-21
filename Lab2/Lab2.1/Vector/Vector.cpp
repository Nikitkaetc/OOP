#include "stdafx.h"
#include "Vector.h"
#include <iterator>
#include <algorithm>
#include <iostream>
using namespace std;
using namespace boost::phoenix::placeholders;

vector<double> FillVector()
{
	return{ istream_iterator<double>(cin), (istream_iterator<double>()) };
}


vector<double> VectorTransform(vector<double> &vec)
{
	if (vec.empty() != 0)
	{
		auto minElement = min_element(vec.begin(), vec.end());
		boost::transform(vec, vec.begin(), arg1 / float(*minElement));
		sort(vec.begin(), vec.end());
	}
	return vec;
}

void PrintVector(const vector<double> &vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}