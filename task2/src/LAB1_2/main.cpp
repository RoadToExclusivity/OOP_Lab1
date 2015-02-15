#include <stdio.h>
#include <cstdlib>

bool StringToInt(const char* s, int* num)
{
	char* pEnd = NULL;
	*num = strtol(s, &pEnd, 10);
	return !((*s == '\0') || (*pEnd != '\0'));
}

int main(int argc, char* argv[]){
	if (argc < 2)
	{
		printf("Not enough parameters\n");
		return 0;
	}

	unsigned char n, k = 0;
	int temp;

	if (!StringToInt(argv[1], &temp))
	{
		printf("First argument not a number\n");
		return 1;
	}

	if ((temp < 0) || (temp > 255))
	{
		printf("First argument too large\n");
		return 1;
	}

	n = temp;
	for (int i = 0; i < 8; i++, n >>= 1)
	{
		k = (k << 1) | (n & 1);
	}
	printf("%u\n", k);
	//scanf("%u", &n);
	
	return 0;
}