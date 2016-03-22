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


vector<double> VectorTransform(vector<double> const& vec)
{
	vector<double> vect = vec;
	if (!vect.empty())
	{
		auto minElement = min_element(vect.begin(), vect.end());
		boost::transform(vect, vect.begin(), arg1 / static_cast<float>(*minElement));
		sort(vect.begin(), vect.end());
	}
	return vect;
}

void PrintVector(const vector<double> &vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<double>(cout, " "));
}