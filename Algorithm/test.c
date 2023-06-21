#define _CRT_SECURE_NO_DEPRECATE
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define pi M_PI

#define VECTOR_SIZE 200
#define SAMPLE_SIZE 42
// SAMPLE_SIZE = k + alpha
#define alpha 4

/*Declaration for input of Voltage*/
double Pa[200], Pn[200];
double Ma[200][200], Mn[200][200];
double Na[200][200], Nn[200][200];
double Y_paa[200][200], Y_pan[200][200];
double Y_pra[200][200], Y_prn[200][200];
double V_paa[200][200], V_pan[200][200];
double V_pra[200][200], V_prn[200][200];
double Phi_a, Phi_n;
double PAS_a[500], PAS_n[500];
double PAS_amax, PAS_nmax;
double PAS_amin, PAS_nmin;
double dot, eucl;
double consmatrx_Va_pa[200][200], consmatrx_Va_pr[200][200];
double consmatrx_Vn_pa[200][200], consmatrx_Vn_pr[200][200];

double consmatrx_Ca_pa[200][200], consmatrx_Ca_pr[200][200];
double consmatrx_Cn_pa[200][200], consmatrx_Cn_pr[200][200];

/*Declaration for input of Current*/
double Mca[200][200], Mcn[200][200];
double Nca[200][200], Ncn[200][200];
double Yc_paa[200][200], Yc_pan[200][200];
double Yc_pra[200][200], Yc_prn[200][200];
double Vc_paa[200][200], Vc_pan[200][200];
double Vc_pra[200][200], Vc_prn[200][200];
double Phic_a, Phic_n;
double PASc_a[500], PASc_n[500];

// declare for D parameter
double cur_a[200], cur_b[200], cur_c[200], cur_n[200];

// declare for other elementary
double S1[200][200], S2[200][200];
double mid1[200][200];
double mid2[200][200];
double c1[200][200];

double determinant(double [][25], double);

void cofactor(double [][25], double);

void transpose(double [][25], double [][25], double);

double f, w, Ts;

int i, j, q, cnt, m, k, sample, count, length; // remove "alpha", definded in the header


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

// InvertMatrix
void InvertMatrix()
    {
      double a[25][25], index, d;
      int i, j;
      index = 2;
      for (i = 0;i < index; i++)
        {
         for (j = 0;j < index; j++)
           {
            a[i][j]= mid1[i][j];
            }
        }
      d = determinant(a, index);
      if (d == 0)
       printf("\nInverse of Entered Matrix is not possible\n");
      else
       cofactor(a, index);
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
            for (i = 0;i < index; i++)
              {
                for (j = 0 ;j < index; j++)
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
    void cofactor(double num[25][25], double f)
    {
     double b[25][25], fac[25][25];
     int p, q, m, n, i, j;
     for (q = 0;q < f; q++)
     {
       for (p = 0;p < f; p++)
        {
         m = 0;
         n = 0;
         for (i = 0;i < f; i++)
         {
           for (j = 0;j < f; j++)
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
    /*Finding transpose of matrix*/ 
    void transpose(double num[25][25], double fac[25][25], double r)
    {
      int i, j;
      double b[25][25], inverse[25][25], d;
      for (i = 0;i < r; i++)
        {
         for (j = 0;j < r; j++)
           {
             b[i][j] = fac[j][i];
            }
        }
      d = determinant(num, r);
      for (i = 0;i < r; i++)
        {
         for (j = 0;j < r; j++)
           {
            inverse[i][j] = b[i][j] / d;
            }
        }
     
       for (i = 0;i < r; i++)
        {
         for (j = 0;j < r; j++)
           {
            mid2[i][j] = inverse[i][j];
            }
         }
    }


void printVector(double vector[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%lf ", vector[i]);
    }
    printf("\n");
}

typedef struct
{
	double voltage_a;
	double voltage_n;

	double current_a;
	double current_n;
} Signal;

int main() {
	int i;
    double Voltage_a[VECTOR_SIZE]; 
    double Voltage_n[VECTOR_SIZE];
    double Current_a[VECTOR_SIZE];
    double Current_n[VECTOR_SIZE];

    double Sample_Va[SAMPLE_SIZE]; // Vector Sample with the first 12 elements of Voltage_a
    double Sample_Vn[SAMPLE_SIZE];
    double Sample_Ca[SAMPLE_SIZE];
    double Sample_Cn[SAMPLE_SIZE];

    double Va_pa[SAMPLE_SIZE - alpha]; // Vector Pa with size SAMPLE_SIZE - 2
    double Va_pr[SAMPLE_SIZE - alpha]; // Vector Pb with size SAMPLE_SIZE - 2
    double Vn_pa[SAMPLE_SIZE - alpha];
    double Vn_pr[SAMPLE_SIZE - alpha];

    double Ca_pa[SAMPLE_SIZE - alpha];
    double Ca_pr[SAMPLE_SIZE - alpha];
    double Cn_pa[SAMPLE_SIZE - alpha];
    double Cn_pr[SAMPLE_SIZE - alpha];
    volatile Signal S[201];
    volatile int sampledouble = 201;
    int read = 0;
	int records = 0;

    // Input frequency of inverter for f
	f = 50;

	// Compute w from f
	w = 2 * pi * f;

	// Choose Ts for sampling period
	Ts = 0.000526;
    //Ts = 0.0001;
	//Ts = 0.025;

	// Choose the amount of samples in one sampling window
	k = 38;

	// Choose the length between two sampling window (0.1*sample<=alpha<=0.25*sample)
	//alpha = 10;

	// The amount of samples (include samples in one window plus the length between two window)
	//sample = k + alpha;

	count = 0;
	cnt = 0;


    clock_t start, end; // Khai báo biến thời gian
	double time_use;		// Thời gian sử dụng
	start = clock();	// Lấy thời gian trước khi thực hiện thuật toán


	FILE *file1;
	file1 = fopen("data_test_3.txt", "r");

    if (file1 == NULL)
	{
		printf("Error opening file. \n");
		return 1;
	}

    //Create constant matrix S1 S2
    
    for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (i == 0)
			{
				
                S1[i][j] = sin(w * (j + 1) * Ts);
			}
			else if (i == 1)
			{
				S1[i][j] = cos(w * (j + 1) * Ts);
			}
			S2[j][i] = S1[i][j]; // S1 = S , S2 = S^T
		}
    }

    printf("Matrix S1:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < k; j++) {
            printf("%lf ", S1[i][j]);
        }
        printf("\n");
    }

	printf("Matrix S2:\n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%lf ", S2[i][j]);
        }
        printf("\n");
    }

    // Compute C1=(S2*S1)^-1*S2

	MatrixMultiply(S1, S2, 2, k, 2, mid1);

    	printf("Matrix mid1:\n");
        for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%lf ", mid1[i][j]);
        }
        printf("\n");
    	}

	InvertMatrix();
	//InvertMatrix(mid1, k, mid2);

	printf("Matrix mid2:\n");
        for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%lf ", mid2[i][j]);
        }
        printf("\n");
    	}

	MatrixMultiply(mid2, S1, 2, 2, k, c1);

	printf("Matrix c1:\n");
        for (int i = 0; i < 2; i++) {
        for (int j = 0; j < k; j++) {
            printf("%lf ", c1[i][j]);
        }
        printf("\n");
    	}

    //Multiply matrix --> based on Pas_main
    //Create constant matrix for each input value
    MatrixMultiply(S2, c1, k, 2, k, consmatrx_Va_pa);
    MatrixMultiply(S2, c1, k, 2, k, consmatrx_Va_pr);

    MatrixMultiply(S2, c1, k, 2, k, consmatrx_Vn_pa);
	MatrixMultiply(S2, c1, k, 2, k, consmatrx_Vn_pr);

	MatrixMultiply(S2, c1, k, 2, k, consmatrx_Ca_pa);
	MatrixMultiply(S2, c1, k, 2, k, consmatrx_Ca_pr);

	MatrixMultiply(S2, c1, k, 2, k, consmatrx_Cn_pa);
	MatrixMultiply(S2, c1, k, 2, k, consmatrx_Cn_pr);

    do
	{
            for (i = 0; i < 200; i++) {
            fscanf(file1, "%lf", &S[i].voltage_a);
            fscanf(file1, "%lf", &S[i].voltage_n);
            fscanf(file1, "%lf", &S[i].current_a);
            fscanf(file1, "%lf", &S[i].current_n);
        }

		printf("\n");
		if (read <= sampledouble)
			records++;

		if (read == sampledouble && (!feof(file1)))
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

    int position = 0; // Starting position for Sample

    // Fill the Voltage_a vector with some sample values
    for (int i = 0; i < VECTOR_SIZE; i++) {
        Voltage_a[i] = S[i].voltage_a;
        Voltage_n[i] = S[i].voltage_n;
        Current_a[i] = S[i].current_a;
        Current_n[i] = S[i].current_n;
    }

    FILE *fp = NULL;

	fp = fopen("PAS_data_output_3.txt", "w+");
   
    while (position <= VECTOR_SIZE - SAMPLE_SIZE) {
        // Copy values from Voltage_a to Sample
        for (int i = 0; i < SAMPLE_SIZE; i++) {
            Sample_Va[i] = Voltage_a[position + i];
            Sample_Vn[i] = Voltage_n[position + i];
            Sample_Ca[i] = Current_a[position + i];
            Sample_Cn[i] = Current_n[position + i];
        }

        // Populate Pa and Pb vectors
        //M = past, N = present
        for (int i = 0; i < SAMPLE_SIZE - alpha; i++) {
            Va_pa[i] = Sample_Va[i];
            Ma[i][0] = Va_pa[i];
            Va_pr[i] = Sample_Va[i + alpha];
            Na[i][0] = Va_pr[i];

            Vn_pa[i] = Sample_Vn[i];
            Mn[i][0] = Vn_pa[i];
            Vn_pr[i] = Sample_Vn[i + alpha];
            Nn[i][0] = Vn_pr[i];

            Ca_pa[i] = Sample_Ca[i];
            Mca[i][0] = Ca_pa[i];
            Ca_pr[i] = Sample_Ca[i + alpha];
            Nca[i][0] = Ca_pr[i];

            Cn_pa[i] = Sample_Cn[i];
            Mcn[i][0] = Cn_pa[i];
            Cn_pr[i] = Sample_Cn[i + alpha];
            Ncn[i][0] = Cn_pr[i];   

        // Matrix caculation
        MatrixMultiply(consmatrx_Va_pa, Ma, k, k, 1, V_paa);
        MatrixMultiply(consmatrx_Va_pr, Na, k, k, 1, V_pra);

		MatrixMultiply(consmatrx_Vn_pa, Mn, k, k, 1, V_pan);
        MatrixMultiply(consmatrx_Vn_pr, Nn, k, k, 1, V_prn);

        MatrixMultiply(consmatrx_Ca_pa, Mca, k, k, 1, Vc_paa);
        MatrixMultiply(consmatrx_Ca_pr, Nca, k, k, 1, Vc_pra);

        MatrixMultiply(consmatrx_Cn_pa, Mcn, k, k, 1, Vc_pan);
		MatrixMultiply(consmatrx_Cn_pr, Ncn, k, k, 1, Vc_prn);

        
        dot = DotProduct(V_pra, V_paa, k);

		eucl = Euclidian(V_pra, V_paa, k);

		Phi_a = dot / eucl;
		Phi_a = acos(Phi_a);
        printf("Phi_a = %lf", Phi_a);
        printf("\n");

		dot = DotProduct(V_prn, V_pan, k);

		eucl = Euclidian(V_prn, V_pan, k);

		Phi_n = dot / eucl;
		Phi_n = acos(Phi_n);

		dot = DotProduct(Vc_pra, Vc_paa, k);

		eucl = Euclidian(Vc_pra, Vc_paa, k);

		Phic_a = dot / eucl;
		Phic_a = acos(Phic_a);

		dot = DotProduct(Vc_prn, Vc_pan, k);

		eucl = Euclidian(Vc_prn, Vc_pan, k);

		Phic_n = dot / eucl;
		Phic_n = acos(Phic_n);

			// Find PAS
			PAS_a[i] = fabs((Phi_a * 180 / pi) - ((alpha * 360) / k));
            printf("PAS_a : %lf \n",PAS_a[i]);
            printf("\n");
			PAS_n[i] = fabs((Phi_n * 180 / pi) - ((alpha * 360) / k));
            printf("PAS_n : %lf \n",PAS_n[i]);
            printf("\n");
			PASc_a[i] = fabs((Phic_a * 180 / pi) - ((alpha * 360) / k));
            printf("PASc_a : %lf \n",PASc_a[i]);
            printf("\n");
			PASc_n[i] = fabs((Phic_n * 180 / pi) - ((alpha * 360) / k));
            printf("PASc_n : %lf \n",PASc_n[i]);
            printf("\n");

            fprintf(fp, "%lf %lf %lf %lf \n",
				PAS_a[i], PAS_n[i],
				PASc_a[i], PASc_n[i]);
        }
        

        printf("Va_pa: ");
        printVector(Va_pa, SAMPLE_SIZE - alpha);
        printf("Va_pr: ");
        printVector(Va_pr, SAMPLE_SIZE - alpha);
        printf("\n");
        printf("\n");
        
        printf("Vn_pa: ");
        printVector(Vn_pa, SAMPLE_SIZE - alpha);
        printf("Vn_pr: ");
        printVector(Vn_pr, SAMPLE_SIZE - alpha);
        printf("\n");
        printf("\n");

        printf("Ca_pa: ");
        printVector(Ca_pa, SAMPLE_SIZE - alpha);
        printf("Ca_pr: ");
        printVector(Ca_pr, SAMPLE_SIZE - alpha);
        printf("\n");
        printf("\n");

        printf("Cn_pa: ");
        printVector(Cn_pa, SAMPLE_SIZE - alpha);
        printf("Cn_pr: ");
        printVector(Cn_pr, SAMPLE_SIZE - alpha);
        printf("\n");
        printf("\n");

        position += SAMPLE_SIZE; // Move to the next position in Voltage_a
		// Ghi dữ liệu theo định dạng chỉ định vào file
        printf("Mẫu sample đầu tiên \n");
        printf("position : %d \n",position);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
    }
    fclose(fp);
    return 0;
}
