#include <stdio.h>
#include <stdlib.h>

#include "binaryToDecimal.h"

int main(void) {
    printf("input binary number: ");
    char input[256] = { 0 };
    if (scanf("%255s", input) != 1) {
        printf("failed to read string\n");
        return 1;
    }

    char *decimal = binaryToDecimal(input);
    if (decimal == NULL) {
        printf("failed to convert string\n");
        return 1;
    }

    printf("number as decimal: %s\n", decimal);

    free(decimal);
}
