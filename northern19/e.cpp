#include <bits/stdc++.h>
#define int int64_t

using namespace std;

template<class T>
T eval(const vector<int> &a, T x) {
    T res = 0;
    T p = 1;
    for (int i = 0; i < a.size(); ++i) {
        res += a[i] * p;
        p *= x;
    }
    return res;
}

double sign(double x) {
    return x < 0 ? -1 : 1;
}

vector<double> solve2(const vector<int> &e) {
    double a = e[2];
    double b = e[1];
    double c = e[0];
    double delta = b * b - 4.0 * a * c;
    if (delta < 0) return vector<double>();
    vector<double> x;
    x.push_back((-b + sqrt(delta)) / (2.0 * a));
    x.push_back((-b - sqrt(delta)) / (2.0 * a));
    return x;
}

int solve(vector<int> a) {
    int n = a.size() - 1;
    //cerr << "n=" << n << endl;
    if (n == 1) {
        return -a[0] / a[1];
    } else if (n == 2) {
        vector<double> x = solve2(a);
        int res = 1e9;
        for (double x_real : x) {
            for (int x_int = x_real - 5; x_int <= x_real + 5; ++x_int) {
                if (eval<int64_t>(a, x_int) == 0) {
                    res = min(res, x_int);
                }
            }
        }
        return res;
    } else {
        vector<int> a2(3);
        a2[2] = 3 * a[3];
        a2[1] = 2 * a[2];
        a2[0] = a[1];
        vector<double> x = solve2(a2);
        x.push_back(1e5);
        x.push_back(-1e5);
        sort(begin(x), end(x));
        int res = 1e9;
        for (int i = 1; i < x.size(); ++i) {
            double l = x[i - 1];
            double r = x[i];
            if (sign(eval<double>(a, l)) == sign(eval<double>(a, r))) continue;
            for (int it = 0; it < 100; ++it) {
                double mid = (l + r) / 2;
                if (sign(eval<double>(a, mid)) != sign(eval<double>(a, l))) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            for (int x_int = l - 5; x_int <= l + 5; ++x_int) {
                if (eval<int64_t>(a, x_int) == 0) {
                    res = min(res, x_int);
                }
            }
        }
        return res;
    }
}

vector<int> read() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = n; i >= 0; --i) cin >> a[i];
    return a;
}

vector<int> gen() {
    // ax3 + bx2 + cx + d = 0
    const int LIM = 10000;
    long long a = rand() % LIM - rand() % LIM;
    long long b = rand() % LIM - rand() % LIM;
    long long c = rand() % LIM - rand() % LIM;
    long long x = rand() % LIM - rand() % LIM;
    long long d = -a * x * x * x - b * x * x - c * x;
    cerr << a << ' ' << b << ' ' << c << ' ' << d << endl;
    cerr << "expect " << x << ' ';
    return vector<int>{d, c, b, a};
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    //int T = 100;
    while (T--) {
        vector<int> a = read();
        //vector<int> a = gen();
        cout << solve(a) << '\n';
    }
    return 0;
}