#include <stdio.h>

#include "intPalindrome.h"

int readValue(const char *prompt, const char *incorrectValueMessage) {
    int value;
    printf("%s", prompt);
    while ((scanf("%d", &value) != 1)) {
        while (getchar() != '\n') {}
        printf("%s", incorrectValueMessage);
    }
    return value;
}

int main(void) {
    int value = readValue("enter a number: ", "incorrect value, should be nuber; try again: ");

    if (isPalindrome(value)) {
        printf("number is a palinfrome\n");
    } else {
        printf("number is not a palinfrome\n");
    }
}
