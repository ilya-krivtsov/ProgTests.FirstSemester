#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "intPalindrome.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

CTEST(intPalindromeTests, zeroTest) {
    ASSERT_TRUE(isPalindrome(0));
    ASSERT_TRUE(isPalindrome(-0));
}

CTEST(intPalindromeTests, oneDigitTest) {
    ASSERT_TRUE(isPalindrome(1));
    ASSERT_TRUE(isPalindrome(3));
    ASSERT_TRUE(isPalindrome(7));

    ASSERT_TRUE(isPalindrome(-8));
    ASSERT_TRUE(isPalindrome(-2));
    ASSERT_TRUE(isPalindrome(-6));
}

CTEST(intPalindromeTests, twoDigitsTest) {
    ASSERT_TRUE(isPalindrome(11));
    ASSERT_TRUE(isPalindrome(33));
    ASSERT_TRUE(isPalindrome(77));

    ASSERT_TRUE(isPalindrome(-88));
    ASSERT_TRUE(isPalindrome(-22));
    ASSERT_TRUE(isPalindrome(-66));
}

CTEST(intPalindromeTests, randomNumberTest) {
    ASSERT_TRUE(isPalindrome(15351));
    ASSERT_TRUE(isPalindrome(854458));
    ASSERT_TRUE(isPalindrome(7235327));

    ASSERT_TRUE(isPalindrome(-83438));
    ASSERT_TRUE(isPalindrome(-220022));
    ASSERT_TRUE(isPalindrome(-6326236));
}

CTEST(intPalindromeTests, notPalindromeTest) {
    ASSERT_FALSE(isPalindrome(12));
    ASSERT_FALSE(isPalindrome(123));
    ASSERT_FALSE(isPalindrome(1234));

    ASSERT_FALSE(isPalindrome(155553342));
    ASSERT_FALSE(isPalindrome(8534223));
    ASSERT_FALSE(isPalindrome(1232432));
    ASSERT_FALSE(isPalindrome(-83243432));
    ASSERT_FALSE(isPalindrome(-220334442));
    ASSERT_FALSE(isPalindrome(-632642333));
}
