#define _CRT_SECURE_NO_DEPRECATE
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define pi M_PI
#define VECTOR_SIZE 200
#define SAMPLE_SIZE 48
#define ALPHA 10

double S1[2][SAMPLE_SIZE];
double S2[SAMPLE_SIZE][2];
double C1[2][SAMPLE_SIZE];
double mid1[2][2];
double mid2[2][2];

void MatrixMultiply(double a[][SAMPLE_SIZE], double b[][SAMPLE_SIZE], int row1, int col1, int col2, double c[][SAMPLE_SIZE])
{
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            c[i][j] = 0;
            for (int q = 0; q < col1; q++)
            {
                c[i][j] += (a[i][q] * b[q][j]);
            }
        }
    }
}

void InvertMatrix()
{
    double d = mid1[0][0] * mid1[1][1] - mid1[0][1] * mid1[1][0];
    double invDet = 1.0 / d;
    mid2[0][0] = mid1[1][1] * invDet;
    mid2[0][1] = -mid1[0][1] * invDet;
    mid2[1][0] = -mid1[1][0] * invDet;
    mid2[1][1] = mid1[0][0] * invDet;
}

void PrintMatrix(const char *name, double matrix[][SAMPLE_SIZE], int rows, int cols)
{
    printf("%s:\n", name);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    double f = 50.0;
    double w = 2 * pi * f;
    double Ts = 0.000526;
    int k = 37;
    int sample = k + ALPHA;

    FILE *file1 = fopen("data_test_2.txt", "r");
    if (file1 == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Create matrix S1 and S2
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < k; j++)
        {
            double angle = w * (j + 1) * Ts;
            S1[i][j] = (i == 0) ? sin(angle) : cos(angle);
            S2[j][i] = S1[i][j];
        }
    }

    PrintMatrix("Matrix S1", S1, 2, k);
    PrintMatrix("Matrix S2", S2, k, 2);

    // Compute C1 = (S2 * S1)^-1 * S2
    MatrixMultiply(S2, S1, k, 2, k, mid1);
    InvertMatrix();
    MatrixMultiply(mid2, S1, 2, 2, k, C1);

    PrintMatrix("Matrix C1", C1, 2, k);

    fclose(file1);
    return 0;
}
