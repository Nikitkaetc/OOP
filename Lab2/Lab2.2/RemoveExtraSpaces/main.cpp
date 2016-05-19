#include "stdafx.h"
#include "RemoveExtraSpaces.h"
using namespace std;

int main()
{
	string arg = ReadLineFromConsole();
	arg = RemoveExtraSpaces(arg);
	PrintString(arg);
	return 0;
}

