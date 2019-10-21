#include <bits/stdc++.h>

using namespace std;
#define double long double

int const N = 3e5 + 5;
double const MAX = 1e300 + 1;

vector < int > a[N];

double dp[N], sum[N];
int deg[N], cnt_visited[N], ok[N];



int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        dp[i] = MAX;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
        deg[v]++;
        deg[u]++;
    }

    priority_queue < pair < double, int > > que;
    dp[n] = 0;

    que.push(make_pair(0, n));
    while (!que.empty()) {
        pair < double, int > p = que.top(); que.pop();
        int u = p.second;
        if (-p.first != dp[p.second] || ok[u]) {
            continue;
        }
        ok[u] = 1;

        for (int v : a[u]) {
            double sum_cur = (sum[v] + dp[u] + 1);
            int cnt_cur = cnt_visited[v] + 1;
            if (dp[v] > (sum_cur + deg[v] - cnt_cur) / cnt_cur) {
                dp[v] = (sum_cur + deg[v] - cnt_cur) / cnt_cur;
                sum[v] = sum_cur;
                cnt_visited[v] = cnt_cur;
                que.push(make_pair(-dp[v], v));
            }
        }
    }

//    printf("%0.10Lf\n", dp[1]);
    cout << setprecision(10) << fixed << dp[1] << endl;
}