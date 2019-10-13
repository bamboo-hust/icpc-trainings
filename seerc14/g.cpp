#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
const int CHAR = 26;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

string s;
int n;
vector<pair<int, int>> rules[CHAR];
int dp[N][N];
int used[N][N];
int mask[CHAR];
vector<int> ls[N];

int go(int id, int l, int r) {
    // cerr << "inside " << id << ' ' << l << ' ' << r << endl;
    if ((double)clock() / CLOCKS_PER_SEC >= 1.95) {
        cout << 0 << endl;
        exit(0);
    }
    // if (used[l][r] >> id & 1) {
    //     if (l == 3 && r == 3 && id == 3) cout << "val " << (dp[l][r] >> id & 1) << endl;
    //     return (dp[l][r] >> id & 1);
    // }
    used[l][r] |= (1 << id);
    int res = 0;
    if (l == r) {
        res = (mask[id] >> (s[l] - 'a') & 1);
    }
    else {
        for (auto rule : rules[id]) {
            if (res) break;
            for (int delta : ls[r - l]) {
                int k = l + delta;
                if (k - l + 1 < r - k) {
                    int foo = go(rule.first, l, k);
                    if (!foo) continue;
                    foo = go(rule.second, k + 1, r);
                    if (foo) {
                        // cout << id << ' ' << l << ' ' << k << ' ' << r << endl;
                        res = 1;
                        break;
                    }
                } else {
                    int foo = go(rule.second, k + 1, r);
                    if (!foo) continue;
                    foo = go(rule.first, l, k);
                    // cout << id << ' ' << l << ' ' << k << ' ' << r << endl;
                    if (foo) {
                        res = 1;
                        break;
                    }
                }
            }
        }
    }
    // cerr << "inside " << id << ' ' << l << ' ' << r << ' ' << res << endl;
    if (res) dp[l][r] |= (1 << id);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("g.in", "r", stdin);
    memset(dp, -1, sizeof dp);
    cin >> s;
    n = s.size();
    string foo;
    while (cin >> foo) {
        if (foo.size() == 2) {
            int id = foo[0] - 'A';
            int terChar = foo[1] - 'a';
            mask[id] |= (1 << terChar);
            // cerr << "added " << id << ' ' << terChar << endl;
        } else {
            int id = foo[0] - 'A';
            int u = foo[1] - 'A';
            int v = foo[2] - 'A';
            rules[id].push_back({u, v});
        }
    }
    for (int i = 0; i < CHAR; i++) {
        shuffle(rules[i].begin(), rules[i].end(), rng);
    }
    for (int i = 1; i <= n; i++) {
        ls[i].resize(i);
        for (int j = 0; j < i; j++) {
            ls[i][j] = j;
        }
        // shuffle(ls[i].begin(), ls[i].end(), rng);
    }
    cout << go('S' - 'A', 0, n - 1) << endl;
    return 0;
}