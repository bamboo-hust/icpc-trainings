#include <bits/stdc++.h>
#define SW 0
#define SE 1
#define NE 2
#define NW 3

using namespace std;

const int N = 30003;

map<int, int> E[N];
int n;
int q;

void normalize(int &x, int &y, int dir) {
    if (dir == SE) return;
    if (dir == SW) y -= 1;
    else if (dir == NE) x -= 1;
    else x -= 1, y -= 1;
}

void get_range(int x, int y, int len, int dir, int row, int &l, int &r) {
    if (dir == SW) {
        if (row < x) return;
        if (row >= x + len) return;
        l = y - len + 1 + (row - x);
        r = y;
    } else if (dir == SE) {
        if (row < x) return;
        if (row >= x + len) return;
        l = y;
        r = y + len - 1 - (row - x);
    } else if (dir == NE) {
        if (row > x) return;
        if (row <= x - len) return;
        l = y;
        r = y + len - 1 - (x - row);
    } else {
        if (row > x) return;
        if (row <= x - len) return;
        l = y - len + 1 + (x - row);
        r = y;
    }

    l = max(l, 0);
    r = min(r, n - 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    freopen("j.in", "r", stdin);

    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        E[i][0] = 0;
        E[i][n] = 0;
    }
    while (q--) {
        int x, y, len, dir;
        cin >> x >> y >> len >> dir;
        normalize(x, y, dir);
        for (int i = max(x - len + 1, 0); i < min(x + len, n); ++i) {
            int l = n, r = -1;
            get_range(x, y, len, dir, i, l, r);
            if (l <= r) {
                E[i][l]++; E[i][r + 1]--;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        int last_col = 0;
        int last_sum = 0;
        for (auto it : E[i]) {
            if (it.first == 0) {
                last_sum = it.second;
            } else {
                if (last_sum % 2 == 1) {
                    res += it.first - last_col;
                }
                last_col = it.first;
                last_sum += it.second;
            }
        }
    }

    cout << res << endl;
}