#include "commentsExtractor.h"

#include <stdbool.h>
#include <stdio.h>

bool extractSemicolonComments(FILE *input, FILE *output) {
    if (input == NULL || output == NULL) {
        return false;
    }

    bool isComment = false;
    while (!feof(input)) {
        int readCharacter = fgetc(input);
        if (readCharacter == EOF) {
            break;
        }

        if (readCharacter == ';') {
            isComment = true;
        } else if (readCharacter == '\n') {
            if (isComment) {
                fputc('\n', output);
            }
            isComment = false;
        }

        if (isComment) {
            fputc(readCharacter, output);
        }
    }

    return true;
}
