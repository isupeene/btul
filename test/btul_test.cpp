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

	ASSERT_EQ(expected, length1.value);
	ASSERT_EQ(expected, length2.value);

	ASSERT_EQ(expected, mass1.value);
	ASSERT_EQ(expected, mass2.value);

	ASSERT_EQ(expected, time1.value);
	ASSERT_EQ(expected, time2.value);

	ASSERT_EQ(expected, current1.value);
	ASSERT_EQ(expected, current2.value);

	ASSERT_EQ(expected, temperature1.value);
	ASSERT_EQ(expected, temperature2.value);

	ASSERT_EQ(expected, amount1.value);
	ASSERT_EQ(expected, amount2.value);

	ASSERT_EQ(expected, luminosity1.value);
	ASSERT_EQ(expected, luminosity2.value);
}

TEST(ValueTest, test01_multipliers) {
	ASSERT_EQ(pow(10, 12), Tm.value);
	ASSERT_EQ(pow(10, 12), (1_Tm).value);

	ASSERT_EQ(pow(10, 9), Gm.value);
	ASSERT_EQ(pow(10, 9), (1_Gm).value);

	ASSERT_EQ(pow(10, 6), Mm.value);
	ASSERT_EQ(pow(10, 6), (1_Mm).value);

	ASSERT_EQ(pow(10, 3), km.value);
	ASSERT_EQ(pow(10, 3), (1_km).value);

	ASSERT_EQ(pow(10, 2), hm.value);
	ASSERT_EQ(pow(10, 2), (1_hm).value);

	ASSERT_EQ(pow(10, 1), dam.value);
	ASSERT_EQ(pow(10, 1), (1_dam).value);

	ASSERT_EQ(pow(10, -1), dm.value);
	ASSERT_EQ(pow(10, -1), (1_dm).value);

	ASSERT_EQ(pow(10, -2), cm.value);
	ASSERT_EQ(pow(10, -2), (1_cm).value);

	ASSERT_EQ(pow(10, -3), mm.value);
	ASSERT_EQ(pow(10, -3), (1_mm).value);

	ASSERT_EQ(pow(10, -6), um.value);
	ASSERT_EQ(pow(10, -6), (1_um).value);

	ASSERT_EQ(pow(10, -9), nm.value);
	ASSERT_EQ(pow(10, -9), (1_nm).value);

	ASSERT_EQ(pow(10, -12), pm.value);
	ASSERT_EQ(pow(10, -12), (1_pm).value);
}

