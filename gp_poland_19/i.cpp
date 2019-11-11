#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n;
int res;
int a[N];
vector<pair<int, int>> adj[N];
int root[N];
string ans;
int used[N];
int c[N];

bool inside(int u) {
    return u >= 1 && u <= n;
}

void addEdge(int u, int v, int w) {
    if (inside(u) && inside(v)) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        return;
    }
    if (w == 0) {
        res = 0;
    }
}

void dfs(int u, int color, int r) {
    root[u] = r;
    used[u] = color;
    for (auto val : adj[u]) {
        int v = val.first;
        int w = val.second;
        if (used[v] == -1) {
            dfs(v, color ^ w, r);
        } else {
            if (used[v] != color ^ w) res = 0;
        }
    }
}

void go(int u, const vector<int> roots) {
    if (u >= roots.size()) {
        for (int i = 1; i <= n; i++) {
            ans[i - 1] = (char)('0' + (used[i] ^ c[root[i]]));
        }
        cout << ans << '\n';
        return;
    }       
    c[roots[u]] = 0;
    go(u + 1, roots);
    c[roots[u]] = 1;
    go(u + 1, roots);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;

        for (int i = 1; i <= n; i++) adj[i].clear();
        ans = "";
        for (int i = 1; i <= n; i++) {
            used[i] = -1;
            ans += '0';
        }

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        res = 1;
        pair<int, int> curMax(0, 0);
        for (int i = 1; i <= n; i++) {
            int curRange = 0;
            if (i <= curMax.first + curMax.second) {
                int id = curMax.first * 2 - i;
                if (id < 1 || id >= i) {
                    res = 0;
                    break;
                }
                curRange = a[id];
                curRange = min(curRange, curMax.first + curMax.second - i);
            }
            if (curRange > a[i]) {
                res = 0;
                break;
            }
            for (int j = curRange + 1; j <= a[i]; j++) {
                if (i + j <= curMax.first + curMax.second) {
                    res = 0;
                    break;
                }
                addEdge(i - j, i + j, 0);
            }
            addEdge(i - a[i] - 1, i + a[i] + 1, 1);
            if (curMax.first + curMax.second < i + a[i]) {
                curMax = {i, a[i]};
            }
        }
        vector<int> roots;
        for (int i = 1; i <= n; i++) {
            if (used[i] >= 0) continue;
            roots.push_back(i);
            res *= 2;
            dfs(i, 0, i);
        }
        cout << res << '\n';
        if (res > 0) {
            go(0, roots);
        }
    }
    return 0;
}