#ifndef LONGNUMBER_HPP
#define LONGNUMBER_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>

class LongNumber {
private:
    int precision;
    bool isNegative;

    void normalize();
    void addBit(bool bit);
    bool isZero() const;
    void shiftRight(int n);
    void shiftLeft(int n);

public:
    std::vector<bool> bits;
    LongNumber();
    LongNumber(int prec);
    LongNumber(double value, int prec);
    LongNumber(const LongNumber& other);

    std::vector<bool> gett();

    LongNumber& operator=(const LongNumber& other);

    ~LongNumber();

    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;

    /*
    func(a + b) // передаст просто значение
    func(a += b) // передаст новый a
    */

    LongNumber& operator+=(const LongNumber& other);
    LongNumber& operator-=(const LongNumber& other);
    LongNumber& operator*=(const LongNumber& other);
    LongNumber& operator/=(const LongNumber& other);

    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;
    bool operator<=(const LongNumber& other) const;
    bool operator>=(const LongNumber& other) const;

    void fromDouble(double value);

    void setPrecision(int prec);
    int getPrecision() const;

    void printBinary() const;
    std::string toDecimalString() const;

    static LongNumber calculatePi(int precision);
};

LongNumber operator""_longnum(long double value);

#endif
