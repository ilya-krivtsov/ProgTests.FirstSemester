#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdbool.h>
#include <stdio.h>

#include "fileParser.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

static bool isWhitespace(char c) {
    return c == ' ' || c == '\n';
}

static void testCase(int minRange, int maxRange, const char *input, const char *expectedOutput) {
    const char *inputFilename = "testInputFile.txt";
    const char *outputFilename = "testOutputFile.txt";

    FILE *inputWrite = fopen(inputFilename, "w");
    ASSERT_NOT_NULL(inputWrite);
    fprintf(inputWrite, "%s\n", input);
    ASSERT_EQUAL(fclose(inputWrite), 0);

    FILE *inputRead = fopen(inputFilename, "r");
    ASSERT_NOT_NULL(inputRead);

    FILE *outputWrite = fopen(outputFilename, "w");
    ASSERT_NOT_NULL(outputWrite);

    ASSERT_TRUE(rearrangeNumbers(inputRead, outputWrite, minRange, maxRange));

    ASSERT_EQUAL(fclose(inputRead), 0);
    ASSERT_EQUAL(fclose(outputWrite), 0);

    FILE *outputRead = fopen(outputFilename, "r");
    ASSERT_NOT_NULL(outputRead);

    for (int i = 0; expectedOutput[i] != '\0'; ++i) {
        int readResult = fgetc(outputRead);
        if (readResult == EOF) {
            break;
        }
        char fileChar = (char)readResult;
        char expectedChar = expectedOutput[i];

        if (isWhitespace(fileChar) && isWhitespace(expectedChar)) {
            continue;
        }

        ASSERT_EQUAL(fileChar, expectedChar);
    }

    ASSERT_EQUAL(fclose(outputRead), 0);

    ASSERT_EQUAL(remove(inputFilename), 0);
    ASSERT_EQUAL(remove(outputFilename), 0);
}

CTEST(fileParserTests, emptyArrayTest) {
    testCase(0, 1, "", "");
}

CTEST(fileParserTests, singleNumberTest) {
    testCase(4, 8, "2", "2");
    testCase(4, 8, "6", "6");
    testCase(4, 8, "10", "10");
}

CTEST(fileParserTests, severalNumberTest) {
    testCase(10, 20,
        "25 21 17 14 11 8 6 3",
        "8 6 3 17 14 11 25 21");

    testCase(32, 64,
        "24 60 31 27 96 29 52 47 20 35",
        "24 31 27 29 20 60 52 47 35 96");
}
