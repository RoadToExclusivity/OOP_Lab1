#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 3
#define MINOR_SIZE 2

bool ReadMatrix(FILE *fin, float(&m)[MATRIX_SIZE][MATRIX_SIZE])
{
	bool isSuccess = true;
	for (int i = 0; i < 3 && isSuccess; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (fscanf(fin, "%f", &m[i][j]) != 1)
			{
				isSuccess = false;
				break;
			}
		}
	}

	return isSuccess;
}

void RevertMatrix(float(&inverseMatrix)[MATRIX_SIZE][MATRIX_SIZE], 
				  const float(&m)[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			inverseMatrix[i][j] = m[j][i];
	}
}

void Exclude(float (&minor)[MINOR_SIZE][MINOR_SIZE], 
			 const float (&m)[MATRIX_SIZE][MATRIX_SIZE], int x, int y)
{
	int kx = 0, ky = 0;
	for (int i = 0; i < 3; i++)
	{
		if (i == x)
		{
			continue;
		}
		ky = 0;
		for (int j = 0; j < 3; j++)
		{
			if (j == y)
			{
				continue;
			}
			minor[kx][ky++] = m[i][j];
		}
		kx++;
	}
}

float Det2(float(&m)[MINOR_SIZE][MINOR_SIZE])
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

float Det3(float(&m)[MATRIX_SIZE][MATRIX_SIZE])
{
	float firstRowCurMinor[MINOR_SIZE][MINOR_SIZE];
	float determinant = 0;
	int ñoef = 1;
	for (int i = 0; i < 3; i++)
	{
		Exclude(firstRowCurMinor, m, 0, i);
		determinant += m[0][i] * ñoef * Det2(firstRowCurMinor);
		ñoef = -ñoef;
	}

	return determinant;
}

void CalcAdjugateMatrix(float (&adjMatrix)[MATRIX_SIZE][MATRIX_SIZE], 
						const float (&m)[MATRIX_SIZE][MATRIX_SIZE])
{
	float curMinor[MINOR_SIZE][MINOR_SIZE];
	for (int i = 0; i < 3; i++)
	{
		int coef = 1;
		if (i & 1 == 1)
		{
			coef = -1;
		}
		for (int j = 0; j < 3; j++)
		{
			Exclude(curMinor, m, i, j);
			adjMatrix[i][j] = coef * Det2(curMinor);
			coef = -coef;
		}
	}
}

void PrintInverseMatrix(const float(&m)[MATRIX_SIZE][MATRIX_SIZE], float det)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.3f", m[i][j] / det);
			if (j < 2)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Not enough arguments\n");
		return 0;
	}
	if (!strlen(argv[1]))
	{
		printf("Empty file name\n");
		return 1;
	}

	FILE *f;
	if (!(f = fopen(argv[1], "r")))
	{
		printf("Error with opening file %s\n", argv[1]);
		return 1;
	}

	float a[MATRIX_SIZE][MATRIX_SIZE];
	if (!ReadMatrix(f, a))
	{
		printf("Matrix is not [3 x 3]\n");
		return 1;
	}
	fclose(f);

	float det = Det3(a);
	if (det == 0)
	{
		printf("Determinant = 0\n");
		return 0;
	}
	
	float reverseMatrix[MATRIX_SIZE][MATRIX_SIZE];
	RevertMatrix(reverseMatrix, a);

	float adjMatrix[MATRIX_SIZE][MATRIX_SIZE];
	CalcAdjugateMatrix(adjMatrix, reverseMatrix);

	PrintInverseMatrix(adjMatrix, det);

	return 0;
}