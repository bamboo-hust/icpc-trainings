#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 6;

vector<int> a[N];
int sz[N];
int cnt[N];
int n;

void dfs(int u, int p = 0) {
    sz[u] = 1;
    for (int v : a[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    cnt[sz[u]]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1);
    for (int k = 1; k < n; ++k) if (n % (k + 1) == 0){
        int each = n / (k + 1);
        int cur = 0;
        for (int i = each; i <= n; i += each) {
            cur += cnt[i];
        }
        //cerr << k << ' ' << each << ' ' << cur << endl;
        if (cur >= k + 1) {
            cout << k << ' ';
        }
    }
    cout << endl;
}