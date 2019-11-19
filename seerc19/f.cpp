#include <bits/stdc++.h>
 
using namespace std;
 
 
int const N = 1e5 + 5;
 
int n, dp[N];
vector < int > a[N];
 
void dfs(int u, int pre) {
    int cnt = 0;
    int cnt_lose = 0;
    for (int v : a[u]) {
        if (v == pre) {
            continue;
        }
        dfs(v, u);
        cnt += dp[v];
        cnt_lose += dp[v] == 0;
    }
    dp[u] = (cnt >= 2) || (cnt == 0);
    if (cnt == 1) {
        dp[u] = cnt_lose > 1;
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
 
    dfs(1, 0);
    // for (int i = 1; i <= n; i++) {
    //     cout << dp[i] << endl;
    // }
    if (dp[1]) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }
}
