#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

long long f2[N];
long long f3[N];
long long sz[N];
int n;
vector<int> a[N];

void dfs1(int u, int p) {
    sz[u] = 1;
    for (int v : a[u]) if (v != p) {
        dfs1(v, u);
        sz[u] += sz[v];
    }
}

void dfs2(int u, int p) {
    long long pref = 0;
    for (int v : a[u]) if (v != p) {
        dfs2(v, u);
        f2[u] += f2[v];
        f2[u] += pref * sz[v];
        pref += sz[v];
    }
}

void dfs3(int u, int p) {
    long long pref = 0;
    long long pref2 = 0;
    long long pref_sz = 0;
    for (int v : a[u]) if (v != p) {
        dfs3(v, u);
        f3[u] += f3[v];
        f3[u] += pref * sz[v];
        f3[u] += pref2 * sz[v];
        f3[u] += pref_sz * f2[v];
        f3[u] += f2[v];
        pref += f2[v];
        pref2 += pref_sz * sz[v];
        pref_sz += sz[v];
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    dfs3(1, 0);
    cout << f3[1] << endl;
}