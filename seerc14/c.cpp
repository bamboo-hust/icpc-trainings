#include <bits/stdc++.h>

using namespace std;

struct IT {
    vector<int> a;
    int n;

    IT() {}
    IT(int n) {
        this->n = n;
        a.resize(n * 4 + 1);
    }

    void init(int k, int l, int r, const vector<int64_t> &v) {
        if (l == r) {
            a[k] = v[l];
            return;
        }
        init(k * 2, l, l + r >> 1, v);
        init(k * 2 + 1, (l + r >> 1) + 1, r, v);
        a[k] = max(a[k * 2], a[k * 2 + 1]);
    }

    void init(const vector<int64_t> &v) {
        init(1, 1, n, v);
    }

    void update(int k, int l, int r, int i, int v) {
        if (r < i || i < l) return;
        if (l == r) {
            a[k] = v;
            return;
        }
        update(k * 2, l, l + r >> 1, i, v);
        update(k * 2 + 1, (l + r >> 1) + 1, r, i, v);
        a[k] = max(a[k * 2], a[k * 2 + 1]);
    }

    void update(int i, int v) {
        update(1, 1, n, i, v);
    }

    int get_prefix(int k, int l, int r, int low) {
        if (a[k] < low) return 0;
        if (l == r) return l;
        if (a[k * 2] >= low) return get_prefix(k * 2, l, l + r >> 1, low);
        return get_prefix(k * 2 + 1, (l + r >> 1) + 1, r, low);
    }

    int get_prefix(int low) {
        return get_prefix(1, 1, n, low);
    }

    int get_suffix(int k, int l, int r, int low) {
        if (a[k] < low) return 0;
        if (l == r) return l;
        if (a[k * 2 + 1] >= low) return get_suffix(k * 2 + 1, (l + r >> 1) + 1, r, low);
        return get_suffix(k * 2, l, (l + r >> 1), low);
    }

    int get_suffix(int low) {
        return get_suffix(1, 1, n, low);
    }
};

int n, m, R, K, P;
vector< vector<int64_t> > a;

vector<IT> row;
vector<IT> col;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    freopen("c.in", "r", stdin);
    cin >> n >> m >> R >> K >> P;
    a.resize(n + 1);
    a[0].resize(m + 1);
    for (int i = 1; i <= n; ++i) {
        a[i].resize(m + 1);
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    row.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        row[i] = IT(m);
        row[i].init(a[i]);
    }

    col.resize(m + 1);
    for (int i = 1; i <= m; ++i) {
        vector<int64_t> temp(n + 1);
        for (int j = 1; j <= n; ++j) temp[j] = a[j][i];
        col[i] = IT(n);
        col[i].init(temp);
    }

    for (int it = 1; it <= K; ++it) {
        char dir;
        int i, low;
        cin >> dir >> i >> low;
        if (dir == 'W' || dir == 'E') {
            vector<int> changed;
            for (int t = 0; t < R; ++t) {
                int pos = dir == 'W' ? row[i].get_prefix(low) : row[i].get_suffix(low);
                if (!pos) break;
                a[i][pos]--;
                changed.push_back(pos);
                row[i].update(pos, 0);
            }
            for (int pos : changed) {
                row[i].update(pos, a[i][pos]);
                col[pos].update(i, a[i][pos]);
            }
        }
        if (dir == 'N' || dir == 'S') {
            vector<int> changed;
            for (int t = 0; t < R; ++t) {
                int pos = dir == 'N' ? col[i].get_prefix(low) : col[i].get_suffix(low);
                if (!pos) break;
                a[pos][i]--;
                changed.push_back(pos);
                col[i].update(pos, 0);
            }
            for (int pos : changed) {
                col[i].update(pos, a[pos][i]);
                row[pos].update(i, a[pos][i]);
            }
        }
    }

    int64_t res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            a[i][j] += a[i - 1][j];
            a[i][j] += a[i][j - 1];
            a[i][j] -= a[i - 1][j - 1];
            if (i >= P && j >= P) {
                res = max(res, a[i][j] - a[i - P][j] - a[i][j - P] + a[i - P][j - P]);
            }
        }
    }

    cout << res << endl;
}