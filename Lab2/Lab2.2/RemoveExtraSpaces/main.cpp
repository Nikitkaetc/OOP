#include "stdafx.h"
#include "RemoveExtraSpaces.h"
using namespace std;

int main()
{
	string arg = ReadingString();
	arg = RemoveExtraSpaces(arg);
	PrintString(arg);
	return 0;
}

