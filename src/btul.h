/* The MIT License (MIT)

Copyright (c) 2014 Isaac Supeene

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef BTUL_H
#define BTUL_H

#include <utility>
#include <cmath>
#include <string>
#include <sstream>


#define BASE_QUANTITIES_DECLARATION	\
	int Length,			\
	int Mass,			\
	int Time,			\
	int Current,			\
	int Temperature,		\
	int Amount,			\
	int Luminosity

#define BASE_QUANTITIES	\
	Length,		\
	Mass,		\
	Time,		\
	Current,	\
	Temperature,	\
	Amount,		\
	Luminosity

#define BASE_QUANTITIES_DECLARATION_N(N)	\
	int Length##N,				\
	int Mass##N,				\
	int Time##N,				\
	int Current##N,				\
	int Temperature##N,			\
	int Amount##N,				\
	int Luminosity##N

#define BASE_QUANTITIES_DECLARATION_1 BASE_QUANTITIES_DECLARATION_N(1)

#define BASE_QUANTITIES_DECLARATION_2 BASE_QUANTITIES_DECLARATION_N(2)

#define BASE_QUANTITIES_N(N)	\
	Length##N,		\
	Mass##N,		\
	Time##N,		\
	Current##N,		\
	Temperature##N,		\
	Amount##N,		\
	Luminosity##N

#define BASE_QUANTITIES_1 BASE_QUANTITIES_N(1)
#define BASE_QUANTITIES_2 BASE_QUANTITIES_N(2)

#define BASE_QUANTITIES_OP(OP)		\
	Length1 OP Length2,		\
	Mass1 OP Mass2,			\
	Time1 OP Time2,			\
	Current1 OP Current2,		\
	Temperature1 OP Temperature2,	\
	Amount1 OP Amount2,		\
	Luminosity1 OP Luminosity2

#define BASE_QUANTITIES_ADD BASE_QUANTITIES_OP(+)
#define BASE_QUANTITIES_SUB BASE_QUANTITIES_OP(-)

#define BASE_QUANTITIES_N_MUL(N, VALUE)	\
	Length##N * VALUE,		\
	Mass##N * VALUE,		\
	Time##N * VALUE,		\
	Current##N * VALUE,		\
	Temperature##N * VALUE,		\
	Amount##N * VALUE,		\
	Luminosity##N * VALUE

#define BASE_QUANTITIES_1_MUL(VALUE) BASE_QUANTITIES_N_MUL(1, VALUE)

namespace detail {
	const char* super(char c) {
		switch (c) {
			case '(': return "\xe2\x81\xbd";
			case ')': return "\xe2\x81\xbe";
			case '+': return "\xe2\x81\xba";
			case '-': return "\xe2\x81\xbb";
			case '0': return "\xe2\x81\xb0";
			case '1': return "\xc2\xb9";
			case '2': return "\xc2\xb2";
			case '3': return "\xc2\xb3";
			case '4': return "\xe2\x81\xb4";
			case '5': return "\xe2\x81\xb5";
			case '6': return "\xe2\x81\xb6";
			case '7': return "\xe2\x81\xb7";
			case '8': return "\xe2\x81\xb8";
			case '9': return "\xe2\x81\xb9";
			default:  return "";
		}
	}

	std::string formatUnits(const char* units) {
		std::ostringstream result;
		for (const char* c = units; *c != '\0'; ++c) {
			switch (*c) {
				case '*': result << "·";	break;
				case '[':
					++c;
					if (*c == 'n') {
						result << super('-');
					}
					while (*(++c) != ']') {
						result << super(*c);
					}
					break;
				default: result << *c;		break;
			}
		}
		return result.str();
	}

#ifdef MATHEMATICAL_SPACE
	const char* SPACE = "\xe2\x81\x9f";
#else
	const char* SPACE = " ";
#endif
}


template <BASE_QUANTITIES_DECLARATION>
class DefaultQuantityFormat {
	static void print_power(std::ostringstream& stream, int i) {
		std::ostringstream power_stream;
		power_stream << i;
		std::string str = power_stream.str();
		for (char c : str) {
			stream << detail::super(c);
		}
	}

	static inline void print_positive(std::ostringstream& stream,
					  int power,
					  const char* unit,
					  bool& first)
	{
		if (power > 0) {
			if (!first) {
				stream << "·";
			}
			stream << unit;
			if (power > 1) {
				print_power(stream, power);
			}
			first = false;
		}
	}

	static inline bool print_positives(std::ostringstream& stream) {
		bool first = true;

		print_positive(stream, Length, "m", first);
		print_positive(stream, Mass, "kg", first);
		print_positive(stream, Time, "s", first);
		print_positive(stream, Current, "A", first);
		print_positive(stream, Temperature, "K", first);
		print_positive(stream, Amount, "mol", first);
		print_positive(stream, Luminosity, "cd", first);
		
		return !first;
	}

	static inline void print_negative(std::ostringstream& stream,
					  int power,
					  const char* unit,
					  bool& first)
	{
		if (power < 0) {
			if (!first) {
				stream << "·";
			}
			stream << unit;
			print_power(stream, power);
			first = false;
		}
	}

	static inline void print_negatives(std::ostringstream& stream) {
		bool first = true;

		print_negative(stream, Length, "m", first);
		print_negative(stream, Mass, "kg", first);
		print_negative(stream, Time, "s", first);
		print_negative(stream, Current, "A", first);
		print_negative(stream, Temperature, "K", first);
		print_negative(stream, Amount, "mol", first);
		print_negative(stream, Luminosity, "cd", first);
	}

	static inline void print_negatives_as_positives(std::ostringstream& stream) {
		bool first = true;

		print_positive(stream, -Length, "m", first);
		print_positive(stream, -Mass, "kg", first);
		print_positive(stream, -Time, "s", first);
		print_positive(stream, -Current, "A", first);
		print_positive(stream, -Temperature, "K", first);
		print_positive(stream, -Amount, "mole", first);
		print_positive(stream, Luminosity, "cd", first);
	}
public:
	template <class Number>
	static std::string Format(Number value) {
		std::ostringstream result;
		result << value << ' ';

		bool positivesExist = print_positives(result);
		if (positivesExist) {
			int negatives = 0;
			for (int i : {BASE_QUANTITIES}) {
				if (i < 0) {
					++negatives;
				}
			}
			if (negatives == 1) {
				result << '/';
				print_negatives_as_positives(result);
			}
			else if (negatives > 1) {
				result << "/(";
				print_negatives_as_positives(result);
				result << ')';
			}
		}
		else {
			print_negatives(result);
		}
		return result.str();
	}
};


#define OP_RESULT_TYPE(T1, OP, T2) decltype(std::declval<T1>() OP std::declval<T2>())
#define POW_TYPE(T1, T2) decltype(std::pow(std::declval<T1>(), std::declval<T2>()))

template <BASE_QUANTITIES_DECLARATION_1,
	  class Number = long double,
	  class Format = DefaultQuantityFormat<BASE_QUANTITIES_1>>
class Quantity {
public:
	constexpr Quantity() {}
	explicit constexpr Quantity(Number value)
		: value(value)
	{}

	template <class T, class F>
	constexpr Quantity(Quantity<BASE_QUANTITIES_1, T, F> other)
		: value(other.Value())
	{}

	template <class T, class F>
	constexpr Quantity& operator =(Quantity<BASE_QUANTITIES_1, T, F> other) {
		this->value = other.Value();
		return *this;
	}

	#define DECLARE_POWER(N)						\
	constexpr Quantity<BASE_QUANTITIES_1_MUL(N), Number, Format> p##N() {	\
		return Quantity<BASE_QUANTITIES_1_MUL(N), Number, Format>(	\
			std::pow(value, N)					\
		);								\
	}									\
										\
	constexpr Quantity<BASE_QUANTITIES_1_MUL(-N), Number, Format> n##N() {	\
		return Quantity<BASE_QUANTITIES_1_MUL(-N), Number, Format>(	\
			std::pow(value, -N)					\
		);								\
	}

	DECLARE_POWER(0);
	DECLARE_POWER(1);
	DECLARE_POWER(2);
	DECLARE_POWER(3);
	DECLARE_POWER(4);
	DECLARE_POWER(5);
	DECLARE_POWER(6);
	DECLARE_POWER(7);
	DECLARE_POWER(8);
	DECLARE_POWER(9);

	#undef DECLARE_POWER

	template <class NewFormat>
	constexpr Quantity<BASE_QUANTITIES_1, Number, NewFormat> withFormat() const {
		return Quantity<BASE_QUANTITIES_1, Number, NewFormat>(value);
	}

	template <class T1, class T2, class F>
	constexpr bool Within(T1 epsilon,
			      const Quantity<BASE_QUANTITIES_1, T2, F>& other) const
	{
		return (this->Value() == other.Value()) ||
		       (this->Value() < other.Value() &&
			this->Value() + epsilon >= other.Value()) ||
		       (other.Value() < this->Value() &&
			other.Value() + epsilon >= this->Value());
	}

	constexpr Number Value() const {
		return value;
	}

	static constexpr int length = Length1;
	static constexpr int mass = Mass1;
	static constexpr int time = Time1;
	static constexpr int temperature = Temperature1;
	static constexpr int current = Current1;
	static constexpr int amount = Amount1;
	static constexpr int luminosity = Luminosity1;

	typedef Number type;
	typedef Format format;

protected:
	Number value;

private:
	template <BASE_QUANTITIES_DECLARATION,
		  class T1, class F1,
		  class T2, class F2>
	friend constexpr Quantity<BASE_QUANTITIES, T1, F1>& operator +=(
		Quantity<BASE_QUANTITIES, T1, F1>&,
		const Quantity<BASE_QUANTITIES, T2, F2>&
	);

	template <BASE_QUANTITIES_DECLARATION,
		  class T1, class F1,
		  class T2, class F2>
	friend constexpr Quantity<BASE_QUANTITIES, T1, F1>& operator -=(
		Quantity<BASE_QUANTITIES, T1, F1>&,
		const Quantity<BASE_QUANTITIES, T2, F2>&
	);

	template <BASE_QUANTITIES_DECLARATION, class T1, class F, class T2>
	friend constexpr Quantity<BASE_QUANTITIES, T1, F>& operator *=(
		Quantity<BASE_QUANTITIES, T1, F>&,
		const T2&
	);

	template <BASE_QUANTITIES_DECLARATION, class T1, class F, class T2>
	friend constexpr Quantity<BASE_QUANTITIES, T1, F>& operator /=(
		Quantity<BASE_QUANTITIES, T1, F>&,
		const T2&
	);

	template <BASE_QUANTITIES_DECLARATION, class T1, class F, class T2>
	friend constexpr Quantity<BASE_QUANTITIES, T1, F>& operator %=(
		Quantity<BASE_QUANTITIES, T1, F>&,
		const T2&
	);

	template <BASE_QUANTITIES_DECLARATION, class T, class F>
	friend constexpr Quantity<BASE_QUANTITIES, T, F>& operator ++(
		Quantity<BASE_QUANTITIES, T, F>&
	);

	template <BASE_QUANTITIES_DECLARATION, class T, class F>
	friend constexpr Quantity<BASE_QUANTITIES, T, F>& operator --(
		Quantity<BASE_QUANTITIES, T, F>&
	);

	template <BASE_QUANTITIES_DECLARATION, class T, class F>
	friend constexpr Quantity<BASE_QUANTITIES, T, F> operator ++(
		Quantity<BASE_QUANTITIES, T, F>&,
		int
	);

	template <BASE_QUANTITIES_DECLARATION, class T, class F>
	friend constexpr Quantity<BASE_QUANTITIES, T, F> operator --(
		Quantity<BASE_QUANTITIES, T, F>&,
		int
	);
};

// We use some cheap tricks with the comma operator here, since C++11
// only supports single statements as constexpr function bodies.

#define DECLARE_ADDITIVE_QUANTITY_OPERATOR(OP)					\
template <BASE_QUANTITIES_DECLARATION,						\
	  class T1, class F1,							\
	  class T2, class F2>							\
constexpr Quantity<BASE_QUANTITIES, OP_RESULT_TYPE(T1, OP, T2)>			\
operator OP(const Quantity<BASE_QUANTITIES, T1, F1>& x,				\
	    const Quantity<BASE_QUANTITIES, T2, F2>& y) 			\
{										\
	return Quantity<BASE_QUANTITIES, OP_RESULT_TYPE(T1, OP, T2)>(		\
		x.Value() OP y.Value()						\
	);									\
}										\
										\
template <BASE_QUANTITIES_DECLARATION, class T1, class F1, class T2, class F2>	\
constexpr Quantity<BASE_QUANTITIES, T1, F1>&					\
operator OP##=(Quantity<BASE_QUANTITIES, T1, F1>& x,				\
	       const Quantity<BASE_QUANTITIES, T2, F2>& y)			\
{										\
	return (x.value OP##= y.Value(), x);					\
}

DECLARE_ADDITIVE_QUANTITY_OPERATOR(+)
DECLARE_ADDITIVE_QUANTITY_OPERATOR(-)

#define DECLARE_MULTIPLICATIVE_QUANTITY_OPERATOR(OP, UNIT_OP)				\
template <BASE_QUANTITIES_DECLARATION_1, class T1, class F1,				\
	  BASE_QUANTITIES_DECLARATION_2, class T2, class F2>				\
constexpr Quantity<BASE_QUANTITIES_OP(UNIT_OP), OP_RESULT_TYPE(T1, OP, T2)>		\
operator OP(const Quantity<BASE_QUANTITIES_1, T1, F1>& x,				\
	    const Quantity<BASE_QUANTITIES_2, T2, F2>& y)				\
{											\
	return Quantity<BASE_QUANTITIES_OP(UNIT_OP), OP_RESULT_TYPE(T1, OP, T2)>(	\
		x.Value() OP y.Value()							\
	);										\
}											\
											\
template <BASE_QUANTITIES_DECLARATION, class T1, class F, class T2>			\
constexpr Quantity<BASE_QUANTITIES, OP_RESULT_TYPE(T1, OP, T2), F>			\
operator OP(const Quantity<BASE_QUANTITIES, T1, F>& x, const T2& y) {			\
	return Quantity<BASE_QUANTITIES, OP_RESULT_TYPE(T1, OP, T2), F>(		\
		x.Value() OP y								\
	);										\
}											\
											\
template <BASE_QUANTITIES_DECLARATION, class T1, class F, class T2>			\
constexpr Quantity<BASE_QUANTITIES, T1, F>&						\
operator OP##=(Quantity<BASE_QUANTITIES, T1, F>& x, const T2& y) {			\
	return (x.value OP##= y, x);							\
}

DECLARE_MULTIPLICATIVE_QUANTITY_OPERATOR(*, +)
DECLARE_MULTIPLICATIVE_QUANTITY_OPERATOR(/, -)

#define DECLARE_UNARY_QUANTITY_OPERATOR(OP)			\
template <BASE_QUANTITIES_DECLARATION, class T, class F>	\
constexpr Quantity<BASE_QUANTITIES, T, F>			\
operator OP(Quantity<BASE_QUANTITIES, T, F> x) {		\
	return Quantity<BASE_QUANTITIES, T, F>(OP x.Value());	\
}

DECLARE_UNARY_QUANTITY_OPERATOR(+)
DECLARE_UNARY_QUANTITY_OPERATOR(-)

#define DECLARE_PREFIX_QUANTITY_OPERATOR(OP)			\
template <BASE_QUANTITIES_DECLARATION, class T, class F>	\
constexpr Quantity<BASE_QUANTITIES, T, F>&			\
operator OP(Quantity<BASE_QUANTITIES, T, F>& x) {		\
	return (OP x.value, x);					\
}

DECLARE_PREFIX_QUANTITY_OPERATOR(++)
DECLARE_PREFIX_QUANTITY_OPERATOR(--)

#define DECLARE_POSTFIX_QUANTITY_OPERATOR(OP)			\
template <BASE_QUANTITIES_DECLARATION, class T, class F>	\
constexpr Quantity<BASE_QUANTITIES, T, F>			\
operator OP(Quantity<BASE_QUANTITIES, T, F>& x, int) {		\
	return Quantity<BASE_QUANTITIES, T, F>(x.value OP);	\
}

DECLARE_POSTFIX_QUANTITY_OPERATOR(++)
DECLARE_POSTFIX_QUANTITY_OPERATOR(--)

#define DECLARE_QUANTITY_COMPARISON_OPERATOR(OP)					\
template <BASE_QUANTITIES_DECLARATION, class T1, class F1, class T2, class F2>		\
constexpr bool										\
operator OP(Quantity<BASE_QUANTITIES, T1, F1> x, Quantity<BASE_QUANTITIES, T2, F2> y) {	\
	return x.Value() OP y.Value();							\
}

DECLARE_QUANTITY_COMPARISON_OPERATOR(==)
DECLARE_QUANTITY_COMPARISON_OPERATOR(!=)
DECLARE_QUANTITY_COMPARISON_OPERATOR(>)
DECLARE_QUANTITY_COMPARISON_OPERATOR(>=)
DECLARE_QUANTITY_COMPARISON_OPERATOR(<)
DECLARE_QUANTITY_COMPARISON_OPERATOR(<=)

template <BASE_QUANTITIES_DECLARATION, class T, class Format>
std::ostream& operator <<(std::ostream& stream,
			  const Quantity<BASE_QUANTITIES, T, Format>& quantity)
{
	return stream << Format::Format(quantity.Value());
}


#define DECLARE_MULTIPLIER(QUANTITY, UNIT, PREFIX, EXPONENT)			\
constexpr QUANTITY operator "" _##PREFIX##UNIT(long double value) {		\
	return UNIT * value * std::pow(10, EXPONENT);				\
}										\
constexpr QUANTITY operator "" _##PREFIX##UNIT(unsigned long long value) {	\
	return UNIT * value * std::pow(10, EXPONENT);				\
}										\
constexpr QUANTITY PREFIX##UNIT = 1.0_##PREFIX##UNIT

#define DECLARE_MULTIPLIERS(QUANTITY, UNIT)	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, T,  12);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, G,  9);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, M,  6);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, k,  3);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, h,  2);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, da, 1);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, d, -1);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, c, -2);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, m, -3);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, u, -6);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, n, -9);	\
DECLARE_MULTIPLIER(QUANTITY, UNIT, p, -12)

#define DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, PREFIX, EXPONENT, N)			\
constexpr decltype(UNIT.p##N())								\
operator "" _##PREFIX##UNIT##_p##N(long double value) {					\
	return UNIT.p##N() * std::pow(10, EXPONENT * N) * value;			\
}											\
											\
constexpr decltype(UNIT.p##N())								\
operator "" _##PREFIX##UNIT##_p##N(long long unsigned value) {				\
	return UNIT.p##N() * std::pow(10, EXPONENT * N) * value;			\
}											\
											\
constexpr decltype(UNIT.n##N())								\
operator "" _##PREFIX##UNIT##_n##N(long double value) {					\
	return UNIT.n##N() * std::pow(10, EXPONENT * -N) * value;			\
}											\
											\
constexpr decltype(UNIT.n##N())								\
operator "" _##PREFIX##UNIT##_n##N(long long unsigned value) {				\
	return UNIT.n##N() * std::pow(10, EXPONENT * -N) * value;			\
}											\
											\
constexpr decltype(UNIT.p##N()) PREFIX##UNIT##_p##N = 1.0_##PREFIX##UNIT##_p##N;	\
constexpr decltype(UNIT.n##N()) PREFIX##UNIT##_n##N = 1.0_##PREFIX##UNIT##_n##N

#define DECLARE_MULTIPLIER_POWERS(QUANTITY, UNIT, N)	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, T,  12, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, G,  9, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, M,  6, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, k,  3, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, h,  2, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, da, 1, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, d, -1, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, c, -2, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, m, -3, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, u, -6, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, n, -9, N);	\
DECLARE_MULTIPLIER_POWER(QUANTITY, UNIT, p, -12, N)


#define DECLARE_POWER(QUANTITY, UNIT, N)				\
constexpr decltype(UNIT.p##N())						\
operator "" _##UNIT##_p##N(long double value) {				\
	return UNIT.p##N() * value;					\
}									\
									\
constexpr decltype(UNIT.p##N())						\
operator "" _##UNIT##_p##N(long long unsigned value) {			\
	return UNIT.p##N() * value;					\
}									\
									\
constexpr decltype(UNIT.n##N())						\
operator "" _##UNIT##_n##N(long double value) {				\
	return UNIT.n##N() * value;					\
}									\
									\
constexpr decltype(UNIT.n##N())						\
operator "" _##UNIT##_n##N(long long unsigned value) {			\
	return UNIT.n##N() * value;					\
}									\
									\
constexpr decltype(UNIT.p##N())	UNIT##_p##N = 1.0_##UNIT##_p##N;	\
constexpr decltype(UNIT.n##N()) UNIT##_n##N = 1.0_##UNIT##_n##N;	\
									\
DECLARE_MULTIPLIER_POWERS(QUANTITY, UNIT, N)

#define DECLARE_POWERS(QUANTITY, UNIT)	\
DECLARE_POWER(QUANTITY, UNIT, 0);	\
DECLARE_POWER(QUANTITY, UNIT, 1);	\
DECLARE_POWER(QUANTITY, UNIT, 2);	\
DECLARE_POWER(QUANTITY, UNIT, 3);	\
DECLARE_POWER(QUANTITY, UNIT, 4);	\
DECLARE_POWER(QUANTITY, UNIT, 5);	\
DECLARE_POWER(QUANTITY, UNIT, 6);	\
DECLARE_POWER(QUANTITY, UNIT, 7);	\
DECLARE_POWER(QUANTITY, UNIT, 8);	\
DECLARE_POWER(QUANTITY, UNIT, 9)

#define DECLARE_QUANTITY_IMPL(QUANTITY, UNIT, MULTIPLIER)		\
constexpr QUANTITY operator "" _##UNIT(long double value) {		\
	return QUANTITY(value * MULTIPLIER);				\
}									\
									\
constexpr QUANTITY operator "" _##UNIT(unsigned long long value) {	\
	return QUANTITY(value * MULTIPLIER);				\
}									\
									\
constexpr QUANTITY UNIT = 1.0_##UNIT;					\
									\
DECLARE_MULTIPLIERS(QUANTITY, UNIT);					\
DECLARE_POWERS(QUANTITY, UNIT)

#define DECLARE_BASE_QUANTITY(QUANTITY, UNIT, MULTIPLIER)		\
DECLARE_QUANTITY_IMPL(QUANTITY, UNIT, 1.0 / MULTIPLIER);

#define DECLARE_DERIVED_QUANTITY(QUANTITY, UNIT, VALUE)				\
class QUANTITY##Format {							\
public:										\
	template <class Number>							\
	static std::string Format(Number value) {				\
		std::ostringstream result;					\
		result << value / (VALUE).Value() << detail::SPACE << #UNIT;	\
		return result.str();						\
	}									\
};										\
typedef decltype((VALUE).withFormat<QUANTITY##Format>()) QUANTITY;		\
DECLARE_QUANTITY_IMPL(QUANTITY, UNIT, (VALUE).Value());

#define DECLARE_DERIVED_QUANTITY_NO_SYMBOL(QUANTITY, VALUE)				\
class QUANTITY##Format {								\
public:											\
	template <class Number>								\
	static std::string Format(Number value) {					\
		std::ostringstream result;						\
		result << value << detail::SPACE << detail::formatUnits(#VALUE);	\
		return result.str();							\
	}										\
};											\
typedef decltype((VALUE).withFormat<QUANTITY##Format>()) QUANTITY;			\


typedef Quantity<1, 0, 0, 0, 0, 0, 0> Length;
DECLARE_BASE_QUANTITY(Length, m, 1.0L);

typedef Quantity<0, 1, 0, 0, 0, 0, 0> Mass;
DECLARE_BASE_QUANTITY(Mass, g, 1000.0L); // Chemists need not apply.

typedef Quantity<0, 0, 1, 0, 0, 0, 0> Time;
DECLARE_BASE_QUANTITY(Time, s, 1.0L);

typedef Quantity<0, 0, 0, 1, 0, 0, 0> Current;
DECLARE_BASE_QUANTITY(Current, A, 1.0L);

typedef Quantity<0, 0, 0, 0, 1, 0, 0> Temperature;
DECLARE_BASE_QUANTITY(Temperature, K, 1.0L);

typedef Quantity<0, 0, 0, 0, 0, 1, 0> Amount;
DECLARE_BASE_QUANTITY(Amount, mol, 1.0L);

typedef Quantity<0, 0, 0, 0, 0, 0, 1> Luminosity;
DECLARE_BASE_QUANTITY(Luminosity, cd, 1.0L);


DECLARE_DERIVED_QUANTITY(Force, N, kg*m/s_p2);
DECLARE_DERIVED_QUANTITY(Energy, J, N*m);
DECLARE_DERIVED_QUANTITY(Frequency, Hz, s_n1);

DECLARE_DERIVED_QUANTITY_NO_SYMBOL(Area, m_p2);
DECLARE_DERIVED_QUANTITY_NO_SYMBOL(Volume, m_p3);
DECLARE_DERIVED_QUANTITY_NO_SYMBOL(Moment, N*m);

#endif // BTUL_H

