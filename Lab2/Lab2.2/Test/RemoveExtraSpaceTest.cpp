#include "stdafx.h"
#include "../RemoveExtraSpaces/RemoveExtraSpaces.h"

BOOST_AUTO_TEST_SUITE(StringTest)

BOOST_AUTO_TEST_CASE(RemoveExtraSpacesTest)
{
	BOOST_CHECK(RemoveExtraSpaces("       Ni         k it     a   ")== "Ni         k it     a");
	BOOST_CHECK(RemoveExtraSpaces("  he   l   l    o")== "he   l   l    o");
	BOOST_CHECK(RemoveExtraSpaces("  H   ow a   re y  ou   ?  ") == "H   ow a   re y  ou   ?");
}

BOOST_AUTO_TEST_SUITE_END()