#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

using namespace LongNumber;

TEST(DivisionTest, BasicDivision) {
    LongMath epsilon = LongMath::default_epsilon(10);

    EXPECT_TRUE(LongMath("10", 10).equals_with_epsilon(LongMath("10", 10), epsilon));

    LongMath result1 = LongMath("10", 10) / LongMath("2", 10);
    EXPECT_TRUE(result1.equals_with_epsilon(LongMath("5", 10), epsilon));

    LongMath result2 = LongMath("100", 10) / LongMath("10", 10);
    EXPECT_TRUE(result2.equals_with_epsilon(LongMath("10", 10), epsilon));

    LongMath result3 = LongMath("1000", 10) / LongMath("10", 10);
    EXPECT_TRUE(result3.equals_with_epsilon(LongMath("100", 10), epsilon));

    LongMath result4 = LongMath("1", 10) / LongMath("2", 10);
    EXPECT_TRUE(result4.equals_with_epsilon(LongMath("0.5", 10), epsilon));
    LongMath result5 = LongMath("1", 10) / LongMath("4", 10);
    EXPECT_TRUE(result5.equals_with_epsilon(LongMath("0.25", 10), epsilon));
    LongMath result6 = LongMath("1", 10) / LongMath("8", 10);
    EXPECT_TRUE(result6.equals_with_epsilon(LongMath("0.125", 10), epsilon));
}

TEST(DivisionTest, SignHandling) {
    EXPECT_TRUE((LongMath("10", 10) / LongMath("2", 10)).equals_with_epsilon(LongMath("5", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("-10", 10) / LongMath("2", 10)).equals_with_epsilon(LongMath("-5", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("10", 10) / LongMath("-2", 10)).equals_with_epsilon(LongMath("-5", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("-10", 10) / LongMath("-2", 10)).equals_with_epsilon(LongMath("5", 10), LongMath::default_epsilon(10)));
}

TEST(DivisionTest, SpecialCases) {
    EXPECT_TRUE((LongMath("123.456", 10) / LongMath("1", 10)).equals_with_epsilon(LongMath("123.456", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("0", 10) / LongMath("5", 10)).equals_with_epsilon(LongMath("0", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("1", 10) / LongMath("7", 10)).equals_with_epsilon(LongMath("0.142857142857", 10), LongMath::default_epsilon(10)));
}

TEST(DivisionTest, PrecisionTests) {
    EXPECT_TRUE((LongMath("1", 10) / LongMath("3", 10)).equals_with_epsilon(LongMath("0.333333333333", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("2", 10) / LongMath("3", 10)).equals_with_epsilon(LongMath("0.666666666666", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("1", 10) / LongMath("7", 10)).equals_with_epsilon(LongMath("0.142857142857", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("1", 10) / LongMath("9", 10)).equals_with_epsilon(LongMath("0.111111111111", 10), LongMath::default_epsilon(10)));
}

TEST(DivisionTest, ChainDivision) {
    LongMath a("1000", 10);
    LongMath b = a / LongMath("10", 10);
    EXPECT_TRUE(b.equals_with_epsilon(LongMath("100", 10), LongMath::default_epsilon(10)));
    
    LongMath c = b / LongMath("10", 10);
    EXPECT_TRUE(c.equals_with_epsilon(LongMath("10", 10), LongMath::default_epsilon(10)));
    
    LongMath d = c / LongMath("10", 10);
    EXPECT_TRUE(d.equals_with_epsilon(LongMath("1", 10), LongMath::default_epsilon(10)));
}

TEST(DivisionTest, ComplexDivision) {
    EXPECT_TRUE((LongMath("123.456", 10) / LongMath("2", 10)).equals_with_epsilon(LongMath("61.728", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("999.999", 10) / LongMath("3", 10)).equals_with_epsilon(LongMath("333.333", 10), LongMath::default_epsilon(10)));
    EXPECT_TRUE((LongMath("999999", 10) / LongMath("1000", 10)).equals_with_epsilon(LongMath("999.999", 10), LongMath::default_epsilon(10)));
    LongMath num1("1", 15);
    LongMath num2("3", 15);
    EXPECT_TRUE((num1 / num2).equals_with_epsilon(LongMath("0.333333333333333", 15), LongMath::default_epsilon(15)));
} 