#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int CalcCurrentPrefixFunctionValue(const string &pattern, 
								   const vector<size_t> &patternPrefixFunction, 
								   int prevPrefixFunctionValue, char c)
{
	int k = prevPrefixFunctionValue;
	while (k > 0 && c != pattern[k])
		k = patternPrefixFunction[k - 1];
	if (c == pattern[k])
		k++;

	return k;
}

vector<size_t> CalcPatternPrefixFunction(const string &pattern)
{
	vector<size_t> prefixFunction(pattern.length());
	int curPrefixFunctionValue = 0;
	prefixFunction[0] = 0;

	for (size_t i = 1; i < pattern.length(); i++)
	{
		curPrefixFunctionValue = CalcCurrentPrefixFunctionValue(pattern, prefixFunction, curPrefixFunctionValue, pattern[i]);
		prefixFunction[i] = curPrefixFunctionValue;
	}
	
	return prefixFunction;
}

void ReplaceAndPrintString(ofstream &fout, const string &pattern, 
							 const string &searchString, const string &replaceString,
							 const string &curString, const vector<size_t> &patternPrefixFunction)
{
	int curPrefixFunctionValue = 0, writingPos = 0, 
		searchStringLength = searchString.length(), curStringLength = curString.length();

	for (int i = 0; i < curStringLength; i++)
	{
		curPrefixFunctionValue = CalcCurrentPrefixFunctionValue(pattern, patternPrefixFunction, curPrefixFunctionValue, curString[i]);
		if (curPrefixFunctionValue == searchStringLength)
		{
			fout << replaceString;
			writingPos = i + 1;
			curPrefixFunctionValue = 0;
		}
		else
		{
			if (writingPos + searchStringLength <= i + 1)
			{
				fout << curString[writingPos++];
			}
		}
	}

	if (writingPos < curStringLength)
	{
		for (int i = writingPos; i < curStringLength; i++)
		{
			fout << curString[i];
		}
	}
}

void DoReplace(ifstream &fin, ofstream &fout, const string &searchString, 
											  const string &replaceString)
{
	string pattern = searchString + '`', curLine = "";
	vector<size_t> patternPrefixFunction = CalcPatternPrefixFunction(pattern);

	while (getline(fin, curLine))
	{
		ReplaceAndPrintString(fout, pattern, searchString, replaceString, curLine, patternPrefixFunction);

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
	if (!strcmp(argv[1], argv[2]))
	{
		printf("Same file\n");
		return 1;
	}
	if (strlen(argv[3]) == 0)
	{
		printf("Search string length = 0\n");
		return 1;
	}

	ifstream fin(argv[1]);
	if (!fin)
	{
		printf("Error with opening input file %s\n", argv[1]);
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

	return 0;
}