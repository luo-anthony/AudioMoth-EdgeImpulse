#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "digitalFilter.h"

/* Code entry point */

int main() {

    float gain, yc0, yc1;

    DF_filterType_t filterType;

    DigitalFilter_designHighPassFilter(16000, 48);

    DigitalFilter_readSettings(&gain, &yc0, &yc1, &filterType);

    printf("48Hz Filter\n-----------\n\nGain: %f\nCoef: %f\n\n", gain, yc0);

    DigitalFilter_designHighPassFilter(16000, 8);

    DigitalFilter_readSettings(&gain, &yc0, &yc1, &filterType);

    printf("8Hz Filter\n----------\n\nGain: %f\nCoef: %f\n\n", gain, yc0);

}
