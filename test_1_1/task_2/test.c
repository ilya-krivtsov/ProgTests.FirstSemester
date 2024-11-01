#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>

#include "bogosort.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

void assertSorted(int *array, int arrayLength) {
    for (int i = 1; i < arrayLength; ++i) {
        ASSERT_GE(array[i], array[i - 1]);
    }
}

void sortAndAssert(int *array, int arrayLength) {
    bogosort(array, arrayLength);

    for (int i = 1; i < arrayLength; ++i) {
        ASSERT_GE(array[i], array[i - 1]);
    }
}

void randomizeArray(int *array, int arrayLength, int minValue, int maxValue) {
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = minValue + (rand() % (maxValue - minValue));
    }
}

CTEST(bogosortTests, emptyArrayTest) {
    bogosort(NULL, 0);
}

CTEST(bogosortTests, oneElementArrayTest) {
#define size 1
    srand(8192);

    int array[size] = { 24 };
    sortAndAssert(array, size);
#undef size
}

CTEST(bogosortTests, sameElementsArrayTest) {
#define size 4
    srand(8192);

    int array[size] = { 31, 31, 31, 31 };
    sortAndAssert(array, size);
#undef size
}

// impossible to test
CTEST_SKIP(bogosortTests, constantArrayTest) {
#define size 4
    srand(3434);

    int array[size] = { 234, 122, 4222, 325 };
    sortAndAssert(array, size);
#undef size
}

// impossible to test
CTEST_SKIP(bogosortTests, randomArrayTest) {
#define size 4
    srand(4353);

    int array[size];
    randomizeArray(array, size, 2, 12);
    sortAndAssert(array, size);
#undef size
}
