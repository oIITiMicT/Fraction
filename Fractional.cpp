#include <iostream>
#include <algorithm>

using namespace std;

const int inf = int(1e9) + 123;

int gcd(int a, int b) {
    while (b > 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

int lcm(int a, int b) {
    return gcd(a, b) * a * b;
}

class Fraction {
public:
    Fraction(int n_num = 0, int n_denum = 1) {
        num = n_num;
        denum = n_denum;
    };
    friend istream& operator>>(istream &in, Fraction &fract);
    friend ostream& operator<<(ostream &out, Fraction fract);
    friend Fraction& operator+=(Fraction& lhs, const Fraction& rhs);
    friend Fraction& operator-=(Fraction& lhs, const Fraction& rhs);
    friend Fraction operator+(Fraction& lhs, Fraction& rhs);
    friend Fraction operator-(Fraction& lhs, Fraction& rhs);
    friend Fraction operator*(Fraction& lhs, Fraction& rhs);
    friend Fraction operator/(Fraction& lhs, Fraction& rhs);
    friend Fraction& operator*=(Fraction& lhs, const Fraction& rhs);
    friend Fraction& operator/=(Fraction& lhs, const Fraction& rhs);
    friend bool operator==(Fraction lhs, Fraction rhs);
    friend bool operator!=(Fraction lhs, Fraction rhs);
    Fraction operator++() {
        num += denum;
        return *this;
    }
    Fraction operator++(int) {
        Fraction prev = *this;
        ++*this;
        return prev;
    }
    Fraction operator--() {
        num -= denum;
        return *this;
    }
    Fraction operator--(int) {
        Fraction prev = *this;
        --*this;
        return prev;
    }
private:
    void Rational() {
        Check();
        int x = __gcd(abs(num), abs(denum));
        num /= x;
        denum /= x;
    }
    void Check() {
        if (num != 0 && denum == 0) {
            cout << "Error: denominator cannot be zero \n";
            num = inf;
            denum = 1;
        }
        if (num == 0 && denum != 0) {
            denum = 1;
        }
        if (num == 0 && denum == 0) {
            denum = 1;
        }
        if (num <= 0) {
            if (denum < 0) {
                num = abs(num);
                denum = abs(num);
            }
        } else {
            if (denum < 0) {
                num = -num;
                denum = -denum;
            }
        }
    }
    int num;
    int denum;
};

istream& operator>>(istream &in, Fraction &fract) {
    in >> fract.num;
    in >> fract.denum;
    fract.Rational();
    return in;
}

ostream& operator<< (ostream& out, Fraction fract) {
    fract.Rational();
    out << fract.num << '/' << fract.denum;
    return out;
}

Fraction& operator+=(Fraction& lhs, const Fraction& rhs) {
    int a = lhs.denum, b = rhs.denum;
    int common_denum = lcm(a, b);
    lhs.num = (common_denum / lhs.denum * lhs.num) + (common_denum / rhs.denum * rhs.num);
    lhs.denum = common_denum;
    lhs.Rational();
    return lhs;
}

Fraction& operator-=(Fraction& lhs, const Fraction& rhs) {
    int a = lhs.denum, b = rhs.denum;
    int common_denum = lcm(a, b);
    lhs.num = (common_denum / lhs.denum * lhs.num) - (common_denum / rhs.denum * rhs.num);
    lhs.denum = common_denum;
    lhs.Rational();
    return lhs;
}

Fraction operator+(Fraction& lhs, Fraction& rhs) {
    int a = lhs.denum, b = rhs.denum;
    int common_denum = lcm(a, b);
    Fraction ans {(common_denum / lhs.denum * lhs.num) + (common_denum / rhs.denum * rhs.num), common_denum};
    ans.Rational();
    return ans;
}

Fraction operator-(Fraction& lhs, Fraction& rhs) {
    int a = lhs.denum, b = rhs.denum;
    int common_denum = lcm(a, b);
    Fraction ans {(common_denum / lhs.denum * lhs.num) - (common_denum / rhs.denum * rhs.num), common_denum};
    ans.Rational();
    return ans;
}

Fraction operator*(Fraction& lhs, Fraction& rhs) {
    Fraction ans {lhs.num * rhs.num, lhs.denum * rhs.denum};
    ans.Rational();
    return ans;
}

Fraction operator/(Fraction& lhs, Fraction& rhs) {
    Fraction ans = {lhs.num * rhs.denum, rhs.num * lhs.denum};
    ans.Rational();
    return ans;
}

Fraction& operator*=(Fraction& lhs, const Fraction& rhs) {
    lhs.num *= rhs.num;
    lhs.denum *= rhs.denum;
    lhs.Rational();
    return lhs;
}

Fraction& operator/=(Fraction& lhs, const Fraction& rhs) {
    lhs.num *= rhs.denum;
    lhs.denum *= rhs.num;
    lhs.Rational();
    return lhs;
}

bool operator==(Fraction lhs, Fraction rhs) {
    return (lhs.num == rhs.num && rhs.denum == lhs.denum);
}

bool operator!=(Fraction lhs, Fraction rhs) {
    return (lhs.num != rhs.num || rhs.denum != lhs.denum);
}

int main() {
    Fraction x, y;
    cin >> x >> y;
    if (x != y) {
        cout << "YES";
    }
    return 0;
}