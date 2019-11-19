#include <bits/stdc++.h>

using namespace std;
int const N = 1e3 + 5;

int n;
vector < int > a[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n * (n - 1) / 2; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        a[u].push_back(w);
        a[v].push_back(w);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        sort(a[i].begin(), a[i].end());
        for (int j = 1; j < n; j += 2) {
            ans += a[i][j];
        }
    }
    cout << ans << endl;
}