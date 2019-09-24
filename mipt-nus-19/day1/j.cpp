#include <bits/stdc++.h>

using namespace std;

int64_t n, m;
long double f;

long double calc(int64_t d_int) {
    if (d_int < 0 || d_int >= n) return 0;
    long double d = d_int;
    long double res = (m - d * d * f * f) / (n - d);
    //cerr << "calc " << d_int << ' ' << res << ' ' << (m - (d * f) * (d * f)) << endl;
    return res;
}

long double solve(long double d_frac) {
    int64_t mid = round(d_frac);
    long double res = 0;
    for (int64_t d = mid - 1; d <= mid + 1; ++d) {
        res = max(res, calc(d));
    }
    return res;
}

int main() {
    cin >> n >> m >> f;
    long double a = f * f;
    long double b = -2 * f * f * n;
    long double c = m;

    long double delta = b * b - 4 * a * c;
    long double res = 0;
    if (delta >= 0) {
        res = max(res, solve((-b + sqrt(delta)) / (2 * a)));
        res = max(res, solve((-b - sqrt(delta)) / (2 * a)));
    }
    res = max(res, solve(0));
    res = max(res, solve(n - 1));
    cout << setprecision(9) << fixed << res << endl;
    return 0;
}