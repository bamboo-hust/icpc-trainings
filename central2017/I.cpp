#include <bits/stdc++.h>

using namespace std;

const int N = 300010;
const long long INF = (1ll << 60);

int n;
long long a[N];
long long int mx[3];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        //cout << u << endl;
        a[i] = a[i - 1] + u;
    }
    long long res = -INF;
    mx[0] = mx[1] = mx[2] = INF;
    mx[0] = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, a[i] - mx[i % 3]);
        mx[i % 3] = min(mx[i % 3], a[i]);
    }
    cout << res << endl;
    return 0;
}