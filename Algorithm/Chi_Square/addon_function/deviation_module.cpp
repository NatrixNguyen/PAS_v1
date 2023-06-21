#include <stdlib.h>
#include <math.h>
#include "deviation_module.h"
#include <stdio.h>

double* calculateDeviations(double* array, int arraySize,int cycleLength) {
    
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

    double* deviations = (double*)malloc(numCycles * sizeof(double));
    
    if (deviations == NULL) {
        // Failed to allocate memory
        return NULL;
    }

    for (i = 0; i < numCycles; i++) {
        double total = 0;
        double variance2 = 0;
        for (j = i * cycleLength; j < i * cycleLength + cycleLength; j++) {
            total += array[j];
        }
        double mean = total / cycleLength;

        for (j = i * cycleLength; j < i * cycleLength + cycleLength; j++) {
            variance2 += pow((array[j] - mean), 2);
        }

        double deviation = sqrt(variance2 / qchisq);
        deviations[i] = deviation*2.3263;
    }

    return deviations;
}
