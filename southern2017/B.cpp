#include <bits/stdc++.h>
#define X first
#define Y second
#define sqr(a) ((a) * (a))

const int N = 222;
const int INF = 1e9;
const int LIMIT = 200;

using namespace std;

typedef pair<double, double> point;

int n;
point a[N];

double dist(const point &a, const point &b) {
    return sqr(a.X - b.X) + sqr(a.Y - b.Y);
}

double evaluate(point C) {
    double ans = 0;
    for (int i = 0; i < n; ++i)
        ans = max(ans, dist(C, a[i]));
    return ans;
}

double ternarySearchY(double x) {
    double ans = INF;
    double l = -2e4, r = 2e4;
    for (int loop = 0; loop < LIMIT; ++loop) {
        double tl = l + (r - l) / 3;
        double tr = r - (r - l) / 3;
        double vl = evaluate(point(x, tl));
        double vr = evaluate(point(x, tr));
        ans = min(ans, min(vl, vr));
        if (vl < vr)
            r = tr;
        else
            l = tl;
    }
    return ans;
}

double ternarySearchX() {
    double ans = INF;
    double l = -2e4, r = 2e4;
    for (int loop = 0; loop < LIMIT; ++loop) {
        double tl = l + (r - l) / 3;
        double tr = r - (r - l) / 3;
        double vl = ternarySearchY(tl);
        double vr = ternarySearchY(tr);
        ans = min(ans, min(vl, vr));
        if (vl < vr)
            r = tr;
        else
            l = tl;
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i].X >> a[i].Y;
    double ans = ternarySearchX();
    cout << setprecision(6) << fixed << sqrt(ans) << endl;
    return 0;
}
