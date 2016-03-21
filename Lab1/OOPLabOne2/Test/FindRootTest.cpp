#include "stdafx.h"
#include "../FindRoot/FindRoot.h"

BOOST_AUTO_TEST_SUITE(FindRootTest)

BOOST_AUTO_TEST_CASE(DiscriminantTest)
{
	BOOST_CHECK_EQUAL(Discriminant(2, 5, 0), 25);
	BOOST_CHECK_EQUAL(Discriminant(8, 2, 1), -28);
	BOOST_CHECK_EQUAL(Discriminant(2, 4, 2), 0);
	BOOST_CHECK_EQUAL(Discriminant(-1.1875, 4.5, 1), 25);
}

BOOST_AUTO_TEST_CASE(SolveEquationTest)
{
	std::vector<float> t1 = { -0.5,-2 };
	std::vector<float> t2 = { -1 };
	std::vector<float> voidvector = {};
	BOOST_CHECK(SolveEquation(2, 5, 2) == t1);
	BOOST_CHECK(SolveEquation(2, 4, 2) == t2);
	BOOST_CHECK(SolveEquation(1, 2, 24) == voidvector);
}
BOOST_AUTO_TEST_SUITE_END()