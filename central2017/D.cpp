#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m, l, r;
pair<int, int> a[N];
int x[N], xx[N], y[N], yy[N];
int res[N];

int main() {
    scanf("%d %d %d %d", &n, &l, &r, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &a[i].first, &a[i].second);
    }
    sort(a + 1, a + n + 1);
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            x[i] = xx[i] = 1;
            y[i] = 1 + l - 1;
            yy[i] = 1 + r - 1;
        } else {
            x[i] = y[i - 1] + 1;
            xx[i] = yy[i - 1] + 1;
            y[i] = x[i] + l - 1;
            yy[i] = xx[i] + r - 1;
        }
        y[i] = min(y[i], n);
        yy[i] = min(yy[i], n);
        int s = cur + 1;
        while (cur < m && a[cur + 1].second == i) {
            cur++;
        }   
        int t = cur;
        if (s <= t) {
            y[i] = max(y[i], a[t].first);
            x[i] = max(x[i], y[i] - r + 1);
            xx[i] = min(xx[i], a[s].first);
            yy[i] = min(yy[i], xx[i] + r - 1);
        }
    }
  /*   for (int i = 1; i <= n; i++) {
        cout << i << ""  << x[i] << " " << xx[i] << " " << y[i] << " " << yy[i] << endl;
    } */
    int pos = 0;
    for (int i = n; i; i--) {
        if (x[i] + l - 1 <= n) {
            pos = i;
            break;
        }
    }
    cout << pos << endl;
    int now = n;
    for (int i = pos; i; i--) {
        int nxt = now - l + 1;
        
        nxt = min(nxt, xx[i]);
/*         cout << i << " " <<  nxt << " " << endl;
 */        for (int j = nxt; j <= now; j++) {
            res[j] = i;
        }
        now = nxt - 1;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", res[i]);
    }
    return 0;
}