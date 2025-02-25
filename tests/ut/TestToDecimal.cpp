#include <gtest/gtest.h>
#include "../../src/LongNumber.h"

TEST(ToDecimalTest, IntegerConversion) {
    EXPECT_EQ(LongNumber::LongMath("5", 0).to_decimal_integer(), "5");     
    EXPECT_EQ(LongNumber::LongMath("6", 0).to_decimal_integer(), "6");     
    EXPECT_EQ(LongNumber::LongMath("7", 0).to_decimal_integer(), "7");     
    EXPECT_EQ(LongNumber::LongMath("8", 0).to_decimal_integer(), "8");    
    EXPECT_EQ(LongNumber::LongMath("-5", 0).to_decimal_integer(), "-5"); 
    EXPECT_EQ(LongNumber::LongMath("-8", 0).to_decimal_integer(), "-8"); 
    EXPECT_EQ(LongNumber::LongMath("0", 0).to_decimal_integer(), "0");     
    EXPECT_EQ(LongNumber::LongMath("1", 0).to_decimal_integer(), "1");     
    EXPECT_EQ(LongNumber::LongMath("255", 0).to_decimal_integer(), "255"); 
    EXPECT_EQ(LongNumber::LongMath("1023", 0).to_decimal_integer(), "1023"); 
}

TEST(ToDecimalTest, LargeNumbers) {
    EXPECT_EQ(LongNumber::LongMath("65535", 0).to_decimal_integer(), "65535");
    EXPECT_EQ(LongNumber::LongMath("1092", 0).to_decimal_integer(), "1092");
    EXPECT_EQ(LongNumber::LongMath("-65535", 0).to_decimal_integer(), "-65535");
}

TEST(ToDecimalTest, FractionalConversion) {
    EXPECT_EQ(LongNumber::LongMath("0.5", 10).to_decimal(), "0.5");
    EXPECT_EQ(LongNumber::LongMath("0.25", 10).to_decimal(), "0.25");
    EXPECT_EQ(LongNumber::LongMath("0.125", 10).to_decimal(), "0.125");
    EXPECT_EQ(LongNumber::LongMath("0.0625", 10).to_decimal(), "0.0625");
    EXPECT_EQ(LongNumber::LongMath("0.3333333", 10).to_decimal().substr(0, 8), "0.333333");
    EXPECT_EQ(LongNumber::LongMath("0.6666666", 10).to_decimal().substr(0, 8), "0.666666");
    EXPECT_EQ(LongNumber::LongMath("123.456", 10).to_decimal().substr(0, 8), "123.4559");
    EXPECT_EQ(LongNumber::LongMath("999.999", 10).to_decimal().substr(0, 12), "999.99899999");
    EXPECT_EQ(LongNumber::LongMath("-123.456", 10).to_decimal().substr(0, 12), "-123.4559999");
    EXPECT_EQ(LongNumber::LongMath("0.0001", 10).to_decimal().substr(0, 9), "0.0000999");
    EXPECT_EQ(LongNumber::LongMath("0.00001", 10).to_decimal().substr(0, 9), "0.0000099");
    EXPECT_EQ(LongNumber::LongMath("999999.999999", 12).to_decimal().substr(0, 14), "999999.9999989");
}
