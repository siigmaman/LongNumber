#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

using namespace LongNumber;

TEST(AdditionTest, IntegerAddition) {
    LongMath a("5", 0);
    LongMath b("3", 0);
    LongMath result = a + b;

    std::vector<bool> expected_integer = {1, 0, 0, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    EXPECT_FALSE(result.get_sign());
}

TEST(AdditionTest, FractionalAddition) {
    LongMath a("0.5", 1);
    LongMath b("0.25", 2);
    LongMath result = a + b;
    std::vector<bool> expected_fractional = {1, 1};
    auto result_frac = result.get_fractional_part();
    result_frac.resize(2);
    EXPECT_EQ(result_frac, expected_fractional);
}

TEST(AdditionTest, MixedAddition) {
    LongMath a("1.75", 1);
    LongMath b("2.5", 2);
    LongMath result = a + b;
    
    std::vector<bool> expected_integer = {1, 0, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    std::vector<bool> expected_fractional = {0, 1};

    auto result_frac = result.get_fractional_part();
    result_frac.resize(2);

    EXPECT_EQ(result.get_integer_part(), expected_integer);
    EXPECT_EQ(result_frac, expected_fractional);
}

TEST(AdditionTest, NegativeNumbers) {
    LongMath a("-2", 0);
    LongMath b("-2", 0);
    LongMath result = a + b;

    std::vector<bool> expected_integer = {1, 0, 0};
    std::reverse(expected_integer.begin(), expected_integer.end());
    EXPECT_EQ(result.get_integer_part(), expected_integer);
    EXPECT_TRUE(result.get_sign());
}

TEST(AdditionTest, VeryLargeNumbers) {

    LongMath a("123456789123456789.123456789", 9);
    LongMath b("987654321987654321.987654321", 9);
    LongMath result = a + b;

    EXPECT_EQ(result.to_decimal_integer(), "1111111111111111111");
    for (size_t i = 0; i < result.get_fractional_part().size(); i++) {
        std::cout << result.get_fractional_part()[i];
    }
    auto integer_bits = result.get_integer_part();
    EXPECT_TRUE(integer_bits[0]);
    EXPECT_TRUE(integer_bits[integer_bits.size() - 1]);

    EXPECT_FALSE(result.get_sign());

    LongMath reverse_result = b + a;
    EXPECT_EQ(result.get_integer_part(), reverse_result.get_integer_part());

    auto fractional_bits = result.get_fractional_part();
    std::vector<bool> expected_fractional_start = {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1};
    for (size_t i = 0; i < expected_fractional_start.size(); i++) {
        EXPECT_EQ(fractional_bits[i], expected_fractional_start[i]);
    }
}
