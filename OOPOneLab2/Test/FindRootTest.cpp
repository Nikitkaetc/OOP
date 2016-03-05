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

BOOST_AUTO_TEST_CASE(RootTest)
{
	BOOST_CHECK_EQUAL(Root(2, 5, sqrt(25)), 0);
	BOOST_CHECK_EQUAL(Root(2, 5.5, -sqrt(30.25)), -2.75);
}

BOOST_AUTO_TEST_SUITE_END()