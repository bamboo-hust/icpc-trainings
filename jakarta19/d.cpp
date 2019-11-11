#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int CHAR = 26;
const int SZ = 510;

int r, c, q;
char a[SZ][SZ];
int node[N];
int curNode[SZ][SZ];

struct AC {
    int nxt[CHAR][N];
    int cnt;
    int link[N];
    int len[N];
    long long sum[N];
    long long sum2[N];
    vector<int> adj[N];

    AC() {
        cnt = 0;
        memset(nxt, -1, sizeof nxt);
        memset(link, -1, sizeof link);
        memset(len, 0, sizeof len);
    }

    int add(const string &u) {
        int cur = 0;
        for (char v : u) {
            int id = v - 'A';
            if (nxt[id][cur] == -1) {
                nxt[id][cur] = ++cnt;
                len[cnt] = len[cur] + 1;
            }
            cur = nxt[id][cur];
        }
        return cur;
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < CHAR; i++) {
                int to = (u == 0 ? 0 : nxt[i][link[u]]);
                if (nxt[i][u] == -1) nxt[i][u] = to;
                else {
                    link[nxt[i][u]] = to;
                    adj[link[nxt[i][u]]].push_back(nxt[i][u]);
                    q.push(nxt[i][u]);
                }
            }
        }
    }

    void dfs(int u) {
        for (int v : adj[u]) {
            dfs(v);
            sum[u] += sum[v];
        }
    }

    void solve() {
        dfs(0);
    }
} ac;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> r >> c >> q;
    for (int i = 1; i <= r; i++) {
        cin >> (a[i] + 1);
    }
    for (int i = 1; i <= q; i++) {
        string u;
        cin >> u;
        node[i] = ac.add(u);
    }
    ac.build();
    for (int i = 1; i <= r; i++) {
        curNode[i][1] = ac.nxt[a[i][1] - 'A'][0];
        for (int k = 2; k <= c; k++) {
            curNode[i][k] = ac.nxt[a[i][k] - 'A'][curNode[i][k - 1]];
        }
        for (int j = i + 1; j <= r; j++) {
            for (int k = 1; k <= c; k++) {
                curNode[j][k] = ac.nxt[a[j][k] - 'A'][curNode[j - 1][k]];
            }
        }

        for (int j = i; j <= r; j++) {
            for (int k = 1; k <= c; k++) {
                ac.sum[curNode[j][k]]++;
            }
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int k = 1; k <= c; k++) {
            int cur = 0;
            for (int j = i; j <= r; j++) {
                int nxt = ac.nxt[a[j][k] - 'A'][cur];
                if (ac.len[nxt] <= ac.len[cur]) break;
                cur = nxt;
                ac.sum2[cur] -= (i - 1);
            }
        }
    }
    ac.solve();
    for (int i = 1; i <= q; i++) {
        cout << ac.sum[node[i]] + ac.sum2[node[i]] << '\n';
    }
    return 0;
}