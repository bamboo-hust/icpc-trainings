#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOG = 20;
const long long INF = 1e18;

int n;
int x[N], t[N], id[N], pos[N];
long long dp[N];
int eventT[N];

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

pair<int, int> getEvent(int u, int v) {
    int low = 0, high = u + 1;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (getVal(u, mid) >= getVal(v, mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    eventT[u] = high;
    return {high, u};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        init();
        root[0] = init(1, n);
        for (int i = 1; i <= n; i++) {
            cin >> x[i] >> t[i];
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

        set<int> s;
        set<pair<int, int>> events;

        for (int i = 1; i <= n; i++) s.insert(i);
        for (int i = 1; i < n; i++) {
            events.insert(getEvent(i, i + 1));
        }
        dp[0] = 0;

        auto updateSet = [&](int u) {
            auto it = s.find(u);
            int pre = -1, suf = -1;
            if (it != s.begin()) {
                auto itpre = it;
                itpre--;
                pre = *itpre;
            }
            auto itsuf = it;
            itsuf++;
            if (itsuf != s.end()) suf = *itsuf;
            s.erase(u);
            if (pre != -1) {    
                events.erase({eventT[pre], pre});
                if (suf != -1) events.insert(getEvent(pre, suf));
            }
        };

        for (int i = 1; i <= n; i++) {
            while (!events.empty()) {
                auto u = *events.begin();
                if (u.first > i) break;
                events.erase(u);
                if (u.first < i) break;
                updateSet(u.second);
            }
            dp[i] = getVal(*s.begin(), i);
        }
        //
        int q;
        cin >> q;
        for (int i = 1; i <= q; i++) {
            long long u;
            cin >> u;
            cout << upper_bound(dp, dp + n + 1, u) - dp - 1 << ' ';
            cout << '\n'; 
        }
    }
    return 0;
}