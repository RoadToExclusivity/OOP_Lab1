#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef unsigned char BYTE;

BYTE MixByte(BYTE k, BYTE shiftSeq[])
{
	BYTE c = 0;
	for (int i = 0; i < 8; i++)
	{
		c = (c << 1) | (static_cast<BYTE>(k << shiftSeq[i]) >> 7);
	}
	return c;
}

void Crypt(FILE *in, FILE *out, int key, BYTE seq[])
{
	BYTE curByte;
	while (fread(&curByte, sizeof(BYTE), 1, in))
	{
		curByte = MixByte(curByte ^ key, seq);
		fwrite(&curByte, sizeof(BYTE), 1, out);
	}
}

void Decrypt(FILE *in, FILE *out, int key, BYTE seq[])
{
	BYTE curByte;
	while (fread(&curByte, sizeof(BYTE), 1, in))
	{
		curByte = MixByte(curByte, seq) ^ key;
		fwrite(&curByte, sizeof(BYTE), 1, out);
	}
}

bool StringToInt(const char *s, int &num)
{
	char *pEnd = NULL;
	num = strtol(s, &pEnd, 10);
	return !((*s == '\0') || (*pEnd != '\0'));
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		printf("Not enough arguments\n");
		return 0;
	}
	
	int type;
	if (!strcmp(argv[1], "crypt"))
	{
		type = 1;
	}
	else
	{
		if (!strcmp(argv[1], "decrypt"))
		{
			type = 0;
		}
		else
		{
			printf("Unknown action\n");
			return 1;
		}
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
		return 1;
	}
	
	int key;
	if (!StringToInt(argv[4], key))
	{
		printf("Key is not a number\n");
		return 1;
	}
	if (key < 0 || key > 255)
	{
		printf("Key is out of range 0-255\n");
		return 1;
	}

	BYTE shiftSeqStraight[8] = { 3, 4, 0, 5, 6, 7, 1, 2 }, 
		shiftSeqRevert[8] = { 2, 6, 7, 0, 1, 3, 4, 5 };
	switch (type)
	{
		case 0:
			Decrypt(fin, fout, key, shiftSeqRevert);
			break;
		case 1:
			
			Crypt(fin, fout, key, shiftSeqStraight);
			break;
		default:
			printf("TYPE == 0 ?\n");
			break;
	}

	fclose(fin);
	fclose(fout);

	return 0;
}