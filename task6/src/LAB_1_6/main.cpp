#include <cstdio>
#include <vector>

#define MAX 102

using namespace std;

typedef pair<int, int> pii;

void Fill(int **a, int x, int y)
{
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	for (int i = 0; i < 4; i++)
	{
		if (a[x + dx[i]][y + dy[i]] == ' ')
		{
			a[x + dx[i]][y + dy[i]] = '.';
			Fill(a, x + dx[i], y + dy[i]);
		}
	}
}

void ZeroMemory(int **&a, int *&rowSizes)
{
	a = new int*[MAX];
	rowSizes = new int[MAX];
	for (int i = 0; i < MAX; i++)
	{
		a[i] = new int[MAX];
		memset(a[i], 0, sizeof(a[i]));
	}
}

vector<pii> ReadData(FILE *fin, int &rows, int **a, int *rowSizes)
{
	int c, n = 1, m = 1;
	vector<pii> posList;
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
			posList.push_back(make_pair(n, m));
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

void PrintData(FILE *fout, int rows, 
			   const int* const * const a, 
			   const int* const rowSizes)
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

void Free(int **a, int *rowSizes)
{
	for (int i = 0; i < MAX; i++)
	{
		delete[] a[i];
		a[i] = nullptr;
	}

	delete[] a;
	delete[] rowSizes;

	a = nullptr;
	rowSizes = nullptr;
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

	int **a = nullptr, *rowsSizes = nullptr;
	ZeroMemory(a, rowsSizes);

	int rows;
	auto posList = ReadData(fin, rows, a, rowsSizes);
	fclose(fin);

	for (size_t i = 0; i < posList.size(); i++)
	{
		Fill(a, posList[i].first, posList[i].second);
	}

	PrintData(fout, rows, a, rowsSizes);
	fclose(fout);

	Free(a, rowsSizes);

	return 0;
}