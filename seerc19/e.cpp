#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int64_t INF = 1e18;

int64_t lc, pc, lm, pm;
int64_t t, d;
int64_t a[N];
int n, k;

int64_t S[N];
int64_t A[N], C[N], E[N];

int64_t sum(int64_t s[], int l, int r) {
    if (l > r) return 0;
    return s[r] - s[l - 1];
}

int find_first_greater_or_equal(int from, int to, int64_t value) {
    if (from > to) {
        return from;
    }
    int l = from, r = to;
    int res = to + 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] >= value) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return res;
}

int64_t solve(int x) {
    // x = number of motorcycles
    int car = (n - x) / k + bool((n - x) % k);

    int startB = n - car + 1;
    int startA = find_first_greater_or_equal(startB, n, lc);
    int startD = startB - x;
    int startC = find_first_greater_or_equal(startD, startD + x - 1, lm);

    int64_t minB = a[startB];
    int64_t minD = a[startD];

    if (car > 0 && lc - minB > d) return INF;
    if (x > 0 && lm - minD > d) return INF;

    int64_t spare = sum(A, startA, n) + sum(C, startC, startB - 1) + sum(E, 1, startD - 1);
    int64_t need = lc * (startA - startB) - sum(S, startB, startA - 1) + lm * (startC - startD) - sum(S, startD, startC - 1);

    if (spare < need) return INF;

    return pm * x + pc * car + t * need;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> k;
    cin >> lc >> pc >> lm >> pm;
    cin >> t >> d;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + 1 + n);

    for (int i = 1; i <= n; ++i) {
        A[i] = a[i] - max(a[i] - d, lc);
        C[i] = a[i] - max(a[i] - d, lm);
        E[i] = a[i] - max(a[i] - d, int64_t(1));
    }

    for (int i = 1; i <= n; ++i) {
        A[i] += A[i - 1];
        C[i] += C[i - 1];
        E[i] += E[i - 1];
        S[i] = S[i - 1] + a[i];
    }

    int64_t res = INF;
    for (int x = 0; x <= n; ++x) {
        res = min(res, solve(x));
    }

    if (res == INF) res = -1;
    cout << res << endl;

    return 0;
}