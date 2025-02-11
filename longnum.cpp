#include <vector>
#include <iostream>
#include <cmath>
#include "longnum.hpp"


LongNumber::LongNumber() : precision(0), isNegative(false) {}

LongNumber::LongNumber(int prec) : precision(prec), isNegative(false) {}

// str = 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000
LongNumber::LongNumber(double value, int prec) : precision(prec), isNegative(value < 0) {
    fromDouble(value);
}

LongNumber::LongNumber(const LongNumber& other)
    : bits(other.bits), precision(other.precision), isNegative(other.isNegative) {}

LongNumber& LongNumber::operator=(const LongNumber& other) {
    if (this != &other) {
        bits = other.bits;
        precision = other.precision;
        isNegative = other.isNegative;
    }
    return *this;
}

LongNumber::~LongNumber() {}

void LongNumber::normalize() {
    while (!bits.empty() && bits.back() == false) {
        bits.pop_back();
    }
    if (bits.empty()) {
        isNegative = false;
    }
}

void LongNumber::addBit(bool bit) {
    bits.push_back(bit);
}

bool LongNumber::isZero() const {
    return bits.empty();
}

void LongNumber::shiftRight(int n) {
    if (n <= 0) return;
    bits.insert(bits.begin(), n, false);
}

void LongNumber::shiftLeft(int n) {
    if (n <= 0) return;
    bits.erase(bits.begin(), bits.begin() + n);
}

void LongNumber::fromDouble(double value) {
    bits.clear();
    isNegative = value < 0;
    value = std::abs(value);

    int intPart = static_cast<int>(value);
    while (intPart > 0) {
        bits.push_back(intPart % 2);
        intPart /= 2;
    }
    std::reverse(bits.begin(), bits.end());

    double fracPart = value - static_cast<int>(value);
    for (int i = 0; i < precision; ++i) {
        fracPart *= 2;
        bits.push_back(static_cast<int>(fracPart) >= 1);
        if (fracPart >= 1) fracPart -= 1;
    }

    normalize();
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
    LongNumber result(std::max(precision, other.precision));
    bool carry = false;
    for (int i = bits.size() - 1; i >= 0; --i) {
        bool sum = bits[i] ^ other.bits[i] ^ carry;
        carry = (bits[i] && other.bits[i]) || (bits[i] && carry) || (other.bits[i] && carry);
        result.bits[i] = sum;
    }
    if (carry) {
        result.bits.insert(result.bits.begin(), true);
    }
    return result;
}
