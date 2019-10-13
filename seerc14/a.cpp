#include <bits/stdc++.h>

using namespace std;


int const N = 1e4 + 5;

int a[N], n;

int main() {
    freopen("a.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin >> n;
    priority_queue < pair < int, int > > que;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        que.push(make_pair(-a[i], i));
    }

    

    int ans = 0;
    while (!que.empty()) {
        pair < int, int > top = que.top(); que.pop();
        int i = top.second;
        if (-top.first != a[i]) {
            continue;
        }
        if (a[i] >= 0) {
            break;
        }

        ans++;

        int nxt = i + 1 <= n ? i + 1 : 1;
        int pre = i - 1 >= 1 ? i - 1 : n;
        a[nxt] += a[i];
        a[pre] += a[i];
        a[i] = - a[i];
        que.push(make_pair(-a[nxt], nxt));
        que.push(make_pair(-a[pre], pre));
        que.push(make_pair(-a[i], i));

    }
    cout << ans << endl;
}