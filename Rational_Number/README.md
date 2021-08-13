> # Programming Assignment: Rational Class
> In this task, you need to design a class for representing rational numbers and embed it in the C ++ language type system so that it can be used naturally. The assignment consists of several parts. A file with a program preparation is attached to each part, which has the following structure

> ## Part 1
> In the first part, you need to implement the Rational class, which is a rational number of the form p / q, where p is an integer and q is a natural and the ranges of possible values of p, q are such that they can be represented by the int type.
> The Rational class must ensure that p / q is an irreducible fraction.

> The list of requirements for the implementation of the interface of the Rational class:
1. The default constructor should create a fraction with numerator 0 and denominator 1.
2. When constructing an object of a Rational class with parameters p and q, the reduction of the fraction p / q must be performed
3. If p / q is negative, then the Rational (p, q) object must have a negative numerator and a positive denominator.
4. If p / q is positive, then the Rational (p, q) object must have a positive numerator and denominator (note the Rational (-2, -3) case).
5. If the numerator of the fraction is zero, then the denominator must be 1.
   
> ## Part 2
> Implement the ==, +, and - operators for the Rational class so that you can write operations on fractions naturally. For example, the following code must be valid:
```cpp
const Rational r = Rational(1, 2) + Rational(1, 3) - Rational(1, 4);
if (r == Rational(7, 12)) {
  cout << "equal";
}
```

> ## Part 3
> Similar to the previous section, implement the * and / operators. For example, the following code must be valid:
```cpp
const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
if (r == Rational(2, 3)) {
  cout << "equal";
}
```

> ## Part 4
> In this part, you need to implement the input and output statements for the Rational class. For example, the following code must be valid:

```cpp
Rational r;
cin >> r;
cout << r;
```

> ## Part 5
> Finally, you need to implement the ability to use objects of the Rational class as elements of the set container and keys in the map container.

```cpp
set<Rational> rationals;
rationals.insert(Rational(1, 2));
rationals.insert(Rational(1, 3));

map<Rational, string> name;
name[Rational(1, 2)] = "one half";
```

> ## Changes
> I changed the implementation of the Rational class constructor so that it throws an invalid_argument exception if the denominator is zero. Also, rewrite the implementation of the division operator for the Rational class so that it throws a domain_error exception if the divisor is zero.
