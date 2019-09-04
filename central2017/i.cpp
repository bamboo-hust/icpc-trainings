#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N];
int b[N];

int main() {
    int T; cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int j = 1; j <= n; ++j) cin >> b[j];
        int ans = 0;
        bool has_other = false;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 0 || b[i] == 0) {
                ans += 1;
            } else {
                has_other = 1;
            }
        }
        ans += has_other;
        cout << ans << '\n'
    }
}