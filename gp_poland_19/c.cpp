#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        vector<long long> sum(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a.begin() + 1, a.end());
        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + a[i];
        }
        int res = -1;
        for (int i = 3; i <= n; i++) {
            if (a[i] < sum[i - 1]) res = i;
        }
        if (res == -1) cout << 0 << '\n';
        else cout << sum[res] << '\n';
    }
    return 0;
}