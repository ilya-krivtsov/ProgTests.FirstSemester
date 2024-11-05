#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bogosort.h"

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = minValue + (rand() % (maxValue - minValue));
    }
}

void printArray(const int *array, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d", array[i]);
        if (i != length - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value;
    printf("%s", prompt);
    while ((scanf("%d", &value) != 1) || value < 0) {
        while (getchar() != '\n') {}
        printf("%s", incorrectValueMessage);
    }
    return value;
}

int main(void) {
    int arrayLength = 4;//readValue("enter array length: ", "incorrect value, cannot be less than zero; try again: ");

    int *array = calloc(arrayLength, sizeof(int));

    if (array == NULL) {
        printf("allocaton failed\n");
        return 1;
    }

    srand(time(NULL));
    randomizeArray(array, arrayLength, 0, 1024);

    printf("array before bogosort:\n");
    printArray(array, arrayLength);

    bogosort(array, arrayLength);

    printf("array after bogosort:\n");
    printArray(array, arrayLength);

    free(array);
}
