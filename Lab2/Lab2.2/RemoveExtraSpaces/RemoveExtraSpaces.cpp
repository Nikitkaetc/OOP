#include "stdafx.h"
#include "RemoveExtraSpaces.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

string RemoveExtraSpaces(string const& arg)
{
	string str = arg;
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

string ReadingString()
{
	string str;
	getline(cin, str);
	return str;
}

void PrintString(string const& arg)
{
	copy(arg.begin(), arg.end(), ostream_iterator<char>(cout, ""));
}