btul
====

BTUL Takes Units Literally

BTUL (pronounced 'beetle') is a lightweight library for doing computational mathematics with physical quantities.  In particular, BTUL provides a strongly typed unit system, which makes use of c++11's user-defined literals to create an elegant, very readable syntax for literal physical quantities.

THIS IS NOT A GENERIC UNIT FRAMEWORK!!!  It is a framework for representing physical quantities which can be expressed in terms of the seven fundamental base quantities defined by SI.  If you need to express quantities in terms of farthings or numbers of oranges, this is not the tool for you.

Note also that this library makes use of the user-defined literals feature of c++11, in addition to various other new features.  Keep in mind that not all compilers may support this, and you may need to set certain compiler variables in order to use the latest standard.

Roadmap:
* Add gtest.h and provide reasonable test cases for existing code.
* Add benchmarking code to compare computations with physical units to computations with raw doubles/long doubles.
* Separation of concerns - move code into multiple header files / namespaces.
* Improve flexibility of output formatting - make unit declarations templated typedefs with a default value for the formatting class, rather than a complete specification of all type arguments.
* Improve coverage of SI units.
* Add separate namespaces for imperial and other unit systems, and populate with the appropriate units.
* Improve flexibility of output formatting - determine what a sensible set of rules would be for determining when to use multiplier prefixes, and create a simple system for specifying custom rules.
* Improve math support.  Create overloads of standard math functions that work on quantities.
* Input - allow any quantity to be read in from a stream of text which could be reasonably inferred to represent that quantity.
* Wait for a new c++ standard that gives us a better way to represent exponents, as this is the only wart in an otherwise lovely syntax.
