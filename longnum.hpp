#ifndef LONGMATH
#define LONGMATH

#include <vector> 
#include <string> 
#include <iostream> 

namespace LongMath{
    class LongNumber{ 
    private:
        std::vector<short> digits; 
        unsigned decimalPoint; 
        unsigned precision; 
        bool isNegative; 

        void trimLeadingZeros(); 
        bool isZeroValue() const; 
        int getMagnitude() const; 

    public:
        LongNumber(); 
        explicit LongNumber(const std::string& value); 
        explicit LongNumber(int value);
        LongNumber(int value, int customPrecision);

        std::string toFormattedString() const; 
        std::string toFormattedString(int customPrecision) const; 

        friend std::ostream& operator<<(std::ostream& os, const LongNumber& num); 

        LongNumber negate() const; 

        friend bool areEqual(const LongNumber& num1, const LongNumber& num2);
        friend bool isLessThan(const LongNumber& num1, const LongNumber& num2); 
        friend bool isGreaterThan(const LongNumber& num1, const LongNumber& num2); 
        friend bool isLessOrEqual(const LongNumber& num1, const LongNumber& num2); 
        friend bool isGreaterOrEqual(const LongNumber& num1, const LongNumber& num2); 
        friend bool areNotEqual(const LongNumber& num1, const LongNumber& num2); 

        friend LongNumber subtract(const LongNumber& num1, const LongNumber& num2); 
        friend LongNumber add(const LongNumber& num1, const LongNumber& num2); 
        friend LongNumber multiply(const LongNumber& num1, const LongNumber& num2); 
        friend LongNumber divide(const LongNumber& num1, const LongNumber& num2); 

        LongNumber& subtractAssign(const LongNumber& other); 
        LongNumber& addAssign(const LongNumber& other);
        LongNumber& multiplyAssign(const LongNumber& other); 
        LongNumber& divideAssign(const LongNumber& other);
    };
}

LongMath::LongNumber createFromUnsignedLongLong(unsigned long long value);
LongMath::LongNumber createFromLongDouble(long double value); 

#endif
