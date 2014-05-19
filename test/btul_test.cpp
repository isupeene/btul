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

#include <gtest/gtest.h>

#include <btul.h>
#include <BaseTestCases.h>

#include <cmath>

using namespace std;

// Kind of arbitrary epsilon.
constexpr long double eps = 1.0 * std::pow(10, -18);

// Like EXPECT_NEAR and ASSERT_NEAR, except these functions
// work with our Quantity types.

#define EXPECT_WITHIN(v1, v2, epsilon)			\
	EXPECT_TRUE((v1).Within(epsilon, v2)) <<	\
		"Value " << v2 << " is not " <<		\
		"within " << epsilon << " of " << v1

#define ASSERT_WITHIN(v1, v2, epsilon)			\
	ASSERT_TRUE((v1).Within(epsilon, v2)) <<	\
		"Value " << v2 << " is not " <<		\
		"within " << epsilon << " of " << v1

TEST(ValueTests, test00_fundamentalQuantities) {
	double expected = 10.0;

	Length length1 = 10.0_m;
	Length length2 = 10_m;

	Mass mass1 = 10.0_kg;
	Mass mass2 = 10_kg;

	Time time1 = 10.0_s;
	Time time2 = 10_s;

	Current current1 = 10.0_A;
	Current current2 = 10_A;

	Temperature temperature1 = 10.0_K;
	Temperature temperature2 = 10_K;

	Amount amount1 = 10.0_mol;
	Amount amount2 = 10_mol;

	Luminosity luminosity1 = 10.0_cd;
	Luminosity luminosity2 = 10_cd;

	EXPECT_EQ(expected, length1.Value());
	EXPECT_EQ(expected, length2.Value());

	EXPECT_EQ(expected, mass1.Value());
	EXPECT_EQ(expected, mass2.Value());

	EXPECT_EQ(expected, time1.Value());
	EXPECT_EQ(expected, time2.Value());

	EXPECT_EQ(expected, current1.Value());
	EXPECT_EQ(expected, current2.Value());

	EXPECT_EQ(expected, temperature1.Value());
	EXPECT_EQ(expected, temperature2.Value());

	EXPECT_EQ(expected, amount1.Value());
	EXPECT_EQ(expected, amount2.Value());

	EXPECT_EQ(expected, luminosity1.Value());
	EXPECT_EQ(expected, luminosity2.Value());
}

TEST(ValueTest, test01_multipliers) {
	EXPECT_EQ(pow(10, 12), Tm.Value());
	EXPECT_EQ(pow(10, 12), (1_Tm).Value());

	EXPECT_EQ(pow(10, 9), Gm.Value());
	EXPECT_EQ(pow(10, 9), (1_Gm).Value());

	EXPECT_EQ(pow(10, 6), Mm.Value());
	EXPECT_EQ(pow(10, 6), (1_Mm).Value());

	EXPECT_EQ(pow(10, 3), km.Value());
	EXPECT_EQ(pow(10, 3), (1_km).Value());

	EXPECT_EQ(pow(10, 2), hm.Value());
	EXPECT_EQ(pow(10, 2), (1_hm).Value());

	EXPECT_EQ(pow(10, 1), dam.Value());
	EXPECT_EQ(pow(10, 1), (1_dam).Value());

	EXPECT_EQ(pow(10, -1), dm.Value());
	EXPECT_EQ(pow(10, -1), (1_dm).Value());

	EXPECT_EQ(pow(10, -2), cm.Value());
	EXPECT_EQ(pow(10, -2), (1_cm).Value());

	EXPECT_EQ(pow(10, -3), mm.Value());
	EXPECT_EQ(pow(10, -3), (1_mm).Value());

	EXPECT_EQ(pow(10, -6), um.Value());
	EXPECT_EQ(pow(10, -6), (1_um).Value());

	EXPECT_EQ(pow(10, -9), nm.Value());
	EXPECT_EQ(pow(10, -9), (1_nm).Value());

	EXPECT_EQ(pow(10, -12), pm.Value());
	EXPECT_EQ(pow(10, -12), (1_pm).Value());
}

TEST(ValueTest, test02_binaryArithmeticOperators) {
	EXPECT_WITHIN(2_m, m + m, eps);

	EXPECT_WITHIN(0_m, m - m, eps);

	EXPECT_WITHIN(5_m, m * 5, eps);
	EXPECT_WITHIN(4_m_p2, 2_m * 2_m, eps);
	EXPECT_WITHIN(10_m, 2 * 5_m, eps);
	

	EXPECT_WITHIN(s, 5_s / 5, eps);
	EXPECT_WITHIN(2_s, 4_s_p2 / 2_s, eps);
	EXPECT_WITHIN(5_Hz, 10 / 2_s, eps);
}

TEST(ValueTest, test03_arithmeticAssignmentOperators) {
	Length l1 = m;
	Length& l2 = l1 += m;
	EXPECT_WITHIN(2_m, l1, eps);
	EXPECT_EQ(&l1, &l2);

	Mass m1 = kg;
	Mass& m2 = m1 -= kg;
	EXPECT_WITHIN(0_kg, m1, eps);
	EXPECT_EQ(&m1, &m2);

	Time t1 = s;
	Time& t2 = t1 *= 5;
	EXPECT_WITHIN(5_s, t1, eps);
	EXPECT_EQ(&t1, &t2);

	Temperature T1 = 5_K;
	Temperature& T2 = T1 /= 5;
	EXPECT_WITHIN(K, T1, eps);
	EXPECT_EQ(&T1, &T2);
}

TEST(ValueTest, test04_unaryArithmeticOperators) {
	Length l1 = 10.0_m;
	Length l2 = +l1;
	EXPECT_EQ(l1.Value(), l2.Value());
	
	Length l3 = -l1;
	EXPECT_EQ(-(l1.Value()), l3.Value());
}

TEST(ValueTest, test05_prefixAndPostfixOperators) {
	Length l1 = m;
	Length& l2 = ++l1;
	EXPECT_WITHIN(2_m, l1, eps);
	EXPECT_EQ(&l1, &l2);

	Mass m1 = kg;
	Mass& m2 = --m1;
	EXPECT_WITHIN(0_kg, m1, eps);
	EXPECT_EQ(&m1, &m2);

	Time t1 = s;
	Time t2 = t1++;
	EXPECT_WITHIN(2_s, t1, eps);
	EXPECT_EQ(s, t2);

	Temperature T1 = K;
	Temperature T2 = T1--;
	EXPECT_WITHIN(0_K, T1, eps);
	EXPECT_EQ(K, T2);
}

TEST(ValueTest, test06_powers) {
	Area a1 = m_p2;
	EXPECT_EQ(1, a1.Value());

	Area a2 = 10_m_p2;
	EXPECT_EQ(10, a2.Value());

	Area a3 = (10_m).p2();
	EXPECT_EQ(pow(10, 2), a3.Value());

	Area a4 = 1_km_p2;
	EXPECT_EQ(pow(1000, 2), a4.Value());

	Area a5 = 10_km_p2;
	EXPECT_EQ(10 * pow(1000, 2), a5.Value());

	Area a6 = (10_km).p2();
	EXPECT_EQ(pow(10, 2) * pow(1000, 2), a6.Value());
}

