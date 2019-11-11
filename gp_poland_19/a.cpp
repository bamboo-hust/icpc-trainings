#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        long long k;
        cin >> n >> k;
        multiset<long long> s;
        long long tot = 0;
        for (int i = 1; i <= n; i++) {
            long long u;
            cin >> u;
            s.insert(u);
            tot += u;
        }
        int res = 0;
        while (k < tot) {
            auto it = s.upper_bound(k);
            if (it == s.begin()) {
                res = -1;
                break;
            }
            res++;
            it--;
            long long now = *it;
            s.erase(s.find(now));
            k += now;
            tot -= now;
        }
        cout << res << '\n';
    }
    return 0;  
}