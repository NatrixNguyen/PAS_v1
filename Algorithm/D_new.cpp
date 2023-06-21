#define _CRT_SECURE_NO_DEPRECATE
//#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#define pi M_PI

//#define fopen_s(fp, fmt, mode) *(fp) = fopen((fmt), (mode))

double Pa[200], Pn[200];
double current_known_a[200], current_known_n[200];
double cur_a[200], cur_n[200];
double H1_a[200][200], H1_n[200][200];
double H2_a[200][200], H2_n[200][200];
double mid1_a[200][200], mid1_n[200][200];
double mid2_a[200][200], mid2_n[200][200];
double mid3_a[200][200], mid3_n[200][200];
double current1_a[200][200], current1_n[200][200];
double coefficient_a[200][200], coefficient_n[200][200];
double current_measured_a, current_measured_n;
double current_predicted_a, current_predicted_n;
double Da[500], Dn[500];
double minDa, maxDa;

double volt_known_a[200], volt_known_n[200];
double H1c_a[200][200], H1c_n[200][200];
double H2c_a[200][200], H2c_n[200][200];
double mid1c_a[200][200], mid1c_n[200][200];
double mid2c_a[200][200], mid2c_n[200][200];
double mid3c_a[200][200], mid3c_n[200][200];
double volt1_a[200][200], volt1_n[200][200];
double coefficientv_a[200][200], coefficientv_n[200][200];
double volt_measured_a, volt_measured_n;
double volt_predicted_a, volt_predicted_n;
double Dca[500], Dcn[500];

double S1[200][200], S2[200][200];
double mid1[200][200];
double mid2[200][200];
double c1[200][200];

double f, w, Ts;

int i, j, q, cnt, m, k, alpha, sample, count, length;

double determinant(double[][25], double);

void cofactor(double[][25], double);

void transpose(double[][25], double[][25], double);

// Multiply two matrix
void MatrixMultiply(double a[][200], double b[][200], int row1, int col1, int col2, double c[][200])
{
	int i, j, q;
	for (i = 0; i < row1; i++)
	{
		for (j = 0; j < col2; j++)
		{
			c[i][j] = 0;
			for (q = 0; q < col1; q++)
			{
				c[i][j] += (a[i][q] * b[q][j]);
			}
		}
	}
}

// Dot product of two vector
double DotProduct(double a[][200], double b[][200], int k)
{
	double c = 0;
	for (int i = 0; i < k; i++)
	{
		c += a[i][0] * b[i][0];
	}
	return c;
}

// Euclidian length of vector
double Euclidian(double a[][200], double b[][200], int k)
{
	int i;
	double c = 0;
	double d = 0;
	double e = 0;
	for (i = 0; i < k; i++)
	{
		c += pow(a[i][0], 2);
		d += pow(b[i][0], 2);
	}

	e = sqrt(c) * sqrt(d);
	return e;
}

/*For calculating Determinant of the Matrix */
double determinant(double a[25][25], double index)
{
	double s = 1, det = 0, b[25][25];
	int i, j, m, n, c;
	if (index == 1)
	{
		return (a[0][0]);
	}
	else
	{
		det = 0;
		for (c = 0; c < index; c++)
		{
			m = 0;
			n = 0;
			for (i = 0; i < index; i++)
			{
				for (j = 0; j < index; j++)
				{
					b[i][j] = 0;
					if (i != 0 && j != c)
					{
						b[m][n] = a[i][j];
						if (n < (index - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			det = det + s * (a[0][c] * determinant(b, index - 1));
			s = -1 * s;
		}
	}
	return (det);
}

/*Finding transpose of matrix*/
void transpose(double num[25][25], double fac[25][25], double r)
{
	int i, j;
	double b[25][25], inverse[25][25], d;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			b[i][j] = fac[j][i];
		}
	}
	d = determinant(num, r);
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			inverse[i][j] = b[i][j] / d;
		}
	}

	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			mid2[i][j] = inverse[i][j];
		}
	}
}

void cofactor(double num[25][25], double f)
{
	double b[25][25], fac[25][25];
	int p, q, m, n, i, j;
	for (q = 0; q < f; q++)
	{
		for (p = 0; p < f; p++)
		{
			m = 0;
			n = 0;
			for (i = 0; i < f; i++)
			{
				for (j = 0; j < f; j++)
				{
					if (i != q && j != p)
					{
						b[m][n] = num[i][j];
						if (n < (f - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
		}
	}
	transpose(num, fac, f);
}

void InvertMatrix()
{
	double a[25][25], index, d;
	int i, j;
	index = 2;
	for (i = 0; i < index; i++)
	{
		for (j = 0; j < index; j++)
		{
			a[i][j] = mid1[i][j];
		}
	}
	d = determinant(a, index);
	if (d == 0)
		printf("\nInverse of Entered Matrix is not possible\n");
	else
		cofactor(a, index);
}

// input for trix H
void inputH(double H1[][200], double H2[][200], double current[200], int m)
{
	double temp;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < m - 4; i++)
		{
			H1[i][j] = current[i + j];
		}
	}

	for (int i = 0; i < m - 4; i++)
	{
		temp = H1[i][0];
		H1[i][0] = H1[i][2];
		H1[i][2] = temp;
	}

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < m - 4; i++)
		{
			H2[j][i] = H1[i][j];
		}
	}
}

typedef struct
{
	double voltage_a;
	double voltage_n;

	double current_a;
	double current_n;
} Signal;

int main()
{

	clock_t start, end; // Khai báo biến thời gian
	double time_use;	// Thời gian sử dụng
	start = clock();	// Lấy thời gian trước khi thực hiện thuật toán

	FILE *file1;
	file1 = fopen("data_test.txt", "r");

	if (file1 == NULL)
	{
		printf("Error opening file. \n");
		return 1;
	}

	volatile int samplefloat = 201;

	volatile Signal S[201];

	int read = 0;
	int records = 0;
	do
	{
		// read = fscanf(file1, "%lf %lf %lf %lf", &S[records].voltage_a, &S[records].voltage_n, &S[records].current_a, &S[records].current_n);
		for (i = 0; i < 200; i++)
		{
			fscanf(file1, "%lf", &S[i].voltage_a);
			fscanf(file1, "%lf", &S[i].voltage_n);
			fscanf(file1, "%lf", &S[i].current_a);
			fscanf(file1, "%lf", &S[i].current_n);
		}

		printf("\n");
		if (read <= samplefloat)
			records++;

		if (read == samplefloat && (!feof(file1)))
		{
			printf("File format incorrect.\n");
			return 1;
		}
		if (ferror(file1))
		{
			printf("Error reading file.\n");
			return 1;
		}

	} while (feof(file1));

	fclose(file1);

	printf("\n%d records read.\n\n", records);

	for (i = 0; i < 200; i++)
	{
		printf("%d %lf %lf %lf %lf ",
			   i,
			   S[i].voltage_a,
			   S[i].voltage_n,

			   S[i].current_a,
			   S[i].current_n);
		printf("\n");
	}

	f = 50;

	w = 2 * pi * 50;

	Ts = 0.000526;

	k = 10;

	alpha = 6;

	sample = k + alpha;

	count = 0;
	cnt = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (i == 0)
			{
				S1[i][j] = cos(w * (j + 1) * Ts);
			}
			else if (i == 1)
			{
				S1[i][j] = sin(w * (j + 1) * Ts);
			}
			S2[j][i] = S1[i][j];
		}
	}

	printf("Matrix S1:\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < k; j++)
		{
			printf("%lf ", S1[i][j]);
		}
		printf("\n");
	}

	printf("Matrix S2:\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			printf("%lf ", S2[i][j]);
		}
		printf("\n");
	}

	MatrixMultiply(S1, S2, 2, k, 2, mid1);

	printf("Matrix mid1:\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			printf("%lf ", mid1[i][j]);
		}
		printf("\n");
	}

	InvertMatrix();

	printf("Matrix mid2:\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			printf("%lf ", mid2[i][j]);
		}
		printf("\n");
	}

	MatrixMultiply(mid2, S2, 2, 2, k, c1);

	printf("Matrix c1:\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < k; j++)
		{
			printf("%lf ", c1[i][j]);
		}
		printf("\n");
	}

	while (count < 200)
	{
		count++;
		if (count < sample)
		{
			cur_a[count] = S[count].current_a;
			cur_n[count] = S[count].current_n;
		}
		else
		{
			cnt++;
			for (i = 0; i < sample - 1; i++)
			{
				cur_a[i] = cur_a[i + 1];
				cur_n[i] = cur_n[i + 1];
			}

			cur_a[sample - 1] = S[count].current_a;
			cur_n[sample - 1] = S[count].current_n;
		}
	}
	////////////////////////////////////////////////////////
	m = 33;

	for (i = 0; i < m; i++)
	{
		current_known_a[i] = cur_a[i];
		current_known_n[i] = cur_n[i];

		volt_known_a[i] = Pa[i];
		volt_known_n[i] = Pn[i];
	}

	inputH(H1_a, H2_a, current_known_a, m);
	inputH(H1_n, H2_n, current_known_n, m);

	inputH(H1c_a, H2c_a, volt_known_a, m);
	inputH(H1c_n, H2c_n, volt_known_n, m);

	MatrixMultiply(H2_a, H1_a, 3, m - 4, 3, mid1_a);
	InvertMatrix();
	MatrixMultiply(mid2_a, H2_a, 3, 3, m - 4, mid3_a);

	MatrixMultiply(H2_n, H1_n, 3, m - 4, 3, mid1_n);
	InvertMatrix();
	MatrixMultiply(mid2_n, H2_n, 3, 3, m - 4, mid3_n);

	MatrixMultiply(H2c_a, H1c_a, 3, m - 4, 3, mid1c_a);
	InvertMatrix();
	MatrixMultiply(mid2c_a, H2c_a, 3, 3, m - 4, mid3c_a);

	MatrixMultiply(H2c_n, H1c_n, 3, m - 4, 3, mid1c_n);
	InvertMatrix();
	MatrixMultiply(mid2c_n, H2c_n, 3, 3, m - 4, mid3c_n);

	for (i = 0; i < m - 4; i++)
	{
		current1_a[i][0] = cur_a[i + 3];
		current1_n[i][0] = cur_n[i + 3];

		volt1_a[i][0] = Pa[i + 3];
		volt1_n[i][0] = Pn[i + 3];
	}

	MatrixMultiply(mid3_a, current1_a, 3, m - 4, 1, coefficient_a);
	MatrixMultiply(mid3_n, current1_n, 3, m - 4, 1, coefficient_n);

	MatrixMultiply(mid3c_a, volt1_a, 3, m - 4, 1, coefficientv_a);
	MatrixMultiply(mid3c_n, volt1_n, 3, m - 4, 1, coefficientv_n);

	for (i = m; i < k; i++)
	{
		current_known_a[i] = current_known_a[i - 1] * coefficient_a[0][0] + current_known_a[i - 2] * coefficient_a[1][0] + current_known_a[i - 3] * coefficient_a[2][0];
		current_known_n[i] = current_known_n[i - 1] * coefficient_n[0][0] + current_known_n[i - 2] * coefficient_n[1][0] + current_known_n[i - 3] * coefficient_n[2][0];

		volt_known_a[i] = volt_known_a[i - 1] * coefficientv_a[0][0] + volt_known_a[i - 2] * coefficientv_a[1][0] + volt_known_a[i - 3] * coefficientv_a[2][0];
		volt_known_n[i] = volt_known_n[i - 1] * coefficientv_n[0][0] + volt_known_n[i - 2] * coefficientv_n[1][0] + volt_known_n[i - 3] * coefficientv_n[2][0];
	}

	current_measured_a = 0;
	current_predicted_a = 0;

	current_measured_n = 0;
	current_predicted_n = 0;

	volt_measured_a = 0;
	volt_predicted_a = 0;

	volt_measured_n = 0;
	volt_predicted_n = 0;

	for (i = m; i < k; i++)
	{
		current_measured_a += cur_a[i];
		current_predicted_a += current_known_a[i];

		current_measured_n += cur_n[i];
		current_predicted_n += current_known_n[i];

		volt_measured_a += Pa[i];
		volt_predicted_a += volt_known_a[i];

		volt_measured_n += Pn[i];
		volt_predicted_n += volt_known_n[i];
	}

	Da[count] = fabs(current_measured_a - current_predicted_a);
	Dn[count] = fabs(current_measured_n - current_predicted_n);

	Dca[count] = fabs(volt_measured_a - volt_predicted_a);
	Dcn[count] = fabs(volt_measured_n - volt_predicted_n);

	end = clock();									   // lấy thời gian sau khi thực hiện
	time_use = (double)(end - start) / CLOCKS_PER_SEC; // Tính thời gian sử dụng

	printf("Time used = %lf\n", time_use);

	FILE *fp = NULL;

	// fopen_s(&fp, "vi.txt", "w+");
	fp = fopen("vi.txt", "w+");

	// Ghi dữ liệu theo định dạng chỉ định vào file
	for (int i = 0; i < 201; i++)
	{
		fprintf(fp, "%lf, %lf, %lf, %lf \n",
				Da[i], Dn[i], Dca[i], Dcn[i]);
	}

	fclose(fp);
	return 0;
}