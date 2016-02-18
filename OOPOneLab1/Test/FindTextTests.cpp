#include "stdafx.h"
#include "../FindText/FindText.h"
BOOST_AUTO_TEST_SUITE(FindTextTest)


BOOST_AUTO_TEST_CASE(SearchFileForTextTest)
{
	std::vector<int> t1 = { 1,4 };
	std::vector<int> t2 = { 4 };
	std::vector<int> voidvector = {};
	BOOST_CHECK(SearchFileForText("input.txt", "qwe")== t1);
	BOOST_CHECK(SearchFileForText("input.txt", "QwE") == t2);
	BOOST_CHECK(SearchFileForText("voidfile.txt", "qwe") == voidvector);
	BOOST_CHECK_THROW(SearchFileForText("defunct.txt", "a"),std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(StringContainsTextTest)
{
	BOOST_CHECK_EQUAL(StringContainsText("Qwert", "qwe"),false);
	BOOST_CHECK_EQUAL(StringContainsText("Qwert", "Qwe"), true);
	BOOST_CHECK_EQUAL(StringContainsText("Qwert qwe", "qwe"), true);
}
	
BOOST_AUTO_TEST_CASE(CheckOnTextFoundTest)
{
	std::vector<int> voidvector = {};
	std::vector<int> t1 = { 1,4 };
	BOOST_CHECK_EQUAL(CheckOnTextFound(voidvector), false);
	BOOST_CHECK_EQUAL(CheckOnTextFound(t1), true);
}

BOOST_AUTO_TEST_SUITE_END()