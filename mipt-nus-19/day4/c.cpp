//
// Created by quanglm1998 on 24/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;
const int LOG = 61;

int n, k;
long long m;
long long a[N];
int nxt[LOG][N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto getVal = [](long long u, long long v) {
        return abs(u - v);
    };

    int l = 1, r = k + 1;

    for (int i = 1; i <= n; i++) {
        while (r < n && getVal(a[i], a[r + 1]) < getVal(a[i], a[l])) r++, l++;
        if (getVal(a[i], a[l]) >= getVal(a[i], a[r])) nxt[0][i] = l;
        else nxt[0][i] = r;
    }

    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        }
    }

    auto getNxt = [](int u, long long m) {
        for (int i = 0; i < LOG; i++) {
            if (m >> i & 1) {
                u = nxt[i][u];
            }
        }
        return u;
    };

    for (int i = 1; i <= n; i++) cout << getNxt(i, m) << ' ';
    cout << endl;
    return 0;
}