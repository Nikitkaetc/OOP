#include "stdafx.h"
#include "Vector.h"
using namespace std;

int main()
{
	vector<double> vec = FillVector();
	vec = VectorTransform(vec);
	PrintVector(vec);
	return 0;
}

