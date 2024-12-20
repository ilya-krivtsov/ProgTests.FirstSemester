#include "fileParser.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    int capacity;
    int *elements;
} List;

static bool createList(List *list) {
    list->count = 0;
    list->capacity = 16;
    list->elements = calloc(list->capacity, sizeof(int));
    if (list->elements == NULL) {
        return false;
    }

    return true;
}

static bool addToList(List *list, int value) {
    if (list->count == list->capacity) {
        list->capacity *= 4;
        int *newElements = realloc(list->elements, list->capacity * sizeof(int));
        if (newElements == NULL) {
            return NULL;
        }
        list->elements = newElements;
    }
    list->elements[list->count] = value;
    ++list->count;
    return true;
}

static void disposeList(List list) {
    free(list.elements);
}

bool rearrangeNumbers(FILE *input, FILE *output, int minRange, int maxRange) {
    if (input == NULL || output == NULL) {
        return false;
    }

    if (minRange > maxRange) {
        return false;
    }

    List minList = { 0 };
    List midList = { 0 };
    List maxList = { 0 };

    if (!createList(&minList) || !createList(&midList) || !createList(&maxList)) {
        disposeList(minList);
        disposeList(midList);
        disposeList(maxList);

        return false;
    }

    while (!feof(input)) {
        int number = 0;
        if (fscanf(input, "%d", &number) != 1) {
            break;
        }
        if (number < minRange) {
            addToList(&minList, number);
        } else if (number <= maxRange) {
            addToList(&midList, number);
        } else {
            addToList(&maxList, number);
        }
    }

    List lists[3] = { minList, midList, maxList };

    for (int i = 0; i < 3; ++i) {
        List list = lists[i];
        for (int j = 0; j < list.count; ++j) {
            fprintf(output, "%d\n", list.elements[j]);
        }
    }

    return true;
}
