#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdio.h>
#include <stdlib.h>

#include "commentsExtractor.h"

#define TEST_FILES "testFiles/"
#define INPUT "_input.txt"
#define OUTPUT "_output.txt"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

static void testCase(const char *inputFilename, const char *expectedResultFilename) {
    const char *outputFilename = "testOutputFile.txt";

    FILE *inputRead = fopen(inputFilename, "r");
    ASSERT_NOT_NULL(inputRead);

    FILE *outputWrite = fopen(outputFilename, "w");
    ASSERT_NOT_NULL(outputWrite);

    ASSERT_TRUE(extractSemicolonComments(inputRead, outputWrite));

    ASSERT_EQUAL(fclose(inputRead), 0);
    ASSERT_EQUAL(fclose(outputWrite), 0);

    FILE *realOutputRead = fopen(outputFilename, "r");
    ASSERT_NOT_NULL(realOutputRead);

    FILE *expectedOutputRead = fopen(expectedResultFilename, "r");
    ASSERT_NOT_NULL(expectedOutputRead);

    while (!feof(realOutputRead)) {
        int realReadResult = fgetc(realOutputRead);
        int expectedReadResult = fgetc(expectedOutputRead);

        ASSERT_EQUAL(realReadResult, expectedReadResult);

        if (realReadResult == EOF) {
            break;
        }
    }

    ASSERT_EQUAL(fclose(realOutputRead), 0);
    ASSERT_EQUAL(fclose(expectedOutputRead), 0);

    ASSERT_EQUAL(remove(outputFilename), 0);
}

CTEST(commentExtractorTests, singleCommentTest) {
    testCase(
        TEST_FILES "singleComment" INPUT,
        TEST_FILES "singleComment" OUTPUT);
}

CTEST(commentExtractorTests, severalCommentsTest) {
    testCase(
        TEST_FILES "severalComments" INPUT,
        TEST_FILES "severalComments" OUTPUT);
}
