#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int x[N], y[N];
int n;

int get_dir(int i) {
    for (int d = 0; d < 4; ++d) {
        if (x[i + 1] - x[i] == dx[d] && y[i + 1] - y[i] == dy[d]) {
            return d;
        }
    }
    //assert(false);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
    int ans = 0;
    for (int i = 3; i <= n; ++i) {
        int p = get_dir(i - 2);
        int q = get_dir(i - 1);
        //cerr << p << ' ' << q << endl;
        ans += (p + 1) % 4 == q;
    }
    cout << ans << endl;
    return 0;
}