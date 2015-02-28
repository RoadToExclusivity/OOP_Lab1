#include <cstdio>
#include <vector>

#define MAX 102

using namespace std;

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
		return 1;
	}

	int c, n = 1, m = 1;
	int **a = new int*[MAX], *rowSize = new int[MAX];
	for (int i = 0; i < MAX; i++)
	{
		a[i] = new int[MAX];
		memset(a[i], 0, sizeof(a[i]));
	}
	vector<pair<int, int>> posList;
	while ((c = fgetc(fin)) != EOF)
	{
		if (c == '\n')
		{
			rowSize[n] = m;
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
		rowSize[n] = m;
		n++;
	}

	for (size_t i = 0; i < posList.size(); i++)
	{
		Fill(a, posList[i].first, posList[i].second);
	}
	posList.clear();

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < rowSize[i]; j++)
		{ 
			fputc(a[i][j], fout);
		}
		fputc('\n', fout);
		
		delete[] a[i];
	}
	fclose(fin);
	fclose(fout);

	delete[] rowSize;
	delete[] a;
	return 0;
}