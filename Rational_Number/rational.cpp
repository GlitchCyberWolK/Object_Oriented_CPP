#include <iostream>
#include <set>

using namespace std;

int gcd(int a, int b) {
    if(a == 0) return b;
    return gcd(b % a, a);
}

class Rational {
public:
    Rational();
    Rational(const int &p,const int &q);

    int Numerator() const;
    int Denominator() const;
private:
    int num;
    int denum;
};

Rational::Rational() {
    num = 0;
    denum = 1;
}

Rational::Rational(const int &p, const int &q) {
    if(p == 0) {
        num = p;
        denum = 1;
    }
    else if((p < 0 && q < 0) || (p > 0 && q > 0)) {
        num = abs(p);
        denum = abs(q);
        int GCD = gcd(abs(num), abs(denum));
        num /= GCD;
        denum /= GCD;
    } else if((p < 0 && q > 0) || (p > 0 && q < 0)) {
        num = -abs(p);
        denum = abs(q);
        int GCD = gcd(abs(num), abs(denum));
        num /= GCD;
        denum /= GCD;
    } else if(!q) {
        throw invalid_argument("Invalid argument");
    }
}

int Rational::Numerator() const {
    return num;
}

int Rational::Denominator() const {
    return denum;
}

bool operator==(const Rational &rhs, const Rational &lhs) {
    if((rhs.Numerator() == lhs.Numerator()) && (rhs.Denominator() == lhs.Denominator())) {
        return true;
    } return false;
}

Rational operator+(const Rational &rhs, const Rational &lhs) {
    if(rhs.Denominator() == lhs.Denominator()) {
        return {rhs.Numerator() + lhs.Numerator(), rhs.Denominator()};
    }
    int a = rhs.Numerator(), b = rhs.Denominator(), c = lhs.Numerator(), d = lhs.Denominator();
    return {b*c + d*a, b*d};
}

Rational operator-(const Rational &rhs, const Rational &lhs) {
    if(rhs.Denominator() == lhs.Denominator()) {
        return {rhs.Numerator() - lhs.Numerator(), rhs.Denominator()};
    }
    int a = rhs.Numerator(), b = rhs.Denominator(), c = lhs.Numerator(), d = lhs.Denominator();
    return {a*d - b*c, b*d};
}

Rational operator*(const Rational &rhs, const Rational &lhs) {
    return {rhs.Numerator() * lhs.Numerator(), rhs.Denominator() * lhs.Denominator()};
}

Rational operator/(const Rational &rhs, const Rational &lhs) {
    if(!(rhs.Denominator() * lhs.Numerator())) {
        throw domain_error("Division by zero");
    } return {rhs.Numerator() * lhs.Denominator(), rhs.Denominator() * lhs.Numerator()};
}

istream &operator>>(istream &stream, Rational &rhs) {
    int p, q;
    char op;
    if (stream >> p && stream >> op && stream >> q) {
        if(op == '/') rhs = {p, q};
        else throw invalid_argument("Invalid argument");
    }
    return stream;
}

ostream &operator<<(ostream &stream,const Rational &rhs) {
    stream << rhs.Numerator() << "/" << rhs.Denominator();
    return stream;
}

bool operator<(const Rational &rhs, const Rational &lhs) {
    return (rhs.Numerator()*lhs.Denominator()) < (lhs.Numerator()*rhs.Denominator());
}

bool operator>(const Rational &rhs, const Rational &lhs) {
    return (rhs.Numerator()*lhs.Denominator()) > (lhs.Numerator()*rhs.Denominator());
}

char c;

void exceptionPrint(const exception &e) {
    cout << e.what() << endl;
}

int main() {
    Rational left{}, right{};
    try {
        cin >> left;
        cin >> c;
        cin >> right;
        switch(c) {
            case '+':
                cout << (left + right) << endl; break;
            case '-':
                cout << (left - right) << endl; break;
            case '*':
                cout << (left * right) << endl; break;
            case '/':
                cout << (left / right) << endl; break;
            default: cout << endl; }
    } catch(const exception &e) {cout << e.what() << endl;}

    return 0;
}
