#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>

#include "binaryToDecimal.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

void assertString(const char *input, const char *expectedOutput) {
    char *output = binaryToDecimal(input);
    ASSERT_NOT_NULL(output);
    ASSERT_STR(output, expectedOutput);
    free(output);
}

CTEST(binaryToDecimalTest, incorrectStrings) {
    ASSERT_NULL(binaryToDecimal("3435345"));
    ASSERT_NULL(binaryToDecimal("sdfghzsffrsw"));
    ASSERT_NULL(binaryToDecimal("01010101bbbbbbb124213432432"));
}

CTEST(binaryToDecimalTest, tooLongStrings) {
    ASSERT_NULL(binaryToDecimal("011001100110011001100110011001101"));
    ASSERT_NULL(binaryToDecimal("011001100110011001100110011001101001011101"));
    ASSERT_NULL(binaryToDecimal("011001100110011001100110011001101010101011"));
}

CTEST(binaryToDecimalTest, basicStrings) {
    assertString("0", "0");
    assertString("000", "0");
    assertString("1", "1");
    assertString("001", "1");
    assertString("10", "2");
    assertString("010", "2");
    assertString("11", "3");
    assertString("011", "3");
}

CTEST(binaryToDecimalTest, regularStrings) {
    assertString("10101010", "170");
    assertString("11111111", "255");
    assertString("110100011010", "3354");
}
