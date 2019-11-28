#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        map<int, int> cnt;
        int64_t res = 0;
        for (int j = 1; j < n; ++j) {
            cnt[a[j - 1]]++;
            for (int k = j + 1; k < n; ++k) {
                int ai = a[j] + a[j] - a[k];
                if (cnt.count(ai)) {
                    res += cnt[ai];
                }
            }
        }
        cout << res << '\n';
    }
    return 0;
}