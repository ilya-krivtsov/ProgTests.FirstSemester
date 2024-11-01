#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    FILE *file = fopen("file.txt", "r");

    if (file == NULL) {
        printf("io error\n");
        return 1;
    }

    char previous = -1;
    while (!feof(file)) {
        char new = fgetc(file);
        if (new == '\0' || new == EOF) {
            break;
        }

        if (new != previous) {
            printf("%c", new);
            previous = new;
        }
    }

    fclose(file);
}
