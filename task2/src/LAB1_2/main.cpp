#include <stdio.h>
#include <cstdlib>

bool StringToInt(const char *s, int &num)
{
	char* pEnd = NULL;
	num = strtol(s, &pEnd, 10);
	return !((*s == '\0') || (*pEnd != '\0'));
}

bool IsUnisignedChar(const char *strNum, unsigned char &returnNumber)
{
	int tempNumber;

	if (!StringToInt(strNum, tempNumber))
	{
		printf("First argument not a number\n");
		return false;
	}

	if ((tempNumber < 0) || (tempNumber > 255))
	{
		printf("Number is not in [0, 255]\n");
		return false;
	}

	returnNumber = (unsigned char)tempNumber;
	return true;
}

unsigned char FlipByte(unsigned char n)
{
	unsigned char k = 0;
	for (int i = 0; i < 8; i++, n >>= 1)
	{
		k = (k << 1) | (n & 1);
	}
	return k;
}

int main(int argc, char* argv[]){
	if (argc < 2)
	{
		printf("Not enough parameters\n");
		return 0;
	}

	unsigned char curNumber;
	if (!IsUnisignedChar(argv[1], curNumber))
	{
		return 1;
	}

	unsigned char flippedNumber = FlipByte(curNumber);
	printf("%u\n", flippedNumber);
	
	return 0;
}