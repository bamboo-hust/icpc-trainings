#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
pair<int, int> a[N];
int mx[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        if (a[i].first > a[i].second) swap(a[i].first, a[i].second);
        a[i].first;
        a[i].second *= 2;
    }
    sort(a + 1, a + n + 1);
    mx[n + 1] = 0;
    for (int i = n; i; i--) {
        mx[i] = max(mx[i + 1], a[i].second);
    }
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, 1ll * a[i].first * a[i].second / 2);
        res = max(res, 1ll * a[i].first * min(a[i].second, mx[i + 1]));
    }
    cout << res / 2 << '.' << (res & 1ll ? '5' : '0') << endl;
    return 0;
}