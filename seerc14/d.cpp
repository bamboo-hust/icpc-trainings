#include <bits/stdc++.h>
 
using namespace std;
 
bool check(int u, int x, int y) {
    if (u > x) return 0;
    int val = x % u;
    if (val != 0 && val != 1) {
        return 0;
    }
    int now = y - 1;
    if (val == 0) now--;
    if (u > now) return 0;
    val = now % u;
    if (val != 0 && val != 1) return 0;
    now = x - 1;
    if (val == 0) now--;
    if (u > now) return 0;
    val = now % u;
    if (val != 0 && val != 1) return 0;
    now = 
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("d.in", "r", stdin);
    int x, y;
    cin >> x >> y;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        cout << ((check(a, x, y) || check(a, y, x)) ? "YES" : "NO") << endl;
    }
    return 0;
}
