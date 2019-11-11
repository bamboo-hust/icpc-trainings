#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const long long INF = 1e18;

int n;
vector<int> events[N];

long long getTopThree(multiset<int> &s) {
    if (s.size() < 3) return -INF;
    int x, y, z;
    x = *s.rbegin();
    s.erase(s.find(x));
    y = *s.rbegin();
    s.erase(s.find(y));
    z = *s.rbegin();
    s.insert(x);
    s.insert(y);
    return x + y + z;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n + 1; i++) {
            events[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            int r, s;
            cin >> r >> s;
            int l = max(1, i - r);
            int x = min(n, i + r);
            events[l].push_back(s);
            events[x + 1].push_back(-s);
        }
        multiset<int> s;
        long long res = -INF;
        for (int i = 1; i <= n; i++) {
            for (int u : events[i]) {
                if (u > 0) s.insert(u);
                else s.erase(s.find(-u));
            }
            res = max(res, getTopThree(s));
        }
        cout << res << '\n';
    }
    return 0;
}