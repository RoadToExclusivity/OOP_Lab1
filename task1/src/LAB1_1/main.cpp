#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int CalcCurrentPrefixFunctionValue(const string &pattern, 
								   const vector<int> &patternPrefixFunction, 
								   int prevPrefixFunctionValue, char c)
{
	int k = prevPrefixFunctionValue;
	while (k > 0 && c != pattern[k])
		k = patternPrefixFunction[k - 1];
	if (c == pattern[k])
		k++;

	return k;
}

void CalcPrefixFunctionOnRange(const string &pattern, vector<int> &prefixFunction)
{
	int curPrefixFunctionValue = 0;
	for (size_t i = 1; i < pattern.length(); i++)
	{
		curPrefixFunctionValue = CalcCurrentPrefixFunctionValue(pattern, prefixFunction, curPrefixFunctionValue, pattern[i]);
		prefixFunction[i] = curPrefixFunctionValue;
	}
}

void DoReplace(ifstream &fin, ofstream &fout, const string &searchString, 
											  const string &replaceString)
{
	string pattern = searchString + '`', curLine = "", s = "";
	int patternLength = pattern.length();
	
	vector<int> prefixFunction(patternLength);
	CalcPrefixFunctionOnRange(pattern, prefixFunction);

	int curPrefixFunctionValue, searchStringLength = searchString.length(), writingPos;
	while (getline(fin, curLine))
	{
		curPrefixFunctionValue = prefixFunction[patternLength - 1];
		writingPos = 0;
		for (int i = 0; i < curLine.length(); i++)
		{
			curPrefixFunctionValue = CalcCurrentPrefixFunctionValue(pattern, prefixFunction, curPrefixFunctionValue, curLine[i]);
			if (curPrefixFunctionValue == searchStringLength)
			{
				fout << replaceString;
				writingPos = i + 1;
				curPrefixFunctionValue = prefixFunction[patternLength - 1];
			}
			else
			{
				if (writingPos + searchStringLength <= i + 1)
				{
					fout << curLine[writingPos++];
				}
			}
		}

		if (writingPos < curLine.length())
		{
			for (size_t i = writingPos; i < curLine.length(); i++)
			{
				fout << curLine[i];
			}
		}
		if (!fin.eof())
			fout << endl;
	}
}

int main(int argc, char *argv[]){

	if (argc < 5)
	{
		printf("Not enough parameters\n");
		return 0;
	}

	ifstream fin(argv[1]);
	if (!fin)
	{
		printf("Error with opening input file %s\n", argv[1]);
		return 1;
	}
	
	if (!strcmp(argv[1], argv[2]))
	{
		printf("Same file\n");
		fin.close();
		return 1;
	}

	ofstream fout(argv[2]);
	if (!fout)
	{
		printf("Error with opening output file %s\n", argv[2]);
		fin.close();
		return 1;
	}
	
	string searchString = argv[3], replaceString = argv[4];
	DoReplace(fin, fout, searchString, replaceString);

	fin.close();
	fout.close();
	
	return 0;
}