#include <stdlib.h>
#include <math.h>
#include "mean_module.h"
#include <stdio.h>

double* calculateMean(double* array, int arraySize, int cycleLength) {

    //int arraySize = sizeof(array);
    /*int arraySize = sizeof(array) / sizeof(array[0]);*/
    int numCycles = arraySize / cycleLength;
    //printf("%d \n", numCycles);
    int i, j;
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

    double* mean = (double*)malloc(numCycles * sizeof(double));

    if (mean == NULL) {
        // Failed to allocate memory
        return NULL;
    }

    for (i = 0; i < numCycles; i++) {
        double total = 0;

        for (j = i * cycleLength; j < i * cycleLength + cycleLength; j++) {
            total += array[j];
        }
        mean[i] = total / cycleLength;
    }

    return mean;
}
