#include "stdafx.h"
#include "../RemoveExtraSpaces/RemoveExtraSpaces.h"

BOOST_AUTO_TEST_SUITE(StringTest)

BOOST_AUTO_TEST_CASE(RemoveExtraSpacesTest)
{
	BOOST_CHECK(RemoveExtraSpaces("       Ni         k it     a   ")== "Nikita");
	BOOST_CHECK(RemoveExtraSpaces("  he   l   l    o")== "hello");
	BOOST_CHECK(RemoveExtraSpaces("  H   ow a   re y  ou   ?  ") == "Howareyou?");
}

BOOST_AUTO_TEST_SUITE_END()