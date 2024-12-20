#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>

#include "hashset.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

Hashset *createNewHashset(void) {
    Hashset *hashset = NULL;
    ASSERT_TRUE(createHashset(&hashset));
    return hashset;
}

CTEST(hashsetTests, createTest) {
    Hashset *hashset = createNewHashset();
    disposeHashset(hashset);
}

CTEST(hashsetTests, singleElemenTest) {
    Hashset *hashset = createNewHashset();

    ASSERT_FALSE(containedInHashset(hashset, "element"));
    ASSERT_TRUE(addToHashset(hashset, "element"));
    ASSERT_TRUE(containedInHashset(hashset, "element"));
    ASSERT_FALSE(containedInHashset(hashset, "not_element"));

    disposeHashset(hashset);
}

CTEST(hashsetTests, randomElementsTest) {
    char *elements[HASHSET_SIZE] = { 0 };

    const char *elementTemplate = "key_000";
    const int elementOffset = strlen("key_");
    const int digitsCount = strlen(elementTemplate) - elementOffset;

    for (int i = 0; i < HASHSET_SIZE; ++i) {
        char *element = strdup(elementTemplate);

        ASSERT_NOT_NULL(element);

        elements[i] = element;

        int number = i;
        for (int j = digitsCount - 1; j >= 0; --j) {
            char digit = (number % 10) + '0';
            element[elementOffset + j] = digit;
            number /= 10;
        }
    }

    Hashset *hashset = createNewHashset();

    srand(453563458);
    for (int i = 0; i < HASHSET_SIZE; ++i) {
        int index = (rand() % (HASHSET_SIZE - i)) + i;

        ASSERT_TRUE(addToHashset(hashset, elements[i]));
    }

    for (int i = 0; i < HASHSET_SIZE; ++i) {
        ASSERT_TRUE(containedInHashset(hashset, elements[i]));
    }

    ASSERT_FALSE(containedInHashset(hashset, "random_element"));
    ASSERT_FALSE(containedInHashset(hashset, "does_not_exist"));

    for (int i = 0; i < HASHSET_SIZE; ++i) {
        free(elements[i]);
    }

    disposeHashset(hashset);
}
