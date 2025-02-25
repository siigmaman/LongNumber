#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

using namespace LongNumber;

TEST(MultiplyTest, SimpleMultiplication) {
    LongMath a("2", 4);
    LongMath b("3", 4);
    LongMath result = a * b;
    
    std::vector<bool> expected = {1, 1, 0};
    std::reverse(expected.begin(), expected.end());
    EXPECT_EQ(result.get_integer_part(), expected);
    EXPECT_EQ(result.to_decimal_integer(), "6");
}

TEST(MultiplyTest, FractionByInteger) {
    LongMath a("0.5", 4);
    LongMath b("2", 4);
    LongMath result = a * b;
    std::vector<bool> expected_integer = {1};
    std::vector<bool> expected_fractional = {0, 0, 0};

    EXPECT_EQ(result.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(result.get_fractional_part()[i], expected_fractional[i]);
    }
}

TEST(MultiplyTest, FractionByFraction) {
    LongMath a("0.5", 4);
    LongMath b("0.5", 4);
    LongMath result = a * b;
    
    std::vector<bool> expected_integer = {0};
    std::vector<bool> expected_fractional = {0, 1, 0, 0};
    
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(result.get_fractional_part()[i], expected_fractional[i]);
    }
}

TEST(MultiplyTest, MixedNumbers) {
    LongMath a("1.5", 4);
    LongMath b("2.5", 4);
    LongMath result = a * b;
    
    std::vector<bool> expected_integer = {1, 1};
    std::vector<bool> expected_fractional = {1, 1, 0, 0};
    
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(result.get_fractional_part()[i], expected_fractional[i]);
    }
}

TEST(MultiplyTest, MultiplyByZero) {
    LongMath a("1.5", 4);
    LongMath b("0", 4);
    LongMath result = a * b;
    
    EXPECT_EQ(result.to_decimal_integer(), "0");
    EXPECT_FALSE(result.get_sign());
}

TEST(MultiplyTest, NegativeNumbers) {
    LongMath a("-2", 4);
    LongMath b("3", 4);
    LongMath result = a * b;
    
    std::vector<bool> expected = {0, 1, 1};
    EXPECT_EQ(result.get_integer_part(), expected);
    EXPECT_TRUE(result.get_sign());
    EXPECT_EQ(result.to_decimal_integer(), "-6");
    
    LongMath c("-2", 4);
    LongMath d("-3", 4);
    LongMath result2 = c * d;
    
    EXPECT_EQ(result2.get_integer_part(), expected);
    EXPECT_FALSE(result2.get_sign());
    EXPECT_EQ(result2.to_decimal_integer(), "6");
}

TEST(MultiplyTest, LargeNumbersWithFraction) {
    LongMath a("123.456789", 10);
    LongMath b("987.654321", 10);
    LongMath result = a * b;

    std::vector<bool> expected_integer = {1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    std::vector<bool> expected_fractional = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1};
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(result.get_fractional_part()[i], expected_fractional[i]);
    }

    LongMath c("-123.456789", 10);
    LongMath d("987.654321", 10);
    LongMath result2 = c * d;

    std::vector<bool> expected_integer2 = {1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};
    std::reverse(expected_integer2.begin(), expected_integer2.end());
    EXPECT_EQ(result2.get_integer_part(), expected_integer2);
    std::vector<bool> expected_fractional2 = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1};
    for (size_t i = 0; i < expected_fractional2.size(); ++i) {
        EXPECT_EQ(result2.get_fractional_part()[i], expected_fractional2[i]);
    }
    LongMath e("0.1", 10);
    LongMath f("0.01", 10);
    LongMath result3 = e * f;
    std::vector<bool> expected_integer3 = {0};
    std::vector<bool> expected_fractional3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,0};
    EXPECT_EQ(result3.get_integer_part(), expected_integer3);
    for (size_t i = 0; i < expected_fractional3.size(); ++i) {
        EXPECT_EQ(result3.get_fractional_part()[i], expected_fractional3[i]);
    }
}

TEST(MultiplyTest, VeryLargeNumbers) {
    LongMath a("999.999", 12);
    LongMath b("999.999", 12);
    LongMath result = a * b;
    std::vector<bool> expected_integer = {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 
    1, 1, 1, 1, 1, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    std::vector<bool> expected_fractional = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(result.get_fractional_part()[i], expected_fractional[i]);
    }
}
