#include <bits/stdc++.h>

using namespace std;

const int N = 2048;

int a[N];
int n, m;

int solve1() {
    int bag1 = 0;
    int bag2 = 0;
    for (int i = n; i >= 1; --i) {
        if (bag1 < bag2) {
            bag1 += a[i];
        } else {
            bag2 += a[i];
        }
    }
    return max(bag1, bag2);
}

int solve2() {
    int sum = accumulate(a + 1, a + 1 + n, 0);
    int cur = 0;
    for (int i = n; i >= 1; --i) {
        if (cur + a[i] <= sum / 2) {
            cur += a[i];
        }
    }
    return max(cur, sum - cur);
}

bitset<1000006> cur;

int solve3() {
    int sum = accumulate(a + 1, a + 1 + n, 0);
    cur[0] = 1;
    for (int i = 1; i <= n; ++i) {
        cur |= cur << a[i];
    }
    for (int i = min(sum / 2, 1000006); i >= 0; --i) {
        if (cur[i]) {
            return max(i, sum - i);
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    m = n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] % 2 == 0) {
            a[i] /= 2;
            a[++m] = a[i];
        }
    }
    n = m;

    sort(a + 1, a + 1 + n);

    cout << min(min(solve1(), solve2()), solve3()) << endl;
}