#include "stdafx.h"
#include "../Vector/Vector.h"


BOOST_AUTO_TEST_SUITE(VectorTest)

BOOST_AUTO_TEST_CASE(VectorTransformTest)
{
	std::vector<double> t1{ 1,2,4,6 };
	std::vector<double> t2{ -12,-3,1 };
	std::vector<double> t3{};
	std::vector<double> p1{ 4,2,12,8 };
	std::vector<double> p2{ 36,-3 ,9 };
	std::vector<double> p3{};
	BOOST_CHECK(VectorTransform(p1) == t1);
	BOOST_CHECK(VectorTransform(p2) == t2);
	BOOST_CHECK(VectorTransform(p3) == t3);
}

BOOST_AUTO_TEST_SUITE_END()
