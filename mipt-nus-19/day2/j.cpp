#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N];
int64_t s[N];
int n;
int64_t L;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        a[i] = min(x, y);
    }
    cin >> L;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + a[i];
    }
    int res = 1;
    if (a[1] + a[2] < L * 2) {
        res = 2;
    }
    for (int i = 3; i <= n; ++i) {
        if (L * 2 - a[i] - a[i - 1] > s[i - 2] * 2) {
            res = i;
        }
    }
    cout << res << endl;
}