#include <stdio.h>
#include <string.h>

typedef float Matrix3x3[3][3];
typedef float Matrix2x2[2][2];

bool ReadMatrix(const char *s, Matrix3x3 &m)
{
	FILE *f;
	if (!(f = fopen(s, "r")))
	{
		return false;
	}

	bool isSuccess = true;
	for (int i = 0; i < 3 && isSuccess; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (fscanf(f, "%f", &m[i][j]) != 1)
			{
				isSuccess = false;
				break;
			}
		}
	}
	fclose(f);
	
	return isSuccess;
}

void TransposeMatrix(const Matrix3x3 &m, Matrix3x3 &transposeMatrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			transposeMatrix[i][j] = m[j][i];
	}
}

void Exclude(const Matrix3x3 &m, Matrix2x2 &minor, int x, int y)
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

float Det2(const Matrix2x2 &m)
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

float Det3(const Matrix3x3 &m)
{
	Matrix2x2 firstRowCurMinor;
	float determinant = 0;
	int coef = 1;
	for (int i = 0; i < 3; i++)
	{
		Exclude(m, firstRowCurMinor, 0, i);
		determinant += m[0][i] * coef * Det2(firstRowCurMinor);
		coef = -coef;
	}

	return determinant;
}

void CalcAdjugateMatrix(const Matrix3x3 &m, Matrix3x3 &adjMatrix)
{
	Matrix2x2 curMinor;
	for (int i = 0; i < 3; i++)
	{
		int coef = 1;
		if ((i & 1) == 1)
		{
			coef = -1;
		}
		for (int j = 0; j < 3; j++)
		{
			Exclude(m, curMinor, i, j);
			adjMatrix[i][j] = coef * Det2(curMinor);
			coef = -coef;
		}
	}
}

bool InverseMatrix(const Matrix3x3 &inputMatrix, Matrix3x3 &inverseMatrix)
{
	float det = Det3(inputMatrix);
	if (det == 0)
	{
		return false;
	}

	Matrix3x3 transposeMatrix;
	TransposeMatrix(inputMatrix, transposeMatrix);

	Matrix3x3 adjMatrix;
	CalcAdjugateMatrix(transposeMatrix, adjMatrix);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			inverseMatrix[i][j] = adjMatrix[i][j] / det;
		}
	}

	return true;
}

void PrintMatrix(const Matrix3x3 &m)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.3f", m[i][j]);
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

	Matrix3x3 inputMatrix;
	if (!ReadMatrix(argv[1], inputMatrix))
	{
		printf("Error with reading matrix or matrix is not 3x3\n");
		return 1;
	}

	Matrix3x3 inverseMatrix;
	if (!InverseMatrix(inputMatrix, inverseMatrix))
	{
		printf("Determinant = 0\n");
		return 0;
	}

	PrintMatrix(inverseMatrix);

	return 0;
}