#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

int const N = 2e5 + 5;
int const MAX = 1e9 + 7;

vector < int > val;

pair < int, int > seg[N];

int a[N], tree[4 * N], lazy[4 * N];



void down(int node) {
    tree[node * 2] += lazy[node];
    tree[node * 2 + 1] += lazy[node];
    lazy[node * 2] += lazy[node];
    lazy[node * 2 + 1] += lazy[node];
    lazy[node] = 0;
}

void update(int node, int l, int r, int d, int c, int val) {
    if (l > c || r < d) {
        return;
    }
    if (d <= l && r <= c) {
        tree[node] += val;
        lazy[node] += val;
        return;
    }
    down(node);
    int mid = (l + r) >> 1;
    update(node * 2, l, mid, d, c, val);
    update(node * 2 + 1, mid + 1, r, d, c, val);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

void init(int node, int l, int r) {
    if (l == r) {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    init(node * 2, l, mid);
    init(node * 2 + 1, mid + 1, r);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}


int get_max(int node, int l, int r, int d, int c) {
    if (l > c || r < d) {
        return -MAX;
    }
    if (d <= l && r <= c) {
        return tree[node];
    }
    down(node);
    int mid = (l + r) >> 1;
    return max(get_max(node * 2, l, mid, d, c), get_max(node * 2 + 1, mid + 1, r, d, c));
}

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        seg[i] = make_pair(y2, y1);
        val.push_back(y1);
        val.push_back(y2);
    }
    val.push_back(-MAX);
    sort(val.begin(), val.end());
    val.resize(unique(val.begin(), val.end()) - val.begin());
    int size = val.size();
    for (int i = 1; i <= n; i++) {
        seg[i].f = lower_bound(val.begin(), val.end(), seg[i].f) - val.begin();
        seg[i].s = lower_bound(val.begin(), val.end(), seg[i].s) - val.begin();
        a[seg[i].f]++;
        a[seg[i].s + 1]--;
    }

    sort(seg + 1, seg + n + 1);

    for (int i = 1; i <= size; i++) {
        a[i] += a[i - 1];
    }

    init(1, 1, size);

    int pos = 1, ans = 0;
    for (int i = 1; i <= size; i++) {
        while (pos <= n && seg[pos].f <= i) {
//            cout << i << " " << seg[pos].f << " " << seg[pos].s << endl;
            update(1, 1, size, i, seg[pos].s, -1);
            pos++;
        }

//        cout << a[i] + get_max(1, 1, size, i + 1, size) << endl;
        ans = max(ans, a[i] + get_max(1, 1, size, i + 1, size));
    }

    cout << ans << endl;

}