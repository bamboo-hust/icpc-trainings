#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 1010;

int n;
int x[N], y[N], h[N];

bool check(int lim, bool flag) {
    int minX = -INF, maxX = INF;
    int minY = -INF, maxY = INF;
    for (int i = 1; i <= n; i++) {
        minX = max(minX, x[i] - (lim - h[i]));
        maxX = min(maxX, x[i] + (lim - h[i]));
        minY = max(minY, y[i] - (lim - h[i]));
        maxY = min(maxY, y[i] + (lim - h[i]));
    }
    if (minX > maxX || minY > maxY) return 0;
    if (flag) {
        cout << minX << ' ' << minY << ' ' << lim << endl;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i] >> h[i];
    }
    int minH = *min_element(h + 1, h + n + 1);
    int low = minH - 1, high = INF;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid, 0)) high = mid;
        else low = mid;
    }
    check(high, 1);
    return 0;
}