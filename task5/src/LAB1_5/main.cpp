#include <cstdio>
#include <cstring>
#include <cstdlib>

#define BYTE_LENGTH 8

typedef unsigned char BYTE;

bool StringToInt(const char *s, int &num)
{
	char *pEnd = NULL;
	num = strtol(s, &pEnd, 10);
	return !((*s == '\0') || (*pEnd != '\0'));
}

BYTE MixByte(BYTE k, const BYTE(&shiftSeq)[BYTE_LENGTH])
{
	BYTE c = 0;
	for (int i = 0; i < 8; i++)
	{
		c = (c << 1) | ((BYTE)(k << shiftSeq[i]) >> 7);
	}
	return c;
}

void Crypt(FILE *in, FILE *out, BYTE key, const BYTE(&seq)[BYTE_LENGTH])
{
	BYTE curByte;
	while (fread(&curByte, sizeof(BYTE), 1, in))
	{
		curByte = MixByte(curByte ^ key, seq);
		fwrite(&curByte, sizeof(BYTE), 1, out);
	}
}

void Decrypt(FILE *in, FILE *out, BYTE key, const BYTE(&seq)[BYTE_LENGTH])
{
	BYTE curByte;
	while (fread(&curByte, sizeof(BYTE), 1, in))
	{
		curByte = MixByte(curByte, seq) ^ key;
		fwrite(&curByte, sizeof(BYTE), 1, out);
	}
}

bool IsCorrectAction(const char *action, bool &actionType)
{
	if (strcmp(action, "crypt") == 0)
	{
		actionType = 1;
		return true;
	}
	
	if (strcmp(action, "decrypt") == 0)
	{
		actionType = 0;
		return true;
	}

	return false;
}

bool IsCorrectNumber(const char *strNum, int &key)
{
	int num;
	if (!StringToInt(strNum, num))
	{
		return false;
	}
	if (num < 0 || num > 255)
	{
		return false;
	}
	
	key = num;
	return true;
}

void DoAction(FILE *fin, FILE *fout, bool isCrypt, BYTE key)
{
	BYTE shiftSeqStraight[BYTE_LENGTH] = { 3, 4, 0, 5, 6, 7, 1, 2 },
		 shiftSeqRevert[BYTE_LENGTH] = { 2, 6, 7, 0, 1, 3, 4, 5 };

	if (isCrypt)
	{
		Crypt(fin, fout, key, shiftSeqStraight);
	}
	else
	{
		Decrypt(fin, fout, key, shiftSeqRevert);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		printf("Not enough arguments\n");
		return 0;
	}
	
	bool isActionCrypt;
	if (!IsCorrectAction(argv[1], isActionCrypt))
	{
		printf("Unknown action\n");
		return 1;
	}

	int key;
	if (!IsCorrectNumber(argv[4], key))
	{
		printf("Incorrect key\n");
		return 1;
	}

	FILE *fin, *fout;
	if (!(fin = fopen(argv[2], "rb")))
	{
		printf("Error with opening input file\n");
		return 1;
	}
	if (!(fout = fopen(argv[3], "wb")))
	{
		printf("Error with opening output file\n");
		fclose(fin);
		return 1;
	}

	DoAction(fin, fout, isActionCrypt, key);

	fclose(fin);
	fclose(fout);

	return 0;
}