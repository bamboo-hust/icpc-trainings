#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int LOG = 42;

int has[LOG];
int n, m;
int food[N];
int mole[N];
int dp_food[N];
int dp_mole[N];

void calc(int dp[], int a[], int u) {
    if (a[u]) {
        dp[u] = 0;
    } else {
        dp[u] = N;
        for (int v = u * 2; v <= u * 2 + 1; ++v) {
            dp[u] = min(dp[u], dp[v] + 1);
        }
    }
}

void calc(int u) {
    if (f[u] < N) --has[f[u]];
    calc(dp_food, food, u);
    calc(dp_mole, mole, u);
    f[u] = N;
    if (u * 2 + 1 <= n) {
        f[u] = min(f[u], dp_mole[u * 2] + dp_food[u * 2 + 1] + 2);
        f[u] = min(f[u], dp_food[u * 2] + dp_mole[u * 2 + 1] + 2);
    }
    if (food[u]) {
        f[u] = min(f[u], dp_mole[u * 2] + 1);
        f[u] = min(f[u], dp_mole[u * 2 + 1] + 1);
    }
    if (mole[u]) {
        f[u] = min(f[u], dp_food[u * 2] + 1);
        f[u] = min(f[u], dp_food[u * 2 + 1] + 1);
    }
    if (f[u] < N) ++has[f[u]];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> food[i];
    for (int i = 1; i <= m; ++i) cin >> pos[i];

    for (int i = 1; i <= n; ++i) f[i] = N;
    for (int i = n; i >= 1; --i) {
        calc(i);
    }

    
}