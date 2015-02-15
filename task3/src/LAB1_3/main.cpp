#include <stdio.h>
#include <string.h>

float Det2(float **m)
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

float **RevertMatrix(float **m)
{
	float **newMatrix = new float*[3];
	for (int i = 0; i < 3; i++)
	{
		newMatrix[i] = new float[3];
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			newMatrix[i][j] = m[j][i];
	}
	return newMatrix;
}

float **Exclude(float **m, int x, int y)
{
	float **newMatrix = new float*[2];
	for (int i = 0; i < 2; i++)
	{
		newMatrix[i] = new float[2];
	}
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
			newMatrix[kx][ky++] = m[i][j];
		}
		kx++;
	}
	return newMatrix;
}

void DeleteMatrix(float **m, int k)
{
	for (int i = 0; i < k; i++)
	{
			delete[] m[i];
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
	float **a = new float*[3];
	for (int i = 0; i < 3; i++)
	{
		a[i] = new float[3];
		for (int j = 0; j < 3; j++)
		{
			if (fscanf(f, "%f", &a[i][j]) != 1)
			{
				printf("Matrix doesn't have %d %d element\n", i + 1, j + 1);
				
				delete[] a;
				return 1;
			}
		}
	}
	fclose(f);

	float ***startMinors = new float**[3];
	for (int i = 0; i < 3; i++)
	{
		startMinors[i] = Exclude(a, 0, i);
	}
	float det3 = a[0][0] * Det2(startMinors[0]) - a[0][1] * Det2(startMinors[1]) + a[0][2] * Det2(startMinors[2]);

	for (int i = 0; i < 3; i++)
	{
		DeleteMatrix(startMinors[i], 2);
	}
	delete[] startMinors;

	if (!det3)
	{
		printf("Determinant = 0\n");
		return 1;
	}
	
	float **reverseMatrix = RevertMatrix(a);

	float ****minors = new float***[3];
	for (int i = 0; i < 3; i++)
	{
		minors[i] = new float**[3];
		for (int j = 0; j < 3; j++)
		{
			minors[i][j] = Exclude(reverseMatrix, i, j);
		}
	}

	float **conjMatrix = new float*[3];
	for (int i = 0; i < 3; i++)
	{
		conjMatrix[i] = new float[3];
		int coef = 1;
		if (i & 1)
		{
			coef = -1;
		}
		for (int j = 0; j < 3; j++)
		{
			conjMatrix[i][j] = coef * Det2(minors[i][j]);
			coef *= -1;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.3f", conjMatrix[i][j] / det3);
			if (j < 2)
			{
				printf(" ");
			}
		}
		printf("\n");
	}

	DeleteMatrix(a, 3);
	DeleteMatrix(reverseMatrix, 3);
	DeleteMatrix(conjMatrix, 3);
	delete[] a;
	delete[] conjMatrix;
	delete[] reverseMatrix;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DeleteMatrix(minors[i][j], 2);
			delete[] minors[i][j];
		}
		delete[] minors[i];
	}
	delete[] minors;

	return 0;
}