#include <bits/stdc++.h>

using namespace std;

struct Fraction {
    int a, b;
    Fraction(int a = 0, int b = 1) : a(a), b(b) {}
    void normalize() {
        if (a == 0) b = 1;
        else {
            int x = __gcd(a, b);
            a /= x;
            b /= x;
        }
    }
    Fraction operator + (const Fraction &u) const {
        Fraction res;
        res.a = a * u.b + b * u.a;
        res.b = b * u.b;
        res.normalize();
        return res;
    }
    Fraction operator - (const Fraction &u) const {
        Fraction res;
        res.a = a * u.b - b * u.a;
        res.b = b * u.b;
        res.normalize();
        return res;
    }
    Fraction operator * (Fraction &u) const {
        Fraction res;
        res.a = a * u.a;
        res.b = b * u.b;
        res.normalize();
        return res;
    }
    Fraction operator * (int k) const {
        Fraction res;
        res.a = a * k;
        res.b = b;
        res.normalize();
        return res;
    }
    bool operator <= (const Fraction &u) const {
        return a * u.b - b * u.a <= 0;
    }
    bool operator < (const Fraction &u) const {
        return a * u.b - b * u.a < 0;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    if (n == m) {
        cout << "0 / 1\n";
        return 0;
    }
    if (n > m) swap(n, m);
    Fraction nn(1, n), mm(1, m);
    int cur = 0;
    Fraction res = mm;
    for (int i = 0; i < n; i++) {
        Fraction now = nn * i;
        while ((mm * cur) <= now) cur++;
        Fraction foo = (mm * cur);
        res = min(res, (mm * cur) - now);
    }
    Fraction foo(1, 2);
    res = res * foo;
    res = mm - res;
    cout << res.a << " / " << res.b << endl;
    return 0;   
}