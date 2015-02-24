#include <cstdio>
#include <string.h>

int main(int argc, char *argv[]){
	if (argc < 5)
	{
		printf("Not enough parameters\n");
		return 0;
	}

	FILE *fin, *fout;
	if (!(fin = fopen(argv[1], "r")))
	{
		printf("Error with opening input file %s\n", argv[1]);
		return 1;
	}
	
	if (!strcmp(argv[1], argv[2]))
	{
		printf("Same file\n");
		return 1;
	}

	if (!(fout = fopen(argv[2], "w")))
	{
		printf("Error with opening output file %s\n", argv[2]);
		return 1;
	}
	

	char *searchString = argv[3], *replaceString = argv[4];
	int searchSLen = strlen(searchString), replaceSLen = strlen(replaceString), curPos = 0;
	char *tempString = new char[replaceSLen + 1];
	bool mbReplaceString = false;
	int c;
	while ((c = fgetc(fin)) != EOF)
	{
		if (replaceSLen && c == searchString[curPos])
		{
			if (!mbReplaceString)
				mbReplaceString = true;
			tempString[curPos] = c;
			tempString[curPos + 1] = 0;
			if (curPos == searchSLen - 1)
			{
				fputs(replaceString, fout);
				curPos = 0;
				mbReplaceString = false;
			}
			else
			{
				curPos++;
			}
		}
		else
		{
			if (mbReplaceString)
			{
				fputs(tempString, fout);
				curPos = 0;
				mbReplaceString = false;
			}
			fputc(c, fout);
		}
	}
	if (mbReplaceString)
	{
		fputs(tempString, fout);
	}

	fclose(fin);
	fclose(fout);
	delete[] tempString;
	
	return 0;
}