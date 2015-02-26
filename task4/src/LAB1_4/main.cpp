#include <cstdio>
#include <math.h>
#include <memory>

#define BI_SIGN 0x4D42
#define BI_RLE8_COMPRESSION 1
#define BI_RLE4_COMPRESSION 2
#define BI_JPEG_COMPRESSION 4
#define BI_PNG_COMPRESSION 5

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef signed int LONG;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
}BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}BITMAPINFOHEADER;
#pragma pack(pop)

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Not enough arguments\n");
		return 0;
	}

	FILE *f;
	if (!(f = fopen(argv[1], "rb")))
	{
		printf("Error with opening input file\n");
		return 1;
	}
	fseek(f, 0, SEEK_SET);

	BITMAPFILEHEADER bfh;
	memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
	size_t res = fread(&bfh, sizeof(BITMAPFILEHEADER), 1, f);
	if (res != 1)
	{
		printf("Corrupted file\n");
		fclose(f);
		return 1;
	}

	if (bfh.bfType != BI_SIGN)
	{
		printf("Not a bitmap file\n");
		fclose(f);
		return 1;
	}

	BITMAPINFOHEADER bih;
	memset(&bih, 0, sizeof(BITMAPINFOHEADER));
	res = fread(&bih, sizeof(BITMAPINFOHEADER), 1, f);
	if (res != 1)
	{
		printf("Corrupted file\n");
		fclose(f);
		return 1;
	}

	LONG picWidth = bih.biWidth;
	LONG picHeight = abs(bih.biHeight);
	printf("Width = %d\nHeight = %d\n", picWidth, picHeight);

	WORD bitCount = bih.biBitCount;
	printf("Bit count = %u\n", bitCount);

	if (bitCount < 16)
	{
		DWORD picClrUsed = bih.biClrUsed;
		if (!picClrUsed)
		{
			picClrUsed = 1 << bitCount;
		}
		printf("Palette colours = %u\n", picClrUsed);
	}

	switch (bih.biCompression)
	{
		case BI_RLE8_COMPRESSION: case BI_RLE4_COMPRESSION:
			printf("Used RLE compression\n");
			break;
		case BI_JPEG_COMPRESSION:
			printf("Used JPEG compression\n");
			break;
		case BI_PNG_COMPRESSION:
			printf("Used PNG compression\n");
			break;
	}

	DWORD picSize = bih.biSizeImage;
	if (!picSize)
	{
		picSize = (picWidth * picHeight) * bitCount / 8;
	}
	printf("Picture size = %u\n", picSize);
	
	fclose(f);
	return 0;
}