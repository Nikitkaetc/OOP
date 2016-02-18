#include "stdafx.h"
#include "FindText.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


bool StringContainsText(const string & haystack, const string& needle)
{
	return haystack.find(needle) != string::npos;
}

vector<int> SearchFileForText(const string &filename, const string &needle)
{
	ifstream f;
	f.open(filename);
	if (!f.is_open())
	{
		throw invalid_argument("File not open");
	}
	int counterStr = 0;
	string haystack;
	vector<int> lineNumbers;
	while (getline(f, haystack))
	{
		counterStr++;
		if (StringContainsText(haystack, needle))
		{
			lineNumbers.push_back(counterStr);
		}
	}
	return lineNumbers;
}


bool IsEmpty(const vector<int> &lineNumbers)
{
	return lineNumbers.size() == 0;
}