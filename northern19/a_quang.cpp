#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOG = 20;
const long long INF = 1e18;

int n;
int x[N], t[N], id[N], pos[N];
long long dp[N];

struct Node {
    int l, r, cnt;
    long long sum;
    Node(int l = -1, int r = -1, int cnt = 0, long long sum = 0) : l(l), r(r), cnt(cnt), sum(sum) {}
} node[N * 4 + N * LOG];

int root[N], cnt;

void init() {
    cnt = 0;
}

int init(int l, int r) {
    int newNode = cnt++;
    node[newNode] = Node();
    if (l < r) {
        int m = l + r >> 1;
        node[newNode].l = init(l, m);
        node[newNode].r = init(m + 1, r);
    }
    return newNode;
}

void up(int u) {
    int l = node[u].l;
    int r = node[u].r;
    node[u].cnt = node[l].cnt + node[r].cnt;
    node[u].sum = node[l].sum + node[r].sum;
}

int update(int cur, int l, int r, int x) {
    int newNode = cnt++;
    node[newNode] = node[cur];
    if (l == r) {
        node[newNode].cnt = 1;
        node[newNode].sum = t[id[x]];
        return newNode;
    }
    int m = l + r >> 1;
    if (x <= m) {
        node[newNode].l = update(node[cur].l, l, m, x);
    } else {
        node[newNode].r = update(node[cur].r, m + 1, r, x);
    }
    up(newNode);
    return newNode;
}

long long get(int cur, int l, int r, int k) {
    if (node[cur].cnt < k) return INF;
    if (k == 0) return 0ll;
    if (l == r) return node[cur].sum;
    int m = l + r >> 1;
    int p1 = node[cur].l;
    int p2 = node[cur].r;
    if (node[p1].cnt >= k) return get(p1, l, m, k);
    return node[p1].sum + get(p2, m + 1, r, k - node[p1].cnt);
}

long long getVal(int u, int k) {
    return 1ll * x[u] + get(root[u], 1, n, k);
}

void go(int l, int r, int optL, int optR) {
    int m = l + r >> 1;
    int optM = optL;
    long long now = getVal(optM, m);
    for (int i = max(optL, m - 1) + 1; i <= optR; i++) {
        long long cur = getVal(i, m);
        if (cur < now) {
            now = cur;
            optM = i;
        }
    }
    dp[m] = now;
    if (l < m) go(l, m - 1, optL, optM);
    if (r > m) go(m + 1, r, optM, optR);
}

int nextInt() {
    char u = getchar();
    while (!isdigit(u)) u = getchar();
    int res = 0;
    while (isdigit(u)) {
        res = res * 10 + u - '0';
        u = getchar();
    }
    return res;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    int tc;
    // cin >> tc;
    tc = nextInt();
    while (tc--) {
        // cin >> n;
        n = nextInt();
        init();
        root[0] = init(1, n);
        for (int i = 1; i <= n; i++) {
            // cin >> x[i] >> t[i];
            x[i] = nextInt();
            t[i] = nextInt();
            id[i] = i;
        }
        sort(id + 1, id + n + 1, [](int u, int v) {
            return t[u] < t[v];
        });
        for (int i = 1; i <= n; i++) {
            pos[id[i]] = i;
        }
        for (int i = 1; i <= n; i++) {
            root[i] = update(root[i - 1], 1, n, pos[i]);
        }

        dp[0] = 0;
        go(1, n, 1, n);

        int q;
        cin >> q;
        for (int i = 1; i <= q; i++) {
            long long u;
            cin >> u;
            cout << upper_bound(dp, dp + n + 1, u) - dp - 1 << ' ';
        }
        cout << '\n'; 
    }
    return 0;
}