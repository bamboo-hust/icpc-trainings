#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, m;
int a[N][N];
int b[N][N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", a[i] + j);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int ii = n - i + 1;
            int jj = m - j + 1;
            vector<int> v;
            v.push_back(a[i][j]);
            v.push_back(a[ii][j]);
            v.push_back(a[i][jj]);
            v.push_back(a[ii][jj]);
            int res = -1;
            int cnt = 0;
            for (int i = 0; i < v.size(); i++) {
                int foo = 0;
                for (int j = 0; j < v.size(); j++) {
                    foo += v[i] == v[j];
                }
                if (foo > cnt) {
                    cnt = foo;
                    res = v[i];
                }
            }
            b[i][j] = b[ii][j] = b[i][jj] = b[ii][jj] = res;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans += a[i][j] != b[i][j];
        }
    }
    cout << ans << endl;
    return 0;
}