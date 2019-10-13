#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("h.in", "r", stdin);
    int m, n;
    cin >> m >> n;
    int res = 0;
    for (int x = 1; x <= m; ++x) {
        for (int y = x; y <= m; ++y) {
            for (int z = y; z <= m; ++z) {
                res += x * x + y * y == z * z;
            }
        }
    }
    // x == 0 => y^j = z^j
    // x==0, y==0 => (n-1)
    // x==0, y!=0 => m * (n-1)
    res += (n - 1);
    res += m * (n - 1);
    cout << res << endl;
}