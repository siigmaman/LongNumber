#include "LongNumber.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

namespace LongMath {
    LongNumber::LongNumber() : isNegative(false), decimalPoint(0), precision(100) {
        digits.push_back(0);
    }

    LongNumber::LongNumber(int value) : decimalPoint(0), precision(100), isNegative(false) {
        if (value == 0) {
            digits.push_back(0);
            return;
        }

        if (value < 0) {
            isNegative = true;
            value = -value;
        }

        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
    }

    LongNumber::LongNumber(int value, int customPrecision) : decimalPoint(0), precision(customPrecision), isNegative(false) {
        if (value == 0) {
            digits.push_back(0);
            return;
        }

        if (value < 0) {
            isNegative = true;
            value = -value;
        }

        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
    }

    LongNumber::LongNumber(const std::string& value) {
        std::string input = value;
        if (input[0] == '-') {
            isNegative = true;
            input.erase(input.begin());
        } else {
            isNegative = false;
        }

        unsigned int dotPosition = input.find('.');
        if (dotPosition != std::string::npos) {
            decimalPoint = input.length() - dotPosition - 1;
            input.erase(dotPosition, 1);
        } else {
            decimalPoint = 0;
        }

        precision = std::max(100, static_cast<int>(decimalPoint + 10));

        for (auto it = input.rbegin(); it != input.rend(); ++it) {
            digits.push_back(*it - '0');
        }

        trimLeadingZeros();
    }

    bool LongNumber::isZeroValue() const {
        return digits.size() == 1 && digits[0] == 0;
    }

    int LongNumber::getMagnitude() const {
        int magnitude = digits.size() - decimalPoint;
        auto it = digits.rbegin();
        while (it != digits.rend() && *it == 0) {
            magnitude--;
            ++it;
        }
        return magnitude;
    }

    void LongNumber::trimLeadingZeros() {
        while (decimalPoint > 0 && digits.front() == 0) {
            digits.erase(digits.begin());
            --decimalPoint;
        }

        while (digits.size() > decimalPoint + 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    std::string LongNumber::toFormattedString() const {
        std::string result;
        if (isNegative) result += '-';

        for (int i = digits.size() - 1; i >= 0; --i) {
            result += static_cast<char>(digits[i] + '0');
            if (i == decimalPoint) {
                result += '.';
            }
        }

        if (decimalPoint == 0) {
            result += '0';
        }

        return result;
    }

    std::string LongNumber::toFormattedString(int customPrecision) const {
        std::string result;
        if (isNegative) result += '-';

        for (int i = digits.size() - 1; i >= 0 && i >= static_cast<int>(decimalPoint) - customPrecision; --i) {
            result += static_cast<char>(digits[i] + '0');
            if (i == decimalPoint) {
                result += '.';
            }
        }

        if (decimalPoint == 0) {
            result += '0';
        }

        return result;
    }

    std::ostream& operator<<(std::ostream& os, const LongNumber& num) {
        return os << num.toFormattedString();
    }

    LongNumber LongNumber::negate() const {
        LongNumber result(*this);
        result.isNegative = !isNegative;
        return result;
    }

    bool areEqual(const LongNumber& num1, const LongNumber& num2) {
        if (num1.isZeroValue() && num2.isZeroValue()) return true;

        if (num1.isNegative != num2.isNegative || num1.decimalPoint != num2.decimalPoint || num1.digits.size() != num2.digits.size()) return false;

        for (int i = 0; i < num1.digits.size(); ++i) {
            if (num1.digits[i] != num2.digits[i]) return false;
        }

        return true;
    }

    bool isLessThan(const LongNumber& num1, const LongNumber& num2) {
        if (num1.isZeroValue()) {
            if (num2.isZeroValue()) {
                return false;
            }
            return !num2.isNegative;
        } else if (num2.isZeroValue()) {
            return num1.isNegative;
        }

        if (num1.isNegative && num2.isNegative) {
            return isLessThan(num2.negate(), num1.negate());
        }

        if (num1.isNegative != num2.isNegative) {
            return num1.isNegative;
        }

        if (num1.getMagnitude() != num2.getMagnitude()) return num1.getMagnitude() < num2.getMagnitude();

        int i = num1.digits.size() - 1;
        int j = num2.digits.size() - 1;
        while (i >= 0 && j >= 0) {
            if (num1.digits[i] != num2.digits[j]) {
                return num1.digits[i] < num2.digits[j];
            }
            --i;
            --j;
        }

        return num1.decimalPoint < num2.decimalPoint;
    }

    bool isGreaterThan(const LongNumber& num1, const LongNumber& num2) {
        return isLessThan(num2, num1);
    }

    bool isLessOrEqual(const LongNumber& num1, const LongNumber& num2) {
        return isLessThan(num1, num2) || areEqual(num1, num2);
    }

    bool isGreaterOrEqual(const LongNumber& num1, const LongNumber& num2) {
        return isGreaterThan(num1, num2) || areEqual(num1, num2);
    }

    bool areNotEqual(const LongNumber& num1, const LongNumber& num2) {
        return !areEqual(num1, num2);
    }

    LongNumber add(const LongNumber& num1, const LongNumber& num2) {
        if (num1.isNegative != num2.isNegative) {
            if (num2.isNegative) return subtract(num1, num2.negate());
            return subtract(num2, num1.negate());
        }

        LongNumber result;
        int precisionDiff = static_cast<int>(num1.decimalPoint - num2.decimalPoint);
        const LongNumber& a = precisionDiff > 0 ? num1 : num2;
        const LongNumber& b = precisionDiff > 0 ? num2 : num1;
        precisionDiff = std::abs(precisionDiff);

        short carry = 0;
        for (int i = 0; i < b.digits.size() || carry != 0; ++i) {
            int j = i + precisionDiff;

            if (j == a.digits.size()) {
                if (i < b.digits.size()) {
                    result.digits.push_back(b.digits[i] + carry);
                } else {
                    result.digits.push_back(carry);
                }
            } else {
                if (i < b.digits.size()) {
                    result.digits[j] += b.digits[i] + carry;
                } else {
                    result.digits[j] += carry;
                }
            }

            if (result.digits[j] >= 10) {
                result.digits[j] -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
        }

        result.trimLeadingZeros();
        return result;
    }

    LongNumber subtract(const LongNumber& num1, const LongNumber& num2) {
        if (num2.isNegative) return add(num1, num2.negate());
        else if (num1.isNegative) return add(num1.negate(), num2).negate();
        else if (isLessThan(num1, num2)) return subtract(num2, num1).negate();

        LongNumber result = num1;
        int precisionDiff = static_cast<int>(num1.decimalPoint - num2.decimalPoint);

        if (precisionDiff > 0) {
            result.digits.insert(result.digits.begin(), precisionDiff, 0);
        } else if (precisionDiff != 0) {
            num1.digits.insert(num1.digits.begin(), -precisionDiff, 0);
            num1.decimalPoint -= precisionDiff;
        }

        short carry = 0;
        for (int i = 0; i < result.digits.size() || carry != 0; ++i) {
            result.digits[i] -= carry;
            if (i < num2.digits.size()) {
                result.digits[i] -= num2.digits[i];
            }

            if (result.digits[i] < 0) {
                result.digits[i] += 10;
                carry = 1;
            } else {
                carry = 0;
            }
        }

        result.trimLeadingZeros();
        return result;
    }

    LongNumber multiply(const LongNumber& num1, const LongNumber& num2) {
        if (num1.isZeroValue() || num2.isZeroValue()) return LongNumber();

        LongNumber result;
        result.isNegative = (num1.isNegative != num2.isNegative);
        result.decimalPoint = num1.decimalPoint + num2.decimalPoint;

        short carry;
        for (int i = 0; i < num1.digits.size(); ++i) {
            carry = 0;
            for (int j = 0; j < num2.digits.size() || carry != 0; ++j) {
                if (i + j >= result.digits.size()) {
                    result.digits.push_back(0);
                }
                short n = result.digits[i + j] + num1.digits[i] * (j < num2.digits.size() ? num2.digits[j] : 0) + carry;

                result.digits[i + j] = n % 10;
                carry = n / 10;
            }
        }

        result.trimLeadingZeros();
        return result;
    }

    LongNumber divide(const LongNumber& num1, const LongNumber& num2) {
        if (num2.isZeroValue()) {
            throw std::overflow_error("Division by zero");
        }

        LongNumber a = num1;
        LongNumber b = num2;

        LongNumber result;
        result.digits.pop_back();

        result.isNegative = (a.isNegative != b.isNegative);
        a.isNegative = false;
        b.isNegative = false;

        int magnitude = a.getMagnitude() - b.getMagnitude() + 1;

        while (b.getMagnitude() < a.getMagnitude()) {
            b = multiply(b, LongNumber(10));
        }

        int precision = std::max(a.precision, b.precision);

        LongNumber bd;
        short digit;
        int size = magnitude > 0 ? precision + magnitude : precision + 1;
        while (!a.isZeroValue() && result.digits.size() <= size) {
            while (isLessThan(a, b)) {
                result.digits.insert(result.digits.begin(), 0);
                a = multiply(a, LongNumber(10));
            }

            digit = 1;
            bd = b;
            while (isLessOrEqual(add(bd, b), a) && digit < 9) {
                bd = add(bd, b);
                digit++;
            }

            result.digits.insert(result.digits.begin(), digit);
            a = subtract(a, bd);
            a = multiply(a, LongNumber(10));
        }

        if (magnitude <= 0) {
            result.decimalPoint = result.digits.size() - 1;
        } else {
            result.digits.insert(result.digits.begin(), magnitude, 0);
            result.decimalPoint = result.digits.size() - magnitude;
        }

        result.precision = precision;

        result.trimLeadingZeros();
        return result;
    }

    LongNumber& LongNumber::addAssign(const LongNumber& other) {
        return *this = add(*this, other);
    }

    LongNumber& LongNumber::subtractAssign(const LongNumber& other) {
        return *this = subtract(*this, other);
    }

    LongNumber& LongNumber::multiplyAssign(const LongNumber& other) {
        return *this = multiply(*this, other);
    }

    LongNumber& LongNumber::divideAssign(const LongNumber& other) {
        return *this = divide(*this, other);
    }
}

LongMath::LongNumber createFromUnsignedLongLong(unsigned long long value) {
    return LongMath::LongNumber(static_cast<int>(value));
}

LongMath::LongNumber createFromLongDouble(long double value) {
    return LongMath::LongNumber(std::to_string(value));
}