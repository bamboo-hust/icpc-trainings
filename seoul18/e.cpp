#include <bits/stdc++.h>

using namespace std;
#define int long long

const int N = 300010;
const long long INF = 1e10;

int n;
int v[N], l[N], id[N];

bool check(long long delta) {
    int cur = 1;
    while (cur <= n && l[id[cur]] <= delta) cur++;
    long long lower = 0, upper = INF;
    while (cur <= n) {
        long long x = max(lower, 1ll * l[id[cur]] - delta);
        long long y = min(upper, 1ll * l[id[cur]] + delta);
        if(x <= y) {
            cur++;
            lower = x;
            upper = y;
        } else break;
    }
    long long l1 = lower;
    lower = 0, upper = INF;
    while (cur <= n) {
        long long x = max(lower, 1ll * l[id[cur]] - delta);
        long long y = min(upper, 1ll * l[id[cur]] + delta);
        if(x <= y) {
            cur++;
            lower = x;
            upper = y;
        } else break;
    }
    long long l2 = upper;
    if (l1 > l2) return 0;
    if (cur <= n) return 0;
    return 1;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> l[i];
        l[i] *= 2;
        id[i] = i;
    }
    sort(id + 1, id + n + 1, [](int x, int y) {
        return v[x] < v[y];
    });
    long long low = -1, high = INF;
    if (v[id[1]] == 0) {
        low = l[id[1]] - 1;
    }
    while (high - low > 1) {
        long long mid = low + high >> 1;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high / 2 << '.' << (high % 2 ? '5' : '0') << endl;
    return 0;
}