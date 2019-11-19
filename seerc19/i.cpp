#include <bits/stdc++.h>

using namespace std;

const int N = 2048;
const int INF = 1e9;

int n;
pair<int, int> a[N];
int cur[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = 0;
    }
    for (int i = n; i < 2 * n; ++i) {
        cin >> a[i].first;
        a[i].second = 1;
    }
    sort(a, a + 2 * n);
    
    int last = -INF;
    for (int i = 0; i < 2 * n; ++i) {
        if (a[i].second == 1) {
            last = a[i].first;
        } else {
            cur[i] = a[i].first - last;
        }
    }
    last = INT_MAX;
    for (int i = 2 * n - 1; i >= 0; --i) {
        if (a[i].second == 1) {
            last = a[i].first;
        } else {
            cur[i] = min(cur[i], last - a[i].first);
        }
    }

    int res = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (a[i].second == 0) {
            res = max(res, cur[i]);
        }
    }

    cout << res << endl;
}