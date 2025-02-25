#include <gtest/gtest.h>
#include "../../src/Helpers.h"

using namespace LongNumber;

TEST(HelpersTest, IncrementStringSimple) {
    EXPECT_EQ(IncrementString("123"), "124");
    EXPECT_EQ(IncrementString("999"), "1000");
    EXPECT_EQ(IncrementString("0"), "1");
    EXPECT_EQ(IncrementString("199"), "200");
}

TEST(HelpersTest, IncrementStringEdgeCases) {
    EXPECT_EQ(IncrementString("9"), "10");
    EXPECT_EQ(IncrementString("99999"), "100000");
    EXPECT_EQ(IncrementString("1999999999"), "2000000000");
}

TEST(HelpersTest, MultiplyStringByTwoSimple) {
    EXPECT_EQ(MultiplyStringByTwo("4"), "8");
    EXPECT_EQ(MultiplyStringByTwo("5"), "10");
    EXPECT_EQ(MultiplyStringByTwo("10"), "20");
    EXPECT_EQ(MultiplyStringByTwo("50"), "100");
}

TEST(HelpersTest, MultiplyStringByTwoEdgeCases) {
    EXPECT_EQ(MultiplyStringByTwo("99"), "198");
    EXPECT_EQ(MultiplyStringByTwo("999999"), "1999998");
    EXPECT_EQ(MultiplyStringByTwo("5555555"), "11111110");
    EXPECT_EQ(MultiplyStringByTwo("0"), "0");
}
