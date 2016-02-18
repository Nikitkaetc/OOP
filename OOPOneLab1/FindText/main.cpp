#include "stdafx.h"
#include "FindText.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Usage : <file name> <text to search>" << endl;
		return 1;
	}
	string filename = argv[1];
	string needle = argv[2];
	vector<int> lineNumbers;
	try
	{
		lineNumbers = SearchFileForText(filename, needle);
	}
	catch (const invalid_argument &err)
	{
		cout << err.what() << endl;
		return 1;
	}
	if (!IsEmpty(lineNumbers))
	{
		for (const auto &line : lineNumbers)
		{
			cout << line << endl;
		}
	}
	else
	{
		cout << "Text not Found" << endl;
		return 1;
	}
	return 0;
}