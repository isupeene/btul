#include <gtest/gtest.h>
#include <btul.h>
#include <BaseTestCases.h>
#include <ostream>


typedef OutputStreamTest HelloTest;

TEST_F(HelloTest, test00_pass) {
	expected = "Hello!";
	result << "Hello!";
}

TEST(ValueTests, test00_meters) {
	double expected = 10.0;
	Length actual = 10.0_m;
	ASSERT_EQ(expected, actual.value);
}

