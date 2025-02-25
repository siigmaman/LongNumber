#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

using namespace LongNumber;

TEST(TestFromString, PositiveIntegerConversion) {
    LongMath num("123", 10);
    std::vector<bool> expected_int = {1, 1, 1, 1, 0, 1, 1};
    std::reverse(expected_int.begin(), expected_int.end());
    for (int i = 0; i < expected_int.size(); i++) {
        EXPECT_EQ(num.get_integer_part()[i], expected_int[i]);
    }
    EXPECT_FALSE(num.get_sign());
}

TEST(TestFromString, NegativeIntegerConversion) {
    LongMath num("-42", 10);
    
    std::vector<bool> expected_int = {1, 0, 1, 0, 1, 0};
    std::reverse(expected_int.begin(), expected_int.end());
    for (int i = 0; i < expected_int.size(); i++) {
        EXPECT_EQ(num.get_integer_part()[i], expected_int[i]);
    }
    EXPECT_TRUE(num.get_sign());
}

TEST(TestFromString, DecimalNumberConversion) {
    LongMath num("10.5", 10);
    
    std::vector<bool> expected_int = {1, 0, 1, 0};
    std::reverse(expected_int.begin(), expected_int.end());
    for (int i = 0; i < expected_int.size(); i++) {
        EXPECT_EQ(num.get_integer_part()[i], expected_int[i]);
    }
    
    std::vector<bool> expected_frac = {1};
    for (int i = 0; i < expected_frac.size(); i++) {
        EXPECT_EQ(num.get_fractional_part()[i], expected_frac[i]);
    }
}

TEST(TestFromString, ZeroConversion) {
    LongMath num("0", 10);
    
    std::vector<bool> expected_int = {0};
    std::reverse(expected_int.begin(), expected_int.end());
    for (int i = 0; i < expected_int.size(); i++) {
        EXPECT_EQ(num.get_integer_part()[i], expected_int[i]);
    }
    EXPECT_FALSE(num.get_sign());
}

TEST(TestFromString, LargeNumberConversion) {
    LongMath num("123456789", 10);
    std::vector<bool> expected_int = {
        1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1
    };
    std::reverse(expected_int.begin(), expected_int.end());
    for (int i = 0; i < expected_int.size(); i++) {
        EXPECT_EQ(num.get_integer_part()[i], expected_int[i]);
    }
}

TEST(TestFromString, SmallDecimalConversion) {
    LongMath num("0.125", 10);

    std::vector<bool> expected_int = {0};
    std::reverse(expected_int.begin(), expected_int.end());
    for (int i = 0; i < expected_int.size(); i++) {
        EXPECT_EQ(num.get_integer_part()[i], expected_int[i]);
    }

    std::vector<bool> expected_frac = {0, 0, 1};
    for (int i = 0; i < expected_frac.size(); i++) {
        EXPECT_EQ(num.get_fractional_part()[i], expected_frac[i]);
    }
}

TEST(TestFromString, PrecisionTest) {
    LongMath num("0.1", 4);

    std::vector<bool> expected_frac = {0, 0, 0, 1};
    for (int i = 0; i < expected_frac.size(); i++) {
        EXPECT_EQ(num.get_fractional_part()[i], expected_frac[i]);
    }
}

TEST(TestFromString, EmptyStringConversion) {
    LongMath num("", 10);

    std::vector<bool> expected_int = {0};
    std::reverse(expected_int.begin(), expected_int.end());
    for (int i = 0; i < expected_int.size(); i++) {
        EXPECT_EQ(num.get_integer_part()[i], expected_int[i]);
    }
    EXPECT_FALSE(num.get_sign());
}

TEST(TestFromString, FractionalPrecisionPreservation) {
    LongMath num("1.5", 10);

    std::vector<bool> expected_frac = {1};
    std::reverse(expected_frac.begin(), expected_frac.end());
    for (int i = 0; i < expected_frac.size(); i++) {
        EXPECT_EQ(num.get_fractional_part()[i], expected_frac[i]);
    }
}
