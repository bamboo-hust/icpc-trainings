#include <bits/stdc++.h>

using namespace std;

struct Fraction {
    long long a, b;
    int id;
    bool operator < (const Fraction &o) const {
        if (a * o.b != b * o.a) return a * o.b < b * o.a;
        return id < o.id;
    }
};

long long calc(long long S, long long a, long long b, long long c) {
    return 2LL * a * b * (S - b - a) + b * a * a + a * b * b;
}

int main() {
    int n;
    cin >> n;
    vector< Fraction > L;
    for (int i = 1; i <= n; ++i) {
        long long S;
        long long a, b, c;
        cin >> S >> a >> b >> c;

        long long numer = 0;
        numer += calc(S, a, b, c);
        numer += calc(S, a, c, b);
        numer += calc(S, b, a, c);
        numer += calc(S, b, c, a);
        numer += calc(S, c, a, b);
        numer += calc(S, c, b, a);

        L.push_back(Fraction{numer, S * S * S, i});
    }
    sort(begin(L), end(L));
    for (int i = 0; i < n; ++i) {
        cout << L[i].id << ' ';
    }
    cout << endl;
    return 0;
}