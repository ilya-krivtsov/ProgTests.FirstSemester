#include "bogosort.h"

#include <stdbool.h>
#include <stdlib.h>

void bogosort(int *array, int arrayLength) {
    if (arrayLength <= 1) {
        return;
    }

    do {
        bool sorted = true;
        for (int i = 1; i < arrayLength; ++i) {
            if (array[i] < array[i - 1]) {
                sorted = false;
                break;
            }
        }
        if (sorted) {
            return;
        }

        for (int i = 0; i < arrayLength - 1; i++) {
            int rem = (arrayLength - i - 1);
            int j = i + (rand() % rem);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    } while (true);
}
