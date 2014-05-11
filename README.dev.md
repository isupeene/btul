This README provides information for contributors to btul, or any users of btul who wish to debug or modify their own version of the source, or are simply curious about the implementation details or project structure.

Overview
--------

Btul is divided into source, and distinct testing sections.

*src - The source.  Everything needed to deploy btul in a project can be found here.  It consists solely of header files, making it dead-easy to integrate into any build system.
*test - Functional unit tests based on gtest.  The makefile is the pre-packaged gtest makefile with as few modifications as possible, so it should be easy for anyone experienced with gtest to add additional tests.
*benchmarking (not yet implemented) - will contain benchmarking code to compare btul calculations with bare floating point computations.
*code analysis (not yet implemented) - will contain tests to ensure that unnecessary code bloat doesn't occur when using btul.
*compilation tests (not yet implemented) - The whole point of using a rich type system for units is to prevent errors caused by typos and other human mistakes at compile-type.  This section will contain tests that we expect not to compile at all.

General note: If you want to help improve btul, feel free to open a pull request on GitHub.  For large changes or additions however, send me an email first to discuss the change at isupeene@ualberta.ca.  I don't want your hard work to go to waste!

Source
------

This is the heart and soul of btul.  If you change it, be sure to do the following:

* Adhere to the style of the surrounding code.
* Make sure all the tests still pass, and performance and code analysis tests are not negatively impacted.
* If you are fixing a bug, add a test in the appropriate test directory that fails before your change, and passes afterwards.
* If you are adding a feature, again, add a test in the appropriate test directory.
* If you are improving performance, either add a test in the benchmarking directory that your change improves significantly, or demonstrate that your change significantly improves the performance of an existing test case.
* If you are reducing the size of binaries using btul, either add a test in the code analysis directory that your change improves significantly, or demonstrate that your change significantly reduces the size of an existing test case.
* If you need to add a test, follow the more detailed guidelines for the specific type of test you're adding.


Test
----

We use gtest to test the behaviour of btul.  Related test cases should all be in the same case/fixture.  There should be one fixture per file.  To add a new test, simply add a make target for it, and append it to the TESTS variable.


FAQ
---

__Q: What's with the wierd notation for exponents?__

A: Realistic exponents are an interesting problem in C++ for the following reason:  If you have a piece of paper in front of you, and you write 1 km^2, you know that this is, in fact, 1,000,000 m^2.  In this case, grouping doesn't matter, and we can equivalently write (1 km)^2.  In C++, we could (hypothetically) represent this as 1_km^2.<sup>1</sup>  Or, we could represent this as (1_km)^2, and get the same result.

Now suppose you take your piece of paper and write 10 km^2.  This is the equivalent of 10,000,000 m^2.  But if you were to write (10 km)^2, you would expect this to yield 100,000,000 m^2.  But in C++, both of these results will yield 100,000,000 m^2.  That
s because in both cases, the UDL is being evaluated before the exponent.  In other words, __there's literally no way to make 10_km^2 yield a different value than (10_km)^2__.  It doesn't matter what variation you use, function((10_km)) is going to be the same as function(10_km).

So we really can't achieve our goal of accurately representing both 10 km^2 and (10 km)^2 unless we use a completely different syntax for each, which ideally, can't be interchanged with the other.  So for the 10 km^2 case, we simply use an extension to the UDL: 10_km_p2.  For the (10 km)^2 case, we use a member function: (10_km).p2().

Now, you may be thinking "But this doesn't satisfy the non-interchangeability constraint, because I could just write 10_km.p2() and get a the 'wrong' answer."  Well, turns out you can't, due to some arcane rules in the C++ standard that most ordinary humans never need to concern themselves with.  Turns out that according to the standard, the entirety of 10_km.p2 matches the definition of a _pp-number_.  Which means that that whole thing is passed as a single token to the parser,which _correctly_ tries to look up _km.p2 as the UDL suffix, and of course fails.  This means that the approach used in btul gives us two completely orthoganal ways of expressing exponents, and each one does exactly what you want it to do.

As for complaints about how _p2 and .p2() are ugly ways of expressing exponents, you are correct, and as soon as there's a nicer way to express them, we'll jump right on it!

<sup><sup>1</sup>This is just an example of course, as there are obvious precedence issues with using operator ^ for exponents.</sup>

