#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>
#include <stdlib.h>

#include "graphCheck.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

static void testCase(int nodeCount, const char *matrix, const int *expectedResultNodes, int expectedResultNodesCount) {
    const char *inputFilename = "testInputFile.txt";

    FILE *inputWrite = fopen(inputFilename, "w");
    ASSERT_NOT_NULL(inputWrite);
    fprintf(inputWrite, "%d\n", nodeCount);
    fprintf(inputWrite, "%s\n", matrix);
    ASSERT_EQUAL(fclose(inputWrite), 0);

    FILE *inputRead = fopen(inputFilename, "r");
    ASSERT_NOT_NULL(inputRead);

    int *reachableNodes = NULL;
    int reachableNodesCount = 0;
    ASSERT_TRUE(getAllReachableNodes(inputRead, &reachableNodes, &reachableNodesCount));

    ASSERT_EQUAL(reachableNodesCount, expectedResultNodesCount);

    for (int i = 0; i < reachableNodesCount; ++i) {
        ASSERT_EQUAL(expectedResultNodes[i], reachableNodes[i]);
    }

    free(reachableNodes);

    ASSERT_EQUAL(fclose(inputRead), 0);
    ASSERT_EQUAL(remove(inputFilename), 0);
}

CTEST(graphCheckTests, emptyGraphTest) {
    testCase(0, "", NULL, 0);
}

CTEST(graphCheckTests, singleNodeTest) {
    int expectedResult[1] = { 0 };
    testCase(1, "0", expectedResult, sizeof(expectedResult) / sizeof(int));
}

CTEST(graphCheckTests, twoNodeTest) {
    int expectedResult[2] = { 0, 1 };
    testCase(2,
        "0 1\n"
        "1 0",
        expectedResult, sizeof(expectedResult) / sizeof(int));
}

CTEST(graphCheckTests, threeNodeTest) {
    int expectedResult[2] = { 0, 1 };
    testCase(3,
        "0 1 1\n"
        "1 0 1\n"
        "0 0 0",
        expectedResult, sizeof(expectedResult) / sizeof(int));
}

CTEST(graphCheckTests, eightNodeTest) {
    int expectedResult[3] = { 0, 1, 2 };
    testCase(8,
        "0 0 1 0 0 0 0 0\n"
        "1 0 0 0 0 0 0 0\n"
        "0 1 0 1 0 0 0 0\n"
        "0 0 0 0 1 0 0 0\n"
        "0 0 0 0 0 1 0 0\n"
        "0 0 0 0 0 0 1 0\n"
        "0 0 0 0 0 0 0 1\n"
        "0 0 0 0 0 1 0 0",
        expectedResult, sizeof(expectedResult) / sizeof(int));
}
