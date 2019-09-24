#include <bits/stdc++.h>

using namespace std;

const int N = 1024;
const int V = 1e5 + 5;

int a[N];
int n;
vector<int> pos[N];
int cnt[V];

int dp[N][N];

int main() {
    ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; ++i) {
            pos[a[i]].push_back(i);
        }
        memset(dp, 0, sizeof dp);
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                if (cnt[a[j]]) break;
                cnt[a[j]]++;
                dp[i][j] = j - i + 1;
            }
            for (int j = i; j <= n; ++j) {
                cnt[a[j]] = 0;
            }
        }

        for (int i = n; i >= 1; --i) {
            for (int j = i; j <= n; ++j) {
                if (!dp[i][j]) {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        int res = 0;
        set< pair<int, int> > ranges;
        multiset< int > vals;
        for (int i = 1; i <= n; ++i) {
            ranges.clear();
            ranges.insert(make_pair(1, n));
            vals.clear();
            vals.insert(dp[1][n]);

            set<int> erased;
            for (int j = i; j <= n; ++j) {
                if (erased.count(a[j])) break;
                erased.insert(a[j]);
                for (int p : pos[a[j]]) {
                    auto it = ranges.upper_bound(make_pair(p + 1, 0));
                    if (it == ranges.begin()) continue;
                    --it;
                    int l = it->first;
                    int r = it->second;
                    if (l <= p && p <= r) {
                        vals.erase(vals.find(dp[l][r]));
                        ranges.erase(it);
                        if (l < p) {
                            ranges.insert(make_pair(l, p - 1));
                            vals.insert(dp[l][p - 1]);
                        }
                        if (p < r) {
                            ranges.insert(make_pair(p + 1, r));
                            vals.insert(dp[p + 1][r]);
                        }
                    }
                }
                //for (auto it : ranges) cerr << it.first << ' ' << it.second << ' ' << dp[it.first][it.second] << endl;
                //for (auto it : vals) cerr << it << ' '; cerr << endl;
                res = max(res, j - i + 1 + (vals.empty() ? 0 : (*vals.rbegin())));
            }
        }

        for (int i = 1; i <= n; ++i) {
            pos[a[i]].clear();
        }

        cout << "Case #" << tc << ": " << res << '\n';
    }

    return 0;
}