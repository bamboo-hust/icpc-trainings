#include <bits/stdc++.h>

using namespace std;

struct Point {
    int64_t x, y;
} a[2019];

int64_t area(Point A, Point B, Point C) {
    return abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;
    int64_t res = 0;
    for (int i = 0; i < n; ++i) {
        int k = (i + 2) % n;
        for (int j = i + 1; j < n; ++j) {
            while ((k + 1) % n != i && area(a[i], a[j], a[j]) <= area(a[i], a[j], a[(k + 1) % n])) k = (k + 1) % n;
            res = max(res, area(a[i], a[j], a[k]));
        }
    }

    cout << setprecision(1) << fixed << res / 2.0 << endl;
}