#include <bits/stdc++.h>
#define int long long

using namespace std;
const int INF = 1e9;

int bezout(int a, int b) {
    // return x such that ax + by == gcd(a, b)
    int xa = 1, xb = 0;
    while (b) {
        int q = a / b;
        int r = a - q * b, xr = xa - q * xb;
        a = b; xa = xb;
        b = r; xb = xr;
    }
    return xa;
}

pair<int, int> solve(int a, int b, int c) {
    // solve ax + by == c
    int d = __gcd(a, b);
    int x = bezout(a, b);
    int y = (d - a * x) / b;
    c /= d;
    return make_pair(x * c, y * c);
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    //int T; cin >> T;
    int T = 100;
    while (T--) {
        int ax, ay, bx, by, k;
        //cin >> ax >> ay >> bx >> by >> k;
        ax = rand() % INF - rand() % INF;
        ay = rand() % INF - rand() % INF;
        bx = rand() % INF - rand() % INF;
        by = rand() % INF - rand() % INF;
        k = 10;
        cout << ax << ' ' << ay << ' ' << bx << ' ' << by << ' ' << k << endl;

        int x0 = bx - ax;
        int y0 = by - ay;
        pair<int, int> C = solve(y0, -x0, __gcd(abs(x0), abs(y0)) + ax * y0 - ay * x0);
        cout << C.first << ' ' << C.second << endl;
        for (int i = 0; i < k; ++i) {
            int x = C.first - x0 * i;
            int y = C.second - y0 * i;
            assert(abs(x) < 1e14);
            cout << x << ' ' << y << '\n';
        }
    }
}