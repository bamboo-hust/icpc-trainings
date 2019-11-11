#include <bits/stdc++.h>

using namespace std;

int const MAX = 1e9 + 5;

int const N = 1e5 + 5;

long long tree[4 * N], cnt[4 * N], a[N], n, m, q;
vector < int > b[N];


void update(int node, int l, int r, int pos, int val) {
    if (l > pos || r < pos) {
        return;
    }
    if (l == r) {
        cnt[node] += val;
        return;
    }
    int mid = (l + r) >> 1;
    update(node * 2, l, mid, pos, val);
    update(node * 2 + 1, mid + 1, r, pos, val);
    tree[node] = min(tree[2 * node], tree[2 * node + 1] - cnt[2 * node]);
    cnt[node] = cnt[2 * node] + cnt[2 * node + 1];
}

void add(int id, int val) {
    val = (int)(val >= a[1]);
    update(1, 1, m, id, val);
}

void del(int id, int val) {
    val = -(int)(val >= a[1]);
    update(1, 1, m, id, val);
}

void init_tree(int node, int l, int r) {
    if (l == r) {
        for (int v : b[l]) {
            cnt[node] += (v >= a[1]);
        }
        tree[node] = n - (b[l].size() - 1);
        return;
    }
    int mid = (l + r) >> 1;
    init_tree(node * 2, l, mid);
    init_tree(node * 2 + 1, mid + 1, r);
    tree[node] = min(tree[2 * node], tree[2 * node + 1] - cnt[2 * node]);
    cnt[node] = cnt[2 * node] + cnt[2 * node + 1];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> q;
    int origin_rank = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        origin_rank += a[i] >= a[1];
    }


    for (int i = 1; i <= m; i++) {
        int size;
        cin >> size;
        b[i].resize(size + 1);
        for (int j = 1; j <= size; j++) {
            cin >> b[i][j];
        }
    }

    init_tree(1, 1, m);

    for (int i = 1; i <= q; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        del(x, b[x][y]);
        b[x][y] = z;
        add(x, b[x][y]);
        if (origin_rank <= tree[1]) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}