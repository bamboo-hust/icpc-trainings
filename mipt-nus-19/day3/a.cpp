//
// Created by lad on 9/23/19.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const long long INF = (1ll << 60);

int n, q;
long long a[N];

struct IT {
    long long delta[N << 2], mn[N << 2], mx[N << 2];
    long long lazyMn[N << 2], lazyMx[N << 2];

    void init(int node, int l, int r) {
        delta[node] = 0;
        lazyMn[node] = INF, lazyMx[node] = -INF;
        if (l == r) {
            mn[node] = mx[node] = a[l];
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        up(node);
    }

    void up(int node) {
        mn[node] = min(mn[node << 1], mn[node << 1 | 1]);
        mx[node] = max(mx[node << 1], mx[node << 1 | 1]);
    }

    void normalize(long long &u, long long lower, long long upper) {
        u = min(u, upper);
        u = max(u, lower);
    }

//    void update(long long &u, long long &v, long long x, long long y) {
//        if (v < x) {
//            u = v = x;
//        } else if (u > y) {
//            u = v = y;
//        } else {
//            u = max(u, x);
//            v = min(v, y);
//        }
//    }

    void down(int node) {
        mn[node << 1] += delta[node];
        mn[node << 1 | 1] += delta[node];
        mx[node << 1] += delta[node];
        mx[node << 1 | 1] += delta[node];

        normalize(mn[node << 1], lazyMx[node], lazyMn[node]);
        normalize(mn[node << 1 | 1], lazyMx[node], lazyMn[node]);
        normalize(mx[node << 1], lazyMx[node], lazyMn[node]);
        normalize(mx[node << 1 | 1], lazyMx[node], lazyMn[node]);


        lazyMx[node << 1] += delta[node];
        lazyMx[node << 1 | 1] += delta[node];
        lazyMn[node << 1] += delta[node];
        lazyMn[node << 1 | 1] += delta[node];


        normalize(lazyMn[node << 1], lazyMx[node], lazyMn[node]);
        normalize(lazyMn[node << 1 | 1], lazyMx[node], lazyMn[node]);
        normalize(lazyMx[node << 1], lazyMx[node], lazyMn[node]);
        normalize(lazyMx[node << 1 | 1], lazyMx[node], lazyMn[node]);

        delta[node << 1] += delta[node];
        delta[node << 1 | 1] += delta[node];
//
//        update(lazyMx[node << 1], lazyMn[node << 1], lazyMx[node], lazyMn[node]);
//        update(lazyMx[node << 1 | 1], lazyMn[node << 1 | 1], lazyMx[node], lazyMn[node]);

        delta[node] = 0;
        lazyMn[node] = INF, lazyMx[node] = -INF;
    }

    void add(int node, int l, int r, int x, int y, long long c) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            delta[node] += c;
            mn[node] += c;
            mx[node] += c;
            lazyMn[node] += c;
            lazyMx[node] += c;
            return;
        }
        down(node);
        int m = l + r >> 1;
        add(node << 1, l, m, x, y, c);
        add(node << 1 | 1, m + 1, r, x, y, c);
        up(node);
    }

    void updateMin(int node, int l, int r, int x, int y, long long c) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            mn[node] = min(mn[node], c);
            mx[node] = min(mx[node], c);
            lazyMn[node] = min(lazyMn[node], c);
            lazyMx[node] = min(lazyMx[node], c);
            return;
        }
        down(node);
        int m = l + r >> 1;
        updateMin(node << 1, l, m, x, y, c);
        updateMin(node << 1 | 1, m + 1, r, x, y, c);
        up(node);
    }

    void updateMax(int node, int l, int r, int x, int y, long long c) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            mn[node] = max(mn[node], c);
            mx[node] = max(mx[node], c);
            lazyMn[node] = max(lazyMn[node], c);
            lazyMx[node] = max(lazyMx[node], c);
            return;
        }
        down(node);
        int m = l + r >> 1;
        updateMax(node << 1, l, m, x, y, c);
        updateMax(node << 1 | 1, m + 1, r, x, y, c);
        up(node);
    }

    pair<long long, long long> get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return {INF, -INF};
        if (x <= l && r <= y) return {mn[node], mx[node]};
        down(node);
        int m = l + r >> 1;
        pair<long long, long long> p1 = get(node << 1, l, m, x, y);
        pair<long long, long long> p2 = get(node << 1 | 1, m + 1, r, x, y);
        p1.first = min(p1.first, p2.first);
        p1.second = max(p1.second, p2.second);
        return p1;
    }
} it;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    it.init(1, 1, n);
    while (q--) {
        int op;
        cin >> op;

        int l, r;
        long long c;

        if (op == 1) {
            cin >> l >> r >> c;
            it.add(1, 1, n, l, r, c);

        } else if (op == 2) {
            cin >> l >> r >> c;
            it.updateMin(1, 1, n, l, r, c);


        } else if (op == 3) {
            cin >> l >> r >> c;
            it.updateMax(1, 1, n, l, r, c);

        } else {
            cin >> l >> r;
            pair<long long, long long> res = it.get(1, 1, n, l, r);
            cout << res.first << ' ' << res.second << '\n';

        }

    }
    return 0;
}