#include <cstdio>
#include <vector>

const int MAX_SIZE = 102;

using namespace std;

typedef int Bitmap[MAX_SIZE][MAX_SIZE];

struct SymbolPosition
{
	int x, y;
};

struct BitmapOffset
{
	int dx, dy;
};

void Fill(Bitmap &a, int x, int y)
{
	BitmapOffset offset[4] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
	for (int i = 0; i < 4; i++)
	{
		if (a[x + offset[i].dx][y + offset[i].dy] == ' ')
		{
			a[x + offset[i].dx][y + offset[i].dy] = '.';
			Fill(a, x + offset[i].dx, y + offset[i].dy);
		}
	}
}

void FillWithZeros(Bitmap &a)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			a[i][j] = 0;
		}
	}
}

vector<SymbolPosition> ReadData(FILE *fin, int &rows, Bitmap &a, int(&rowSizes)[MAX_SIZE])
{
	int c, n = 1, m = 1;
	vector<SymbolPosition> posList;
	while ((c = fgetc(fin)) != EOF)
	{
		if (c == '\n')
		{
			rowSizes[n] = m;
			n++;
			m = 1;
			continue;
		}
		if (c == 'O')
		{
			posList.push_back({ n, m });
		}
		a[n][m] = c;
		m++;
	}
	if (m > 1)
	{
		rowSizes[n] = m;
		n++;
	}

	rows = n;
	return posList;
}

void PrintBitmap(FILE *fout, int rows, const Bitmap &a, const int(&rowSizes)[MAX_SIZE])
{
	for (int i = 1; i < rows; i++)
	{
		for (int j = 1; j < rowSizes[i]; j++)
		{
			fputc(a[i][j], fout);
		}
		fputc('\n', fout);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Not enough arguments\n");
		return 0;
	}
	
	FILE *fin, *fout;
	if (!(fin = fopen(argv[1], "r")))
	{
		printf("Error with opening input file\n");
		return 1;
	}
	if (!(fout = fopen(argv[2], "w")))
	{
		printf("Error with opening output file\n");
		fclose(fin);
		return 1;
	}

	Bitmap a;
	int rowsSizes[MAX_SIZE];
	FillWithZeros(a);

	int rows;
	auto posList = ReadData(fin, rows, a, rowsSizes);
	fclose(fin);

	for (size_t i = 0; i < posList.size(); i++)
	{
		Fill(a, posList[i].x, posList[i].y);
	}

	PrintBitmap(fout, rows, a, rowsSizes);
	fclose(fout);

	return 0;
}