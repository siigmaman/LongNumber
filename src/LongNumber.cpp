#include "LongNumber.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cassert>
#include "Helpers.h"

namespace LongNumber {
	LongMath::LongMath() {
		sign = false;
		precision = 100;
		integer_part.push_back(0);
		fractional_part.resize(PRECISION, 0);
	}

	LongMath::LongMath(int prec) {
		sign = false;
		precision = prec;
		integer_part.push_back(0);
		fractional_part.resize(PRECISION, 0);
	}

	LongMath::LongMath(std::string value, int prec) {
		sign = false;
		precision = prec;
		integer_part.clear();
		integer_part.push_back(0);
		fractional_part.resize(PRECISION, 0);
		from_string(value);
	}

	LongMath::LongMath(const LongMath& other) {
		sign = other.sign;
		precision = other.precision;
		integer_part = other.integer_part;
		fractional_part = other.fractional_part;
	}

	LongMath& LongMath::operator=(const LongMath& other) {
		if (this != &other) {
			sign = other.sign;
			precision = other.precision;
			integer_part = other.integer_part;
			fractional_part = other.fractional_part;
		}
		return *this;
	}

	LongMath::~LongMath() {}

	void LongMath::normalize() {
		while (!integer_part.empty() && integer_part.back() == false) {
			integer_part.pop_back();
		}
		if (integer_part.empty()) {
			sign = false;
			integer_part.push_back(0);
		}
	}

	void LongMath::add_bit(bool bit) {
		integer_part.push_back(bit);
	}

	bool LongMath::is_zero() const {
		for (bool bit : integer_part) {
			if (bit) return false;
		}
		for (bool bit : fractional_part) {
			if (bit) return false;
		}
		return true;
	}

	inline LongMath min(const LongMath &left, const LongMath &right) {
		return left < right ? left : right;
	}

	inline LongMath max(const LongMath &left, const LongMath &right) {
		return left > right ? left : right;
	}

	void LongMath::shift_left(int n) {
		if (n <= 0) {
			return;
		}
		
		integer_part.resize(integer_part.size() + n, false);
		
		for (int i = 0; i < n && !fractional_part.empty(); ++i) {
			integer_part.insert(integer_part.begin(), fractional_part[0]);
			fractional_part.erase(fractional_part.begin());
		}
		
		fractional_part.resize(PRECISION, false);
		normalize();
	}

	void LongMath::shift_right(int n) {
		if (n <= 0) {
			return;
		}
		for (int i = 0; i < n; ++i) {
			if (!integer_part.empty()) {
				fractional_part.insert(fractional_part.begin(), integer_part[0]);
				integer_part.erase(integer_part.begin());
			} else {
				fractional_part.insert(fractional_part.begin(), false);
			}
		}
		if (integer_part.empty()) {
			integer_part.push_back(0);
		}
		if (fractional_part.size() > PRECISION) {
			fractional_part.resize(PRECISION);
		}
		normalize();
	}

	void LongMath::from_string(std::string value) {
		if (value.empty()) {
			return;
		}

		if (value[0] == '-') {
			sign = true;
			value.erase(value.begin());
		} else {
			sign = false;
		}

		integer_part.clear();
		std::fill(fractional_part.begin(), fractional_part.end(), 0);

		size_t decimal_point = value.find('.');
		std::string int_part, frac_part;
		
		if (decimal_point != std::string::npos) {
			int_part = value.substr(0, decimal_point);
			frac_part = value.substr(decimal_point + 1);
		} else {
			int_part = value;
			frac_part = "";
		}

		std::vector<bool> int_bits;
		while (!int_part.empty()) {
			int carry = 0;
			std::string new_int;

			for (char digit : int_part) {
				int current = carry * 10 + (digit - '0');
				if (!new_int.empty() || current / 2 != 0) {
					new_int += (current / 2) + '0';
				}
				carry = current % 2;
			}

			int_bits.push_back(carry);
			int_part = new_int;
		}

		integer_part.insert(integer_part.end(), int_bits.begin(), int_bits.end());

		if (!frac_part.empty()) {
			std::string current_frac = "0." + frac_part;
			for (unsigned i = 0; i < PRECISION; ++i) {
				double val = std::stod(current_frac) * 2.0;
				fractional_part[i] = val >= 1.0;
				if (val >= 1.0) {
					val -= 1.0;
				}
				current_frac = to_string(val, precision);
			}
		}
		
	}
	
	std::string to_string(double number, unsigned precision) {
		std::ostringstream stream;
		stream.precision(precision);
		stream << std::fixed << number;
		return stream.str();
	}

	LongMath LongMath::operator+(const LongMath& other) {
		if (sign != other.sign) {
			if (sign) {
				return LongMath(other) - *this;
			}
			else {
				return *this - other;
			}
		}
		LongMath result(std::max(precision, other.precision));
		bool carry = false;
		for (int i = fractional_part.size() - 1; i >= 0; --i) {
			bool sum = fractional_part[i] ^ other.fractional_part[i] ^ carry;
			carry = (fractional_part[i] + other.fractional_part[i] + carry) > 1;
			result.fractional_part[i] = sum;
		}

		size_t max_size = std::max(integer_part.size(), other.integer_part.size());
		result.integer_part.resize(max_size + 2, false);

		for (size_t i = 0; i < max_size || carry; ++i) {
			bool bit1 = i < integer_part.size() ? integer_part[i] : false;
			bool bit2 = i < other.integer_part.size() ? other.integer_part[i] : false;
			bool sum = bit1 ^ bit2 ^ carry;
			carry = (bit1 + bit2 + carry) > 1;
			if (i >= result.integer_part.size()) {
				result.integer_part.push_back(sum);
			} else {
				result.integer_part[i] = sum;
			}
		}
		
		result.sign = sign;
		result.normalize();
		return result;
	}

	LongMath LongMath::operator-(const LongMath& other) {
		if (sign != other.sign) {
			LongMath temp = other;
			temp.sign = !temp.sign;
			return *this + temp;
		}
		bool this_larger = false;
		if (integer_part.size() != other.integer_part.size()) {
			this_larger = integer_part.size() > other.integer_part.size();
		} else {
			for (int i = integer_part.size() - 1; i >= 0; i--) {
				if (integer_part[i] != other.integer_part[i]) {
					this_larger = integer_part[i] > other.integer_part[i];
					break;
				}
			}
			if (integer_part == other.integer_part) {
				for (size_t i = 0; i < fractional_part.size(); i++) {
					if (fractional_part[i] != other.fractional_part[i]) {
						this_larger = fractional_part[i] > other.fractional_part[i];
						break;
					}
				}
			}
		}
		if (!this_larger) {
			LongMath result = LongMath(other) - *this;
			result.sign = !result.sign;
			return result;
		}
		LongMath result(std::max(precision, other.precision));
		bool borrow = false;
		for (size_t i = fractional_part.size(); i > 0; --i) {
			bool bit1 = fractional_part[i-1];
			bool bit2 = other.fractional_part[i-1];
			if (borrow) {
				if (bit1) {
					bit1 = false;
					borrow = false;
				} else {
					bit1 = true;
				}
			}
			
			if (bit1 >= bit2) {
				result.fractional_part[i-1] = bit1 - bit2;
			} else {
				result.fractional_part[i-1] = (bit1 + 2) - bit2;
				borrow = true;
			}
		}
		result.integer_part.clear();
		for (size_t i = 0; i < integer_part.size(); ++i) {
			bool bit1 = i < integer_part.size() ? integer_part[i] : false;
			bool bit2 = i < other.integer_part.size() ? other.integer_part[i] : false;
			if (borrow) {
				if (bit1) {
					bit1 = false;
					borrow = false;
				} else {
					bit1 = true;
				}
			}
			if (bit1 >= bit2) {
				result.integer_part.push_back(bit1 - bit2);
			} else {
				result.integer_part.push_back((bit1 + 2) - bit2);
				borrow = true;
			}
		}
		result.sign = sign;
		result.normalize();
		return result;
	}

	LongMath LongMath::operator-() const {
		LongMath other = *this;
		other.sign = !other.sign;
		return other;
	}

	LongMath LongMath::operator*(const LongMath& other) const {
		if (this->is_zero() || other.is_zero()) {
			return LongMath("0", std::max(precision, other.precision));
		}
		
		LongMath result(std::max(precision, other.precision));
		LongMath multiplier = other;
		multiplier.sign = false;
		
		size_t expected_size = (integer_part.size() + other.integer_part.size()) * 2;
		result.integer_part.resize(expected_size, false);
		
		for (size_t i = 0; i < fractional_part.size() + integer_part.size(); i++) {
			bool bit = (i < fractional_part.size()) ? 
					   fractional_part[i] : 
					   integer_part[i - fractional_part.size()];
			
			if (bit) {
				LongMath temp = multiplier;
				int shift = (i < fractional_part.size()) ? 
						   (i + 1) : 
						   -(i - fractional_part.size());
						   
				if (shift > 0) temp >>= shift;
				else temp <<= -shift;
				
				result += temp;
			}
		}
		
		result.sign = sign ^ other.sign;
		result.normalize();
		return result;
	}

	LongMath LongMath::operator/(const LongMath& other) const {
		if (other.is_zero()) {
			throw std::invalid_argument("Деление на ноль");
		}
		bool resultSign = sign != other.sign;

		LongMath a = *this;
		LongMath b = other;
		a.sign = false;
		b.sign = false;

		if (a.is_zero()) {
			return LongMath("0", std::max(precision, other.precision));
		}
		if (a == b) {
			LongMath result("1", std::max(precision, other.precision));
			result.sign = resultSign;
			return result;
		}

		unsigned int maxPrecision = std::max(precision, other.precision);

		if (a < b) {
			LongMath scaled_a = a;
			scaled_a.shift_left(PRECISION);

			LongMath l("0", maxPrecision);
			LongMath r("1", maxPrecision);
			r.shift_left(PRECISION);
			
			for (int i = 0; i < PRECISION * 2; i++) {
				LongMath mid = l + r;
				mid.shift_right(1);
				
				LongMath product = mid * b;
				
				if (product <= scaled_a) {
					l = mid;
				} else {
					r = mid;
				}
			}
			l.shift_right(PRECISION);
			l.sign = resultSign;
			return l;
		}
		LongMath l("0", maxPrecision);
		LongMath r = a;
		r.shift_left(1);
		for (int i = 0; i < PRECISION * 2; i++) {
			LongMath mid = l + r;
			mid.shift_right(1);
			LongMath product = mid * b;
			if (product <= a) {
				l = mid;
			} else {
				r = mid;
			}
		}
		
		l.sign = resultSign;
		return l;
	}

	LongMath& LongMath::operator+=(const LongMath& other) {
		*this = *this + other;
		return *this;
	}

	LongMath& LongMath::operator-=(const LongMath& other) {
		*this = *this - other;
		return *this;
	}

	LongMath& LongMath::operator*=(const LongMath& other) {
		*this = *this * other;
		return *this;
	}

	LongMath& LongMath::operator/=(const LongMath& other) {
		*this = *this / other;
		return *this;
	}

	bool LongMath::operator==(const LongMath& other) const {
		return integer_part == other.integer_part && 
			   fractional_part == other.fractional_part &&
			   sign == other.sign;
	}

	bool LongMath::operator!=(const LongMath& other) const {
		return !(*this == other);
	}

	bool LongMath::operator<(const LongMath& other) const {
		if (sign != other.sign) {
			return sign;
		}
		bool invert = sign;
		if (integer_part.size() != other.integer_part.size()) {
			bool size_less = (integer_part.size() < other.integer_part.size());
			return invert ? !size_less : size_less;
		}

		for (int i = integer_part.size() - 1; i >= 0; --i) {
			if (integer_part[i] != other.integer_part[i]) {
				bool bit_less = integer_part[i] < other.integer_part[i];
				return invert ? !bit_less : bit_less;
			}
		}

		for (size_t i = 0; i < fractional_part.size(); ++i) {
			if (fractional_part[i] != other.fractional_part[i]) {
				bool frac_less = fractional_part[i] < other.fractional_part[i];
				return invert ? !frac_less : frac_less;
			}
		}

		return false;
	}

	bool LongMath::operator>(const LongMath& other) const {
		return !(*this < other) && !(*this == other);
	}

	bool LongMath::operator>=(const LongMath& other) const {
		return (*this > other) || (*this == other);
	}

	bool LongMath::operator<=(const LongMath& other) const {
		return (*this < other) || (*this == other);
	}

	void LongMath::set_precision(int prec) {
		precision = prec;
	}

	int LongMath::get_precision() const {
		return precision;
	}

	std::string LongMath::to_decimal_integer() const {
		std::string result = "0";
		for (int i = integer_part.size() - 1; i >= 0; i--) {
			result = MultiplyStringByTwo(result);
			if (integer_part[i]) {
				result = IncrementString(result);
			}
		}
		if (sign && result != "0") {
			result = "-" + result;
		}
		return result;
	}

	std::string LongMath::to_decimal() const {
		std::stringstream ss;
		ss << to_decimal_integer();	
		bool is_null = true;
		for (int i = 0; i < PRECISION; i++) {
			if (this->fractional_part[i] != 0) {
				is_null = false;
				break;
			}
		}
		if (is_null) {
			return ss.str();
		}
		ss << ".";
		LongMath current = *this;
		current.sign = false;
		current.integer_part.clear();
		std::string fraction_str = "";
		const int MAX_DECIMAL_DIGITS = 100;
		for (int i = 0; i < MAX_DECIMAL_DIGITS && !current.is_zero(); i++) {
			current = current * LongMath("10", precision);
			std::string digit = current.to_decimal_integer();
			fraction_str += digit;
			current.integer_part.clear();
		}
		if (fraction_str.empty()) {
			fraction_str = "0";
		}
		ss << fraction_str;
		return ss.str();
	}

	LongMath LongMath::calculate_pi(int precision) {
		LongMath one("1.0", precision);
		LongMath sum("0.0", precision); 
		LongMath term("0.0", precision);
		int k = 0; 

		std::string s = to_string(8.0 * k, precision);

		LongMath kTerm(s, precision);
		LongMath denominator1 = kTerm + one;
		LongMath denominator2 = kTerm + LongMath("4.0", precision);
		LongMath denominator3 = kTerm + LongMath("5.0", precision);
		LongMath denominator4 = kTerm + LongMath("6.0", precision);

		term = LongMath("4.0", precision) / denominator1 -
			LongMath("2.0", precision) / denominator2 -
				LongMath("1.0", precision) / denominator3 -
					LongMath("1.0", precision) / denominator4;

		sum = sum + term;

		return sum;
	}

	void LongMath::print_result() const {
		for (bool bit : integer_part) {
			std::cout << bit;
		}
		std::cout << std::endl;
	}

	LongMath operator""_longnum(long double value) {
		double num = static_cast<double>(value);
		std::string s = to_string(num, 10);
		return LongMath(s, 10);
	}

	std::vector<bool> LongMath::get_integer_part() const {
		return integer_part;
	}

	std::vector<bool> LongMath::get_fractional_part() const {
		return fractional_part;
	}	

	bool LongMath::get_sign() const {
		return sign;
	}

	LongMath LongMath::operator<<(int n) const {
		LongMath result(*this);
		result.shift_left(n);
		return result;
	}

	LongMath LongMath::operator>>(int n) const {
		LongMath result(*this);
		result.shift_right(n);
		return result;
	}

	LongMath& LongMath::operator<<=(int n) {
		shift_left(n);
		return *this;
	}

	LongMath& LongMath::operator>>=(int n) {
		shift_right(n);
		return *this;
	}

	bool LongMath::equals_with_epsilon(const LongMath& other, const LongMath& epsilon) const {
		if (*this == other) return true;
		
		LongMath diff = LongMath(*this) - other;
		if (diff.sign) diff = -diff;
		
		return diff < epsilon;
	}

	bool LongMath::less_than_with_epsilon(const LongMath& other, const LongMath& epsilon) const {
		if (equals_with_epsilon(other, epsilon)) return false;
		return *this < other;
	}

	bool LongMath::greater_than_with_epsilon(const LongMath& other, const LongMath& epsilon) const {
		if (equals_with_epsilon(other, epsilon)) return false;
		return *this > other;
	}

	LongMath LongMath::default_epsilon(int prec) {
		std::string epsilon_str = "0.";
		for (int i = 0; i < prec - 1; i++) {
			epsilon_str += "0";
		}
		epsilon_str += "1";
		
		return LongMath(epsilon_str, prec);
	}
}