#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

using namespace LongNumber;

TEST(CompareTest, PositiveNumbers) {
    LongMath a("10.5", 10);
    LongMath b("5.25", 10);
    LongMath c("10.5", 10);

    EXPECT_TRUE(a > b);
    EXPECT_TRUE(b < a);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a >= c);
    EXPECT_TRUE(b <= a);
}

TEST(CompareTest, NegativeNumbers) {
    LongMath a("-3.75", 10);
    LongMath b("-2.5", 10);
    LongMath c("-3.75", 10);

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(b >= a);
}

TEST(CompareTest, MixedSigns) {
    LongMath positive("5.0", 10);
    LongMath negative("-5.0", 10);
    LongMath zero("0.0", 10);

    EXPECT_TRUE(negative < positive);
    EXPECT_TRUE(positive > negative);
    EXPECT_TRUE(zero > negative);
    EXPECT_TRUE(zero < positive);
    EXPECT_TRUE(positive != negative);
}

TEST(CompareTest, FractionalParts) {
    LongMath a("3.1415", 10);
    LongMath b("3.1416", 10);
    LongMath c("3.14150000", 10);

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b >= a);
}

TEST(CompareTest, EdgeCases) {
    LongMath zero("0.0", 10);
    LongMath small("0.0000000001", 10);
    LongMath almost_zero("0.0000000000", 10);

    EXPECT_TRUE(small > zero);
    EXPECT_TRUE(almost_zero == zero);
    EXPECT_TRUE(small != zero);
    EXPECT_TRUE(small >= zero);
}

TEST(CompareTest, DifferentPrecisions) {
    LongMath a("1.2345", 4);
    LongMath b("1.23450000", 8);
    
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(CompareTest, DifferentIntegerLengths) {
    LongMath a("1234.5", 10);
    LongMath b("123.5", 10);
    
    EXPECT_TRUE(a > b);
    EXPECT_TRUE(b < a);
}
