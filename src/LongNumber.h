#ifndef LONGNUMBER_H
#define LONGNUMBER_H

#include <deque>
#include <vector>
#include <string>

namespace LongNumber {
	class LongMath {
	private:
		const int PRECISION = 333;
		std::vector<bool> integer_part;
		std::vector<bool> fractional_part;
		unsigned precision;
		bool sign;

		void normalize();
		bool is_zero() const;
		void add_bit(bool bit);
		void shift_right(int n);
		void shift_left(int n);

	public:
		LongMath();
		LongMath(int prec);
		LongMath(std::string value, int prec);
		LongMath(const LongMath& other);

		LongMath& operator=(const LongMath& other);

		~LongMath();

		LongMath operator+(const LongMath& other);
		LongMath operator-(const LongMath& other);
		LongMath operator*(const LongMath& other) const;
		LongMath operator/(const LongMath& other) const;

		LongMath& operator+=(const LongMath& other);
		LongMath& operator-=(const LongMath& other);
		LongMath& operator*=(const LongMath& other);
		LongMath& operator/=(const LongMath& other);

		bool operator==(const LongMath& other)const;
		bool operator!=(const LongMath& other)const;
		bool operator<=(const LongMath& other)const;
		bool operator>=(const LongMath& other)const;
		bool operator<(const LongMath& other)const;
		bool operator>(const LongMath& other)const;

		LongMath max(const LongMath& left, const LongMath& right);
		LongMath min(const LongMath& left, const LongMath& right);

		void from_string(std::string value);

		void set_precision(int prec);
		int get_precision() const;

		std::vector<bool> get_integer_part() const;
		std::vector<bool> get_fractional_part() const;
		bool get_sign() const;

		std::string to_decimal() const;
		std::string to_decimal_integer() const;
		static LongMath calculate_pi(int precision);

		void print_result() const;

		LongMath operator<<(int n) const;
		LongMath operator>>(int n) const;
		LongMath& operator<<=(int n);
		LongMath& operator>>=(int n);

		LongMath operator-() const;

		bool equals_with_epsilon(const LongMath& other, const LongMath& epsilon) const;
		bool less_than_with_epsilon(const LongMath& other, const LongMath& epsilon) const;
		bool greater_than_with_epsilon(const LongMath& other, const LongMath& epsilon) const;

		static LongMath default_epsilon(int prec);
	};

	LongMath operator""_longnum(long double value);
	std::string to_string(double number, unsigned precision);
}

#endif