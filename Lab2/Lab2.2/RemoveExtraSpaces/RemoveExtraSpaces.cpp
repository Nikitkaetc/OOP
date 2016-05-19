#include "stdafx.h"
#include "RemoveExtraSpaces.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <boost/algorithm/string.hpp>
using namespace std;

string RemoveExtraSpaces(string const& arg)
{
	string str = arg;
	if (!str.empty())
	{
		boost::trim(str);
	}
	return str;
}

string ReadLineFromConsole()
{
	string str;
	getline(cin, str);
	return str;
}

void PrintString(string const& arg)
{
	copy(arg.begin(), arg.end(), ostream_iterator<char>(cout, ""));
}