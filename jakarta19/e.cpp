#include <bits/stdc++.h>

using namespace std;

int const N = 1e5 + 5;

int a[N], l[N], r[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, left, right, k;
    cin >> n >> left >> right >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    l[n] = left;
    r[n] = right;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] < a[i + 1]) {
            r[i] = r[i + 1] - 1;
            l[i] = max(left, l[i + 1] - k);
        }
        if (a[i] > a[i + 1]) {
            r[i] = min(right, r[i + 1] + k);
            l[i] = l[i + 1] + 1;
        }
        if (a[i] == a[i + 1]) {
            l[i] = l[i + 1];
            r[i] = r[i + 1];
        }
        if (l[i] > r[i]) {
            cout << -1 << endl;
            return 0;
        }
    }
    int cur = l[1];
    vector < int > ans;
    for (int i = 1; i < n; i++) {
        assert(cur >= l[i] && cur <= r[i]);
        ans.push_back(cur);
        if (a[i] == a[i + 1]) {
            continue;
        }
        if (a[i] < a[i + 1]) {
            cur = max(cur + 1, l[i + 1]);
        }
        if (a[i] > a[i + 1]) {
            cur = max(cur - k, l[i + 1]);
        }
    }
    ans.push_back(cur);
    for (int v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}