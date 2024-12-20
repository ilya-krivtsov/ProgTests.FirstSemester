#include "hashset.h"

#include <stdlib.h>
#include <string.h>

typedef struct Hashset {
    char *elements[HASHSET_SIZE];
} Hashset;

bool createHashset(Hashset **hashset) {
    *hashset = malloc(sizeof(Hashset));
    if (*hashset == NULL) {
        return false;
    }

    for (int i = 0; i < HASHSET_SIZE; ++i) {
        (*hashset)->elements[i] = NULL;
    }

    return true;
}

static unsigned int getStringHash(const char *string) {
    unsigned int hash = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        hash = hash * 57 + string[i];
    }
    return hash;
}

bool addToHashset(Hashset *hashset, const char *string) {
    if (string == NULL) {
        return false;
    }

    unsigned int elementIndex = getStringHash(string) % HASHSET_SIZE;

    int counter = 0;
    while (hashset->elements[elementIndex] != NULL) {
        elementIndex = (elementIndex + 1) % HASHSET_SIZE;
        ++counter;
        if (counter >= HASHSET_SIZE) {
            return false;
        }
    }

    char *stringCopy = strdup(string);
    if (stringCopy == NULL) {
        return false;
    }

    hashset->elements[elementIndex] = stringCopy;
}

bool containedInHashset(Hashset *hashset, const char *string) {
    unsigned int elementIndex = getStringHash(string) % HASHSET_SIZE;

    if (hashset->elements[elementIndex] == NULL) {
        return false;
    }

    int counter = 0;
    while (strcmp(hashset->elements[elementIndex], string) != 0) {
        elementIndex = (elementIndex + 1) % HASHSET_SIZE;
        ++counter;
        if (counter >= HASHSET_SIZE) {
            return false;
        }
    }

    return true;
}

void disposeHashset(Hashset *hashset) {
    for (int i = 0; i < HASHSET_SIZE; ++i) {
        free(hashset->elements[i]);
    }
    free(hashset);
}
