#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, m;
char a[N][N];
int x, y;
vector<int> ls[N];
pair<int, int> upper[N], lower[N];

struct Res {
    int area, x, xx, y, yy;
    bool operator < (const Res &u) const {
        return area < u.area;
    }
};

vector<int> cur[N];

void color(char c, int x, int xx, int y, int yy) {
    for (int i = x; i <= xx; i++) {
        for (int j = y; j <= yy; j++) {
            if (a[i][j] == '.') a[i][j] = c - 'A' + 'a';
        }
    }
}

void solve(int x, int xx, int y, int yy) {
    if (x > xx || y > yy) return;
    for (int i = x; i <= xx; i++) cur[i].clear();
    vector<int> id;
    for (int i = x; i <= xx; i++) {
        for (int u : ls[i]) {
            if (u >= y && u <= yy) {
                cur[i].push_back(u);
            }
        }
        if (!cur[i].empty()) id.push_back(i);
    }
    for (int i = 0; i < id.size(); i++) {
        int u = id[i];
        for (int j = 0; j < cur[u].size(); j++) {
            int v = cur[u][j];
            int uu = (i + 1 < id.size() ? id[i + 1] - 1 : xx);
            int vv = (j + 1 < cur[u].size() ? cur[u][j + 1] - 1 : yy);
            int firstU = (i ? u : x);
            int firstV = (j ? v : y);
            color(a[u][v], firstU, uu, firstV, vv);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (a[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '.') continue;
            if (a[i][j] == 'A') {
                x = i, y = j;
            } else {
                ls[i].push_back(j);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        upper[i] = lower[i] = {m + 1, 0};
    }
    int ll = 1, rr = m;
    for (int i = x; i >= 1; i--) {
        int found = 0;
        for (int u : ls[i]) {
            if (u == y) {
                found = 1;
                break;
            }
            if (u < y) ll = max(ll, u + 1);
            else rr = min(rr, u - 1);
        }
        if (found) break;
        upper[i] = {ll, rr};
    }
    ll = 1, rr = m;
    for (int i = x; i <= n; i++) {
        int found = 0;
        for (int u : ls[i]) {
            if (u == y) {
                found = 1;
                break;
            }
            if (u < y) ll = max(ll, u + 1);
            else rr = min(rr, u - 1);
        }
        if (found) break;
        lower[i] = {ll, rr};
    }
    Res res = {0, 0, 0, 0, 0};
    for (int i = 1; i <= x; i++) {
        for (int j = x; j <= n; j++) {
            int ll = max(upper[i].first, lower[j].first);
            int rr = min(upper[i].second, lower[j].second);
            if (ll <= rr) {
                Res foo = {(rr - ll + 1) * (j - i + 1), i, j, ll, rr};
                res = max(res, foo);
            }
        }
    }
    for (int i = res.x; i <= res.xx; i++) {
        for (int j = res.y; j <= res.yy; j++) {
            if (a[i][j] == '.') a[i][j] = 'a';
        }
    }
    solve(1, res.x - 1, 1, m);
    solve(res.xx + 1, n, 1, m);
    solve(res.x, res.xx, 1, res.y - 1);
    solve(res.x, res.xx, res.yy + 1, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            assert(a[i][j] != '.');
            cout << a[i][j];
        }
        cout << '\n';
    }
    return 0;
}