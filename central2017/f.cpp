#include <bits/stdc++.h>

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define REP(i, a, b) for(int i = (a); i <=(b); ++i)
#define REPD(i, a, b) for(int i = (a); i >=(b); --i)
#define SZ(a) (int(a.size()))
#define ALL(a) a.begin(), a.end()
#define PB push_back

using namespace std;

//BIG INTEGER

typedef vector<int> bigInt;

const int BASE = 1000;
const int LENGTH = 3;

void fix(bigInt &a) {
    a.PB(0);
    FOR(i, 0, SZ(a) - 1) {
        a[i + 1] += a[i] / BASE; a[i] %= BASE;
        if (a[i] < 0) a[i] += BASE, --a[i + 1];
    }
    while (SZ(a) > 1 && a.back() == 0) a.pop_back();
}

bigInt big(int a) {
    bigInt ret;
    while (a) {
        ret.PB(a % BASE);
        a /= BASE;
    }
    return ret;
}

bigInt big(string s) {
    bigInt ret (SZ(s) / LENGTH + 1);
    FOR(i, 0, SZ(s)) {
        int x = (SZ(s) - i - 1) / LENGTH;
        ret[x] = ret[x] * 10 + s[i] - '0';
    }
    return fix(ret), ret;
}

istream& operator >> (istream& cin, bigInt &a) {
    string s; cin >> s;
    a = big(s);
    return cin;
}

ostream& operator << (ostream& cout, const bigInt &a) {
    printf("%d", a.back());
    REPD(i, SZ(a) - 2, 0)
        printf("%03d", a[i]);
    return cout;
}

bool operator < (bigInt a, bigInt b) {
    if (SZ(a) != SZ(b)) return SZ(a) < SZ(b);
    REPD(i, SZ(a) - 1, 0)
    if (a[i] != b[i]) return a[i] < b[i];
    return 0;
}

void operator += (bigInt &a, bigInt b) {
    a.resize(max(SZ(a), SZ(b)));
    FOR(i, 0, SZ(b)) a[i] += b[i];
    fix(a);
}
void operator -= (bigInt &a, bigInt b) {
    FOR(i, 0, SZ(b)) a[i] -= b[i];
    fix(a);
}
void operator *= (bigInt &a, int b) {
    FOR(i, 0, SZ(a)) a[i] *= b;
    fix(a);
}

bigInt operator + (bigInt a, bigInt b)
    { a += b; return a; }
bigInt operator - (bigInt a, bigInt b)
    { a -= b; return a; }
bigInt operator * (bigInt a, int b)
    { a *= b; return a; }
bigInt operator * (bigInt a, bigInt b) {
    bigInt c (SZ(a) + SZ(b));
    FOR(i, 0, SZ(a)) FOR(j, 0, SZ(b))
        c[i + j] += a[i] * b[j];
    return fix(c), c;
}

void div(bigInt a, int b, bigInt &q, int &r) {
    q.clear(); r = 0;
    REPD(i, SZ(a) - 1, 0) {
        r = r * BASE + a[i];
        q.PB(r / b); r %= b;
    }
    reverse(ALL(q)); fix(q);
}

bigInt operator / (bigInt &a, int b) {
    bigInt q; int r;
    div(a, b, q, r);
    return q;
}
bigInt operator % (bigInt &a, int b) {
    bigInt q; int r;
    div(a, b, q, r);
    return q;
}

int main() {
    int n; cin >> n;
    bigInt F[100];
    F[0].push_back(1);
    F[1].push_back(1);
    for (int i = 2; i <= n; ++i) F[i] = F[i - 1] + F[i - 2];
    //cerr << F[n - 1] << endl;
    bigInt ans = F[n - 1];
    for (int i = 1; i < n; ++i) {
        ans = ans * F[n - 1];
    }
    cout << ans << endl;
    return 0;
}