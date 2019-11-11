#include <bits/stdc++.h>

using namespace std;


int const N = 1e5 + 5;

int next_r[N], next_c[N], r[N], c[N], n, q;


void solve(int x1, int y1, int x2, int y2) {
    if ((r[x1] + c[y1]) % 2) {
        cout << "NO" << endl;
        return;
    }
    if (x1 > x2) {
        swap(x1, x2);
    }
    if (next_r[x1] < x2) {
        cout << "NO" << endl;
        return;
    }
    if (y1 > y2) {
        swap(y1, y2);
    }
    if (next_c[y1] < y2) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
        r[i] %= 2;
    }
    r[n + 1] = c[n + 1] = -1;
    for (int i = n; i >= 1; i--) {
        if (r[i] == r[i + 1]) {
            next_r[i] = next_r[i + 1];
        } else {
            next_r[i] = i;
        }
    }


    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        c[i] %= 2;
    }

    for (int i = n; i >= 1; i--) {
        if (c[i] == c[i + 1]) {
            next_c[i] = next_c[i + 1];
        } else {
            next_c[i] = i;
        }
    }

    for (int i = 1; i <= q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        solve(x1, y1, x2, y2);
    }


    return 0;
}