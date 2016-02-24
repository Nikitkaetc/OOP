#include "stdafx.h"
#include "../FindText/FindText.h"
BOOST_AUTO_TEST_SUITE(FindTextTest)


BOOST_AUTO_TEST_CASE(SearchFileForTextTest)
{
	std::vector<int> t1 = { 6 };
	std::vector<int> t2 = { 1,8 };
	std::vector<int> voidvector = {};
	BOOST_CHECK(SearchFileForText("input.txt", "Very good")== t1);
	BOOST_CHECK(SearchFileForText("input.txt", "Check") == t2);
	BOOST_CHECK(SearchFileForText("voidfile.txt", "going") == voidvector);
	BOOST_CHECK_THROW(SearchFileForText("defunct.txt", "are"),std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(StringContainsTextTest)
{
	BOOST_CHECK_EQUAL(StringContainsText("Visual Studio", "under"),false);
	BOOST_CHECK_EQUAL(StringContainsText("Visual Studio", "Studio"), true);
	BOOST_CHECK_EQUAL(StringContainsText("No errors detected", "errors"), true);
}

BOOST_AUTO_TEST_SUITE_END()