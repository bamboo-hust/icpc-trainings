#include <bits/stdc++.h>

using namespace std;

const int N = 4096;

const int BASE = 3;
const int MX = 1e9 + 3;
const int MY = 1e9 + 7;

vector<int> a[N];
int n;

int sz[N];
int root;

void dfs_size(int u, int p) {
    sz[u] = 1;
    bool can_be_root = a[u].size() > 1;
    int each = (n - 1) / a[u].size();
    for (int v : a[u]) if (v != p) {
        dfs_size(v, u);
        sz[u] += sz[v];
        if (sz[v] != each) can_be_root = false;
    }
    if (p != 0 && (n - sz[u]) != each) can_be_root = false;
    if (can_be_root) {
        //cerr << "can_be_root " << u << ' ' << each << endl;
        assert(root == 0);
        root = u;
    }
}

struct Hash {
    int x, y;
    int len;

    bool operator < (const Hash &o) const {
        if (len != o.len) return len < o.len;
        if (x != o.x) return x < o.x;
        return y < o.y;
    }

    bool operator == (const Hash &o) const {
        return !(*this < o) && !(o < *this);
    }
};

Hash power[N];

Hash operator * (const Hash &a, int b) {
    return Hash{1LL * a.x * b % MX, 1LL * a.y * b % MY, a.len + 1};
}

Hash operator * (const Hash &a, const Hash &b) {
    return Hash{1LL * a.x * b.x % MX, 1LL * a.y * b.y % MY, a.len + b.len};
}

Hash operator + (const Hash &a, const Hash &b) {
    return Hash{(a.x + b.x) % MX, (a.y + b.y) % MY, a.len};
}

void init_hash() {
    power[0] = Hash{1, 1, 0};
    for (int i = 1; i < N; ++i) {
        power[i] = power[i - 1] * BASE;
    }
}

struct AHU {
    vector<int> centers;
    vector<Hash> H;

    int pre[N];

    int last_node;
    int best_len;

    void dfs_find(int u, int p, int depth) {
        if (depth > best_len) {
            best_len = depth;
            last_node = u;
        }
        for (int v : a[u]) if (v != p) {
            pre[v] = u;
            dfs_find(v, u, depth + 1);
        }
    }

    vector<int> find_longest(int from) {
        last_node = 0;
        best_len = 0;
        dfs_find(from, 0, 1);
        vector<int> res;
        for (int u = last_node; u != from; u = pre[u]) {
            res.push_back(u);
        }
        res.push_back(from);
        reverse(begin(res), end(res));
        return res;
    }

    Hash calc(int u, int p) {
        vector<Hash> child;
        for (int v : a[u]) if (v != p) {
            child.push_back(calc(v, u));
        }
        sort(begin(child), end(child));
        Hash res {1, 1, 1};
        for (Hash v : child) {
            res = res * power[v.len] + v;
        }
        res = res * BASE + Hash{2, 2, 1};
        return res;
    }

    AHU(int root) {
        vector<int> path = find_longest(root);
        path = find_longest(path.back());
        centers.push_back(path[path.size() / 2]);
        if (path.size() - 1 - path.size() / 2 != path.size() / 2) {
            centers.push_back(path[path.size() - 1 - path.size() / 2]);
        }
/*
        cerr << "centers ";
        for (int u : centers) cerr << u << ' '; cerr << endl;
*/
        for (int i = 0; i < centers.size(); ++i) {
            H.push_back(calc(centers[i], 0));
//            cerr << "Hash " << H.back().x << endl;
        }
    }

    bool equals(const AHU &o) {
        if (centers.size() != o.centers.size()) return false;
        for (Hash u : H) {
            for (Hash v : o.H) {
                if (u == v) return true;
            }
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    init_hash();

    dfs_size(1, 0);

    if (root == 0) {
        cout << -1 << endl;
        return 0;
    }

    for (int v : a[root]) {
        a[v].erase(find(begin(a[v]), end(a[v]), root));
    }

    vector<AHU> forest;

    for (int v : a[root]) {
        forest.push_back(AHU(v));
    }

    for (int i = 1; i < forest.size(); ++i) {
        if (!forest[i].equals(forest[i - 1])) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << a[root].size() << endl;
}