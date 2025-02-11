#include "LongNumber.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <sstream>

namespace LongArithmetic {

LongNumber::LongNumber() : precision(0), isNegative(false) {}

LongNumber::LongNumber(int prec) : precision(prec), isNegative(false) {}

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

LongNumber LongNumber::operator-(const LongNumber& other) const {
    LongNumber result(std::max(precision, other.precision));
    bool borrow = false;
    for (int i = bits.size() - 1; i >= 0; --i) {
        bool diff = bits[i] ^ other.bits[i] ^ borrow;
        borrow = (!bits[i] && other.bits[i]) || (!bits[i] && borrow) || (other.bits[i] && borrow);
        result.bits[i] = diff;
    }
    return result;
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    LongNumber result(precision + other.precision));
    for (int i = 0; i < bits.size(); ++i) {
        if (bits[i]) {
            LongNumber temp = other;
            temp.shiftLeft(i);
            result = result + temp;
        }
    }
    return result;
}

LongNumber LongNumber::operator/(const LongNumber& other) const {
    if (other.isZero()) {
        throw std::invalid_argument("Division by zero");
    }
    LongNumber result(precision);
    LongNumber dividend = *this;
    LongNumber divisor = other;
    while (dividend >= divisor) {
        LongNumber temp = divisor;
        int shift = 0;
        while (dividend >= (temp << 1)) {
            temp = temp << 1;
            shift++;
        }
        dividend = dividend - temp;
        result.bits[shift] = true;
    }
    return result;
}

LongNumber& LongNumber::operator+=(const LongNumber& other) {
    *this = *this + other;
    return *this;
}

LongNumber& LongNumber::operator-=(const LongNumber& other) {
    *this = *this - other;
    return *this;
}

LongNumber& LongNumber::operator*=(const LongNumber& other) {
    *this = *this * other;
    return *this;
}

LongNumber& LongNumber::operator/=(const LongNumber& other) {
    *this = *this / other;
    return *this;
}


bool LongNumber::operator==(const LongNumber& other) const {
    return bits == other.bits && precision == other.precision && isNegative == other.isNegative;
}

bool LongNumber::operator!=(const LongNumber& other) const {
    return !(*this == other);
}

bool LongNumber::operator<(const LongNumber& other) const {
    if (isNegative != other.isNegative) {
        return isNegative;
    }
    if (bits.size() != other.bits.size()) {
        return bits.size() < other.bits.size();
    }
    for (int i = bits.size() - 1; i >= 0; --i) {
        if (bits[i] != other.bits[i]) {
            return bits[i] < other.bits[i];
        }
    }
    return false;
}

bool LongNumber::operator>(const LongNumber& other) const {
    return !(*this < other) && !(*this == other);
}

bool LongNumber::operator<=(const LongNumber& other) const {
    return (*this < other) || (*this == other);
}

bool LongNumber::operator>=(const LongNumber& other) const {
    return (*this > other) || (*this == other);
}

void LongNumber::setPrecision(int prec) {
    precision = prec;
}

int LongNumber::getPrecision() const {
    return precision;
}

void LongNumber::printBinary() const {
    for (bool bit : bits) {
        std::cout << bit;
    }
    std::cout << std::endl;
}

std::string LongNumber::toDecimalString() const {
    std::stringstream ss;
    if (isNegative) {
        ss << "-";
    }
    int intPart = 0;
    for (int i = bits.size() - 1; i >= 0; --i) {
        if (bits[i]) {
            intPart += (1 << (bits.size() - 1 - i));
        }
    }
    ss << intPart;

    if (precision > 0) {
        ss << ".";
        double fracPart = 0.0;
        for (int i = 0; i < precision; ++i) {
            if (bits[i]) {
                fracPart += 1.0 / (1 << (i + 1));
            }
        }
        ss << fracPart;
    }

    return ss.str();
}

LongNumber LongNumber::calculatePi(int precision) {
    LongNumber pi(precision);
    LongNumber one(1.0, precision);
    LongNumber sixteen(16.0, precision);
    LongNumber term(0.0, precision);
    LongNumber sum(0.0, precision);

    for (int k = 0; k < precision; ++k) {
        LongNumber kTerm(8.0 * k, precision);
        LongNumber denominator1 = kTerm + one;
        LongNumber denominator2 = kTerm + LongNumber(4.0, precision);
        LongNumber denominator3 = kTerm + LongNumber(5.0, precision);
        LongNumber denominator4 = kTerm + LongNumber(6.0, precision);

        term = (LongNumber(4.0, precision) / denominator1) -
               (LongNumber(2.0, precision) / denominator2) -
               (LongNumber(1.0, precision) / denominator3) -
               (LongNumber(1.0, precision) / denominator4);

        term = term / (sixteen ^ k);
        sum = sum + term;
    }

    return sum;
}

LongNumber operator""_longnum(long double value) {
    return LongNumber(static_cast<double>(value), 10);
}

}
