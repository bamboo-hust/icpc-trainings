#include <bits/stdc++.h>

using namespace std;

const int N = 610;
const int K = 20010;

int n, m, k;

inline int add(int u, int v) {
    return (u += v) >= m ? u - m : u;
}

inline int mul(int u, int v) {
    return u * v % m;
}

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point operator + (const Point &u) const {
        return Point(x + u.x, y + u.y);
    }
    Point operator - (const Point &u) const {
        return Point(x - u.x, y - u.y);
    }
    long long operator % (const Point &u) const {
        return 1ll * x * u.y - 1ll * u.x * y;
    }
};

Point a[N], b[K];
bool parity[N][N];
bool dead[N][N];
int dp[N][N];

long long ccw(Point u, Point v, Point w) {
    u = v - u;
    v = w - v;
    return u % v;
}

int go(int l, int r) {
    int &res = dp[l][r];
    if (res != -1) return res;
    if (l + 2 == r) return res = 1;
    res = 0;
    if (!parity[l + 1][r] && !dead[l + 1][r]) res = add(res, go(l + 1, r));
    if (!parity[l][r - 1] && !dead[l][r - 1]) res = add(res, go(l, r - 1));
    for (int m = l + 2; m < r - 1; m++) {
        if (!parity[l][m] && !parity[m][r] && !dead[l][m] && !dead[m][r]) res = add(res, mul(go(l, m), go(m, r)));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= k; i++) {
        cin >> b[i].x >> b[i].y;
    }
    for (int i = 1; i <= n; i++) {
        auto cmp = [&i](const Point &u, const Point &v) {
            Point uu = u - a[i];
            Point vv = v - a[i];
            return uu % vv > 0;
        };
        sort(b + 1, b + k + 1, cmp);
        int cur = 0;
        for (int j = i + 1; j <= n; j++) {
            while (cur < k && ccw(a[i], b[cur + 1], a[j]) >= 0) cur++;
            parity[i][j] = cur & 1;
            dead[i][j] = dead[j][i] = (cur > 0 && ccw(a[i], b[cur], a[j]) == 0);
        }
    }
    memset(dp, -1, sizeof dp);
    cout << go(1, n) << endl;
    return 0;
}