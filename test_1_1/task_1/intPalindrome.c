#include "intPalindrome.h"

#include <stdlib.h>

bool isPalindrome(int number) {
    int buffer[32] = { 0 };

    number = abs(number);

    int numberLength = 0;
    while (number > 0) {
        buffer[numberLength] = number % 10;
        number /= 10;
        ++numberLength;
    }

    for (int i = 0; i < (numberLength + 1) / 2; ++i) {
        if (buffer[i] != buffer[numberLength - i - 1]) {
            return false;
        }
    }

    return true;
}
