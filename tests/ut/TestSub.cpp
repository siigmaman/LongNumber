#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

using namespace LongNumber;

TEST(SubtractionTest, SimpleSubtraction) {
    LongMath a("5", 0);
    LongMath b("3", 0);
    LongMath result = a - b;

    std::vector<bool> expected_integer = {1, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    EXPECT_FALSE(result.get_sign());
    EXPECT_EQ(result.to_decimal_integer(), "2");
}

TEST(SubtractionTest, NegativeResult) {
    LongMath a("3", 0);
    LongMath b("5", 0);
    LongMath result = a - b;

    std::vector<bool> expected_integer = {1, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    EXPECT_TRUE(result.get_sign());
    EXPECT_EQ(result.to_decimal_integer(), "-2");
}

TEST(SubtractionTest, FractionalSubtraction) {
    LongMath a("1.5", 2);
    LongMath b("0.75", 2);
    LongMath result = a - b;
    std::vector<bool> expected_integer = {0};
    std::vector<bool> expected_fractional = {1, 1};
    auto result_frac = result.get_fractional_part();
    result_frac.resize(2);
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    EXPECT_EQ(result_frac, expected_fractional);
    EXPECT_FALSE(result.get_sign());
}

TEST(SubtractionTest, BorrowFromInteger) {
    LongMath a("1.0", 2);
    LongMath b("0.75", 2);
    LongMath result = a - b;
    std::vector<bool> expected_fractional = {0, 1};
    auto result_frac = result.get_fractional_part();
    result_frac.resize(2);
    EXPECT_EQ(result_frac, expected_fractional);
    EXPECT_FALSE(result.get_sign());
}

TEST(SubtractionTest, LargeNumbers) {
    LongMath a("987654321987654321.987654321", 9);
    LongMath b("123456789123456789.123456789", 9);
    LongMath result = a - b;

    EXPECT_EQ(result.to_decimal_integer(), "864197532864197532");
    EXPECT_FALSE(result.get_sign());
    LongMath reverse_result = b - a;
    EXPECT_TRUE(reverse_result.get_sign());
    auto reverse_bits = reverse_result.get_integer_part();
    auto result_bits = result.get_integer_part();
    EXPECT_EQ(reverse_bits.size(), result_bits.size());
    for (size_t i = 0; i < result_bits.size(); ++i) {
        EXPECT_EQ(reverse_bits[i], result_bits[i]);
    }
}
