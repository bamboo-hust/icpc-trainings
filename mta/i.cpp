#include <bits/stdc++.h>
#define int long long

using namespace std;

int32_t main() {
    int m, x, y, w, h;
    cin >> m >> x >> y >> w >> h;
    int xl = x / m;
    int xr = (x + w) / m + !!((x + w) % m);
    int yl = y / m;
    int yr = (y + h) / m + !!((y + h) % m);
    cout << 1LL * (xr - xl) * (yr - yl) << endl;
    return 0;
}