#include <bits/stdc++.h>

using namespace std;

const int N = 2505;

long long a[N];
int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + 1 + n);
    long long res1 = 0;
    long long res2 = 0;
    long long all = 0;
    for (int i = 1; i <= n; ++i) {
        int k0 = 1;
        int k1 = 1;
        int k2 = 1;
        for (int j = i + 1; j <= n; ++j) {
            while (k0 <= n && a[i] + a[j] > a[k0]) ++k0;
            while (k1 < k0 && a[i] * a[i] + a[j] * a[j] > a[k1] * a[k1]) ++k1;
            while (k2 < k0 && a[i] * a[i] + a[j] * a[j] >= a[k2] * a[k2]) ++k2;
            if (k0 > j) all += k0 - j - 1;
            if (k1 > j) {
                res1 += k1 - j - 1;
                res2 += k2 - k1;
            }
        }
    }

    long long res3 = all - res1 - res2;
    cout << res1 << ' ' << res2 << ' ' << res3 << endl;
}