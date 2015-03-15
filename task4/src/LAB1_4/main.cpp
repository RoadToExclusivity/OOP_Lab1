#include <stdio.h>
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

bool ReadHeaders(FILE *fin, BITMAPFILEHEADER &bfh, BITMAPINFOHEADER &bih)
{
	memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&bih, 0, sizeof(BITMAPINFOHEADER));

	size_t fileHeadersRead = fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fin);
	size_t infoHeadersRead = fread(&bih, sizeof(BITMAPINFOHEADER), 1, fin);

	return (fileHeadersRead + infoHeadersRead == 2);
}

void GetBitmapData(const BITMAPINFOHEADER &bih, LONG &bmpWidth, LONG &bmpHeight, 
				   WORD &bitCount, DWORD &bmpClrUsed, DWORD &bmpSize)
{
	bmpWidth = bih.biWidth;
	bmpHeight = abs(bih.biHeight);

	bitCount = bih.biBitCount;
	if (bitCount < 16)
	{
		bmpClrUsed = bih.biClrUsed;
		if (bmpClrUsed == 0)
		{
			bmpClrUsed = 1 << bitCount;
		}
	}

	bmpSize = bih.biSizeImage;
	if (bmpSize == 0)
	{
		bmpSize = (bmpWidth * bmpHeight) * bitCount / 8;
	}
}

void PrintBitmapData(LONG bmpWidth, LONG bmpHeight, WORD bitCount, 
					 DWORD bmpClrUsed, DWORD bmpCompression, DWORD bmpSize)
{
	printf("Width = %d\nHeight = %d\n", bmpWidth, bmpHeight);
	
	printf("Bit count = %u\n", bitCount);
	if (bitCount < 16)
	{
		printf("Palette colours = %u\n", bmpClrUsed);
	}

	switch (bmpCompression)
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

	printf("Picture size = %u\n", bmpSize);
}

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
	BITMAPINFOHEADER bih;
	if (!ReadHeaders(f, bfh, bih) || bfh.bfType != BI_SIGN)
	{
		printf("Not a bitmap file\n");
		fclose(f);
		return 1;
	}
	fclose(f);
	
	LONG bmpWidth, bmpHeight;
	WORD bitCount;
	DWORD bmpClrUsed, bmpSize;
	
	GetBitmapData(bih, bmpWidth, bmpHeight, bitCount, bmpClrUsed, bmpSize);
	PrintBitmapData(bmpWidth, bmpHeight, bitCount, bmpClrUsed, bih.biCompression, bmpSize);
	
	return 0;
}