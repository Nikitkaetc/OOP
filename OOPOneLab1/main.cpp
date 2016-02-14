#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


bool SearchForWord(const string &strfile, const string &word)
{
	if (strfile.find(word) != string::npos)
	{
		return true;
	}
	return false;
}

vector<int> SearchLineNumber(const string &filename, const string &word)
{
	ifstream f;
	f.open(filename);
	if (!f.is_open())
	{
		throw invalid_argument("Text not found");
	}
	int counterStr = 0;
	string strfile;
	vector<int> lineNumbers;
	while (!f.eof())
	{
		getline(f, strfile);
		counterStr++;
		if (SearchForWord(strfile, word))
		{
			lineNumbers.push_back(counterStr);
		}
	}
	return lineNumbers;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "<file name> <text to search>" << endl;
		return 1;
	}
	string filename = argv[1];
	string word = argv[2];
	vector<int> lineNumbers;
	try
	{
		lineNumbers = SearchLineNumber(filename, word);
	}
	catch(const invalid_argument &err)
	{
		cout << err.what() << endl;
	}
	if (lineNumbers.size() == 0)
	{
		cout << "Text not found" << endl;
		return 1;
	}
	else
	{
		for (const auto &line : lineNumbers)
		{
			cout << line << endl;
		}
	}
	return 0;
}