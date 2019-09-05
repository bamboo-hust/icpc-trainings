#include <bits/stdc++.h>

using namespace std;

const int N = 22;
const double EPS = 1e-6;

inline int cmp(double u, double v) {
    if (abs(u - v) < EPS) return 0;
    if (u + EPS < v) return -1;
    return 1;   
}

int n;
pair<int, int> a[N];

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator + (const Point &u) const {
        return Point(x + u.x, y + u.y);
    }
    Point operator - (const Point &u) const {
        return Point(x - u.x, y - u.y);
    }
    Point operator * (double k) const {
        return Point (x * k, y * k);
    }
    double norm() {
        return x * x + y * y;
    }
    double len() {
        return sqrt(norm());
    }
} target, res[N];

bool checkTri(double a, double b, double c) {
    if (cmp(a, b + c) > 0) return 0;
    if (cmp(b, a + c) > 0) return 0;
    if (cmp(c, a + b) > 0) return 0;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(10);
    cout << fixed;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    cin >> target.x >> target.y;
    Point u = target;
    if (cmp(target.len(), 0) == 0) {
        u = Point(1, 0);
    } else {
        u = u * (1 / u.len());
    }
    if (n == 1) {
        Point res = u * a[1].first;
        cout << res.x << ' ' << res.y << endl;
        return 0;   
    }
    sort(a + 1, a + n + 1, greater<pair<int, int>>());
    int sum = 0;
    for (int i = 2; i <= n; i++) {
        sum += a[i].first;
    }
    
    if (cmp(target.len(), a[1].first + sum) >= 0) {
        for (int i = 1; i <= n; i++) {
            res[a[i].second] = u * a[i].first;
        }
        Point cur(0, 0);
        for (int i = 1; i <= n; i++) {
            cur = cur + res[i];
            cout << cur.x << ' ' << cur.y << '\n';
        }
        return 0;
    }

    if (cmp(a[1].first, target.len() + sum) >= 0) {
        res[a[1].second] = u * a[1].first;
        for (int i = 2; i <= n; i++) {
            res[a[i].second] = u * (-a[i].first);
        }
        Point cur(0, 0);
        for (int i = 1; i <= n; i++) {
            cur = cur + res[i];
            cout << cur.x << ' ' << cur.y << '\n';
        }
        return 0;
    }

        sum += a[1].first;

        int sum1 = 0;
        for (int i = 1; i <= n; i++) {
            sum1 += a[i].first;
            int sum2 = 0;
            for (int j = i + 1; j <= n; j++) {
                sum2 += a[j].first;
                double sum3 = sum - sum1 - sum2 + target.len();
                if (checkTri(sum1, sum2, sum3)) {
                    double alpha = atan2(u.y, u.x);
                    Point now(cos(alpha) * sum3, sin(alpha) * sum3);
                    double beta = (1.0 * sum3 * sum3 + 1.0 * sum1 * sum1 - 1.0 * sum2 * sum2) / (2.0 * sum1 * sum3);
                    beta = acos(beta);
                    alpha += beta;
                    Point foo(cos(alpha) * sum1, sin(alpha) * sum1);
                    Point bar = now - foo;
                    foo = foo * (1 / foo.len());
                    bar = bar * (1 / bar.len());
                    for (int k = 1; k <= i; k++) {
                        res[a[k].second] = foo * a[k].first;
                    }
                    for (int k = i + 1; k <= j; k++) {
                        res[a[k].second] = bar * a[k].first;
                    }
                    for (int k = j + 1; k <= n; k++) {
                        res[a[k].second] = u * -a[k].first; 
                    }
                    Point cur(0, 0);
                    for (int i = 1; i <= n; i++) {
                        cur = cur + res[i];
                        cout << cur.x << ' ' << cur.y << '\n';
                    }
                    return 0;
                }
            }
        }

    return 0;   
}