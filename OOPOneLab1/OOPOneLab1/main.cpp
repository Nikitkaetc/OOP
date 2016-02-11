#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;


int main(int argc, char *argv[])
{
	srand(time(0));
	if (argc != 3)
	{
		cout << "Надо вводить exe имя файла и название строки для поиска через пробел, если вы вводите фразу то в кавычках" << endl;
		return 1;
	}
	bool IsCoincidence;
	bool IsFound;
	string str;
	setlocale(LC_ALL, "rus");
	int counterStr = 0;
	string filename = argv[1];
	string word = argv[2];
	ifstream f;
	f.open(filename);
	if (!f.is_open())
	{
		cout << "Файл не найден" << endl;
		return 1;
	}
	IsFound = false;
	while (!f.eof())
	{
		getline(f, str);
		counterStr++;
		IsCoincidence = false;
		int counterWord = 0;
		for (int i = 0; i <= (str.length()); i++)
		{
			if (counterWord == word.length())
			{
				break;
			}
			else
			{
				if (str[i] == word[0])
				{
					counterWord = 1;
					for (int j = 1; j <= (word.length() - 1); j++)
					{
							if (str[i + 1] == word[j])
							{
								counterWord++;
								i++;
								IsCoincidence = true;
							}
							else
							{
								IsCoincidence = false;
								counterWord = 0;
								break;
							}
					}
				}
			}
		}
		if (IsCoincidence == true)
		{
			cout << counterStr << endl;
			IsFound = true;
		}
	}
	f.close();
	if (IsFound == false)
	{
		cout << "Text not found" << endl;
		cout << "runtime = " << clock() / 1000.0 << endl;
		return 1;
	}
	else
	{
	cout << "runtime = " << clock() / 1000.0 << endl;
	return 0;
	}
}