#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

using namespace LongNumber;

TEST(ShiftTest, ShiftLeftOperator) {
    LongMath a("5.0", 4);
    LongMath result = a << 1;

    std::vector<bool> expected_integer = {1, 0, 1, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    EXPECT_EQ(result.to_decimal_integer(), "10");

    EXPECT_EQ(a.to_decimal_integer(), "5");
}

TEST(ShiftTest, ShiftLeftAssignOperator) {
    LongMath a("5.0", 4);
    a <<= 1;

    std::vector<bool> expected_integer = {1, 0, 1, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(a.get_integer_part(), expected_integer);
    EXPECT_EQ(a.to_decimal_integer(), "10");
}

TEST(ShiftTest, ShiftLeftFractional) {
    LongMath a("0.5", 4);
    a <<= 1;

    std::vector<bool> expected_integer = {1};
    std::vector<bool> expected_fractional = {0};

    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "1");
}

TEST(ShiftTest, ShiftLeftMixed) {
    LongMath a("1.5", 4);
    a <<= 1;

    std::vector<bool> expected_integer = {1, 1};
    std::vector<bool> expected_fractional = {0};

    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "3");
}

TEST(ShiftTest, ShiftLeftMultipleBits) {
    LongMath a("1.625", 4);
    a <<= 2;

    std::vector<bool> expected_integer = {1, 1, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    std::vector<bool> expected_fractional = {1, 0, 0, 0};

    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "6");
}

TEST(ShiftTest, ShiftLeftZero) {
    LongMath a("0.0", 4);
    a <<= 1;

    std::vector<bool> expected_integer = {0};
    std::vector<bool> expected_fractional = {0};

    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "0");
}

TEST(ShiftTest, ShiftLeftNegative) {
    LongMath a("-2.5", 4);
    a <<= 1;

    std::vector<bool> expected_integer = {1, 0, 1};
    std::vector<bool> expected_fractional = {0};

    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "-5");
    EXPECT_TRUE(a.get_sign());
}

TEST(ShiftTest, ShiftRightOperator) {
    LongMath a("2", 4);
    LongMath result = a >> 1;
    
    std::vector<bool> expected_integer = {1};
    std::vector<bool> expected_fractional = {0, 0, 0, 0};
    
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(result.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(result.to_decimal_integer(), "1");
}

TEST(ShiftTest, ShiftRightAssignOperator) {
    LongMath a("3", 4);
    a >>= 1;
    
    std::vector<bool> expected_integer = {1};
    std::vector<bool> expected_fractional = {1, 0, 0, 0};
    
    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
}

TEST(ShiftTest, ShiftRightMultipleBits) {
    LongMath a("8", 4);
    a >>= 2;
    
    std::vector<bool> expected_integer = {1, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    std::vector<bool> expected_fractional = {0, 0, 0, 0};
    
    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "2");
}

TEST(ShiftTest, ShiftRightFractional) {
    LongMath a("1.5", 4);
    a >>= 1;
    
    std::vector<bool> expected_integer = {0};
    std::vector<bool> expected_fractional = {1, 1, 0, 0};
    
    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
}

TEST(ShiftTest, ShiftRightZero) {
    LongMath a("0", 4);
    a >>= 1;
    
    std::vector<bool> expected_integer = {0};
    std::vector<bool> expected_fractional = {0, 0, 0, 0};
    
    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "0");
}

TEST(ShiftTest, ShiftRightNegative) {
    LongMath a("-2", 4);
    a >>= 1;
    
    std::vector<bool> expected_integer = {1};
    std::vector<bool> expected_fractional = {0, 0, 0, 0};
    
    EXPECT_EQ(a.get_integer_part(), expected_integer);
    for (size_t i = 0; i < expected_fractional.size(); ++i) {
        EXPECT_EQ(a.get_fractional_part()[i], expected_fractional[i]);
    }
    EXPECT_EQ(a.to_decimal_integer(), "-1");
    EXPECT_TRUE(a.get_sign());
}
