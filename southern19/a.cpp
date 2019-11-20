<<<<<<< HEAD
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
=======
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define ii pair<int, int>
#define X first
#define Y second
const int N = 50005;
using namespace std;
ii a[N], H[N];
int n, k;
 
void operator -= (ii &A, ii &B) {A.X -= B.X; A.Y -= B.Y;}
bool ccw(ii A, ii B, ii C) {C -= B; B -= A; return B.X * C.Y >= B.Y * C.X;}
int area(int i, int j, int k) 
    {return abs(H[i].X * (H[j].Y - H[k].Y) + H[j].X * (H[k].Y - H[i].Y) + H[k].X * (H[i].Y - H[j].Y));}
 
int Find(int l, int r) {
    int ll = l, rr = r, S = 0;
    while (ll < rr) {
        int m = ll + rr >> 1;
        int p = area(l, m, r), q = area(l, m + 1, r);
        if (p <= q) 
            ll = m + 1;
        else 
            rr = m;
        S = max(S, max(p, q));
    }
    return S;
}
 
int Search(int l, int r) {
    int ll = l + 1, rr = r - 1, S = 0;
    while (ll < rr) {
        int m = ll + rr >> 1;
        int p = Find(l, m), q = Find(l, m + 1);
        if (p <= q) 
            ll = m + 1;
        else
            rr = m;
        S = max(S, max(p, q));
    }
    return S;
}
 
int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        if (n == -1) break;
        for(int i = 0; i < n; i++)
            cin >> a[i].X >> a[i].Y;
        sort(a, a + n);
        int k = 0;
        for(int i = 0; i < n; i++) {
            while (k >= 2 && ccw(H[k - 2], H[k - 1], a[i])) k--;
            H[k++] = a[i];
        }
        for(int i = n - 2, t = k + 1; i >= 0; i--) {
            while (k >= t && ccw(H[k - 2], H[k - 1], a[i])) k--;
            H[k++] = a[i];
        }
        k--;
        int res = 0;
        for(int i = 0; i < k; i++) 
            res = max(res, Search(i, k));
        cout << setprecision(1) << fixed << (double)res / 2 << '\n';
    }
    return 0;
>>>>>>> aaed81a... update
}