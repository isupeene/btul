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

#ifndef BASE_TEST_CASES_H
#define BASE_TEST_CASES_H 

/// Base class for testing streamed output.
/// Simply asserts that the text inserted into
/// the \a result stream is the same as the
/// expected variable.
///
/// \code
/// typedef OutputStreamTest ExampleTest;
///
/// TEST_F(OutputStreamTest, test00_HelloWorld) {
/// 	expected = "Hello World!";
///	result << "Hello World!";
/// }
/// \endcode
class OutputStreamTest : public testing::Test {
public:
	virtual void TearDown() {
		ASSERT_EQ(expected, result.str());
	}

	std::string expected;
	std::ostringstream result;
};

#endif // BASE_TEST_CASES_H

