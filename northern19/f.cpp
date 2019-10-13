#include <bits/stdc++.h>

using namespace std;

int const N = 1e3 + 5;
long long const MAX = 4000000000000000005LL;
int const MOD = 1e9;

struct Edge
{
    int u, v;
    long long w;
    Edge(){};
    Edge(int _u, int _v, long long _w) {
        u = _u; v = _v; w = _w;
    }
};

Edge e[N];

long long c[N][N];
long long ans[N][N];


int main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c[i][j] = MAX;
            ans[i][j] = MAX;
        }
    }
    for (int i = 1; i <= m; i++) {
        long long u, v, w;
        cin >> u >> v >> w;
        e[i] = Edge(u, v, w); 
        c[u][v] = c[v][u] = 1;
    }

    for (int i = 1; i <= n; i++) {
        c[i][i] = 0;
    }

    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                c[u][v] = min(c[u][v], c[u][k] + c[k][v]);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int u = e[i].u;
        int v = e[i].v;
        long long w = e[i].w;
        for (int x = 1; x <= n; x++) {
            for (int y = x + 1; y <= n; y++) {
                if (c[u][x] != MAX && c[v][y] != MAX) {
                    ans[x][y] = min(ans[x][y], 1ll * (c[u][x] + c[v][y] + 1) * w);
                }
                if (c[u][y] != MAX && c[v][x] != MAX) {
                    ans[x][y] = min(ans[x][y], 1ll * (c[v][x] + c[u][y] + 1) * w);
                }
            }
        }
    }

    long long res = 0;
    long long sum = 0;
    bool flag = false;
    for (int x = 1; x <= n; x++) {
        for (int y = x + 1; y <= n; y++) {
            if (ans[x][y] == MAX) {
                continue;
            }
            sum = sum + ans[x][y];
            if (sum >= MOD) {
                flag = true;
                sum = 0;
            }
            res = (res + ans[x][y]) % MOD;
        }
    }

    if (flag) {
        cout << setw(9) << setfill('0') << res << endl;
    } else {
        cout << res << endl;
    }
}