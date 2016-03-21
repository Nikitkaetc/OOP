#include "stdafx.h"
#include "Vector.h"
using namespace std;

int main()
{
	vector<double> vec = FillVector();
	VectorTransform(vec);
	PrintVector(vec);
	return 0;
}

