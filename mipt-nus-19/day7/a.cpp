#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int T[N], C[N];
int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> T[i];
    for (int i = 1; i <= n; ++i) cin >> C[i];
    bool has_odd = false;
    for (int i = 1; i <= n; ++i) {
        has_odd |= C[i] & 1;
    }
    for (int i = 1; i <= q; ++i) {
        int x; cin >> x;
        if (x <= 0) {
            cout << "NO\n";
        } else {
            if (has_odd) {
                cout << "YES\n";
            } else {
                cout << (x % 2 ? "NO" : "YES") << '\n';
            }
        }
    }
}