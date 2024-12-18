#include "binaryToDecimal.h"

#include <stdint.h>
#include <stdlib.h>

char *binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return NULL;
    }

    uint64_t number = 0;

    for (int i = 0; binaryString[i] != '\0'; ++i) {
        if (i >= 32) {
            return NULL;
        }

        char digit = binaryString[i];
        if (digit == '0' || digit == '1') {
            number *= 2;
            number += digit - '0';
        } else {
            return NULL;
        }
    }

    uint64_t numberCopy = number;
    int numberLength = number == 0 ? 1 : 0;
    while (numberCopy > 0) {
        ++numberLength;
        numberCopy /= 10;
    }

    // add 1 for null
    char *decimal = calloc(numberLength + 1, sizeof(char));
    if (decimal == NULL) {
        return NULL;
    }

    for (int i = numberLength - 1; i >= 0; --i) {
        decimal[i] = number % 10 + '0';
        number /= 10;
    }

    return decimal;
}
