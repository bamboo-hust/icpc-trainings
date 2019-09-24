#include <bits/stdc++.h>

using namespace std;


int const N = 3e5 + 5;

int root[N], n, k;
long long a[N], last[N];



int get_root(int u) {
    if (u == root[u]) {
        return u;
    }
    return root[u] = get_root(root[u]);
}

bool find(int mid) {
    for (int i = 1; i <= n + 1; i++) {
        root[i] = i;
    }
    int pos = 1, total = 0;
    for (int i = 1; i <= mid; i++) {
        root[i] = i + 1;
        last[i] = a[i];
        total++;
    }

    for (int i = mid + 1; i <= n; i++) {
        if (a[i] >= last[pos] * 2) {
            last[pos] = a[i];
            pos = pos + 1;
            if (pos > mid) {
                pos = 1;
            }
            total++;
        }
    }
    return total >= mid * k;

}

int main() {
    ios_base::sync_with_stdio(0);
    int test_case;
    cin >> test_case;
    for (int test = 1; test <= test_case; test++) {
        cout << "Case #" << test << ": ";
        cin >> n >> k;
        for (int i = 1; i <= n + 1; i++) {
            root[i] = i;
        }
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        sort(a + 1, a + n + 1);
        int l = 0;
        int r = n + 1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (find(mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        cout << l << endl;
    }
}