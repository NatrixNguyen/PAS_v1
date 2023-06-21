int column = 0;
    int cycleLength = clength;
    double* chiV = (double*)malloc(number_col * sizeof(double));
    double* chiDelta = (double*)malloc(number_col * sizeof(double));
    while (column < number_col) {
        double total = 0.0;
        int row = 0;
        double variance2;
        while (row < cycleLength) {
            total += data[row][column];
            row++;
        }
        double qchisq;
        if (cycleLength == 38) {
            qchisq = 24.07494;
        }
        else if (cycleLength == 64) {
            qchisq = 45.74138;
        }
        else if (cycleLength == 100) {
            qchisq = 135.8067;
        }
        // Calculate mean
        double mean = total / cycleLength;
        while (row < cycleLength) {
            variance2 += pow((data[row][column] - mean), 2);
        }
        printf("Mean of column %d: %lf\n", column, mean);
        double deviation = sqrt(variance2 / qchisq) * 2.3263;
        double a = fabs(mean + deviation);
        double b = fabs(mean - deviation);
        chiV[column] = max_double(a, b);
        column++;
    }