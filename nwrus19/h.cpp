#include <bits/stdc++.h>

using namespace std;

int const N = 1e6 + 5;

int n, a[N], ans[N];


int get_ans(int u) {
    if (ans[u]) {
        return ans[u];
    }

    int pos = 0, res = 0;
    while (pos < n) {
        int next_pos = upper_bound(a + 1, a + n + 1, a[pos] + u) - a - 1;
        if (next_pos == pos) {
            return ans[u] = -1;
        }
        pos = next_pos;
        res++;
    }
    return ans[u] = res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }

    int q;
    cin >> q;
    while (q--) {
        int u;
        cin >> u;
        int res = get_ans(u);
        if (res != -1) {
            cout << res << "\n";
        } else {
            cout << "Impossible" << "\n";
        }
    }
    return 0;
}