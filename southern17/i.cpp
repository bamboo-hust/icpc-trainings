#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m;
int a[N], b[N];

struct BIT {
    long long t[N];

    void init() {
        memset(t, 0, sizeof t);
    }

    void add(int x, long long v) {
        while (x < N) {
            t[x] += v;
            x += (x & -x);
        }
    }

    long long get(int x) {
        long long res = 0;
        while (x) {
            res += t[x];
            x -= (x & -x);
        }
        return res;
    }

    long long get(int l, int r) {
        if (l == 0) {
            return get(r);
        }
        return get(r) - get(l - 1);
    }
} ta1, ta2, ta3, ta0;

long long get(int* a, int *b, int n, int m) {
    long long res = 0;
    ta1.init();
    ta2.init();
    ta3.init();
    ta0.init();
    //cout << 'A' << endl;
    for (int i = 1; i <= n; i++) {
        res += 1ll * i * a[i] * ta0.get(0, a[i] - 1) - 1ll * a[i] * ta1.get(0, a[i] - 1) - 1ll * i * ta2.get(0, a[i] - 1) + ta3.get(0, a[i] - 1);
        res += -1ll * i * a[i] * ta0.get(a[i] + 1, N - 1) + 1ll * a[i] * ta1.get(a[i] + 1, N - 1) + 1ll * i * ta2.get(a[i] + 1, N - 1) - ta3.get(a[i] + 1, N - 1);
        if (i <= m) {
            ta0.add(b[i], 1);
            ta1.add(b[i], i);
            ta2.add(b[i], b[i]);
            ta3.add(b[i], 1ll * i * b[i]);
        }
        //cout << res << endl;
    }
    return res;
}

long long random(long long u) {
    long long res = rand();
    res = (res << 16) + rand();
    res = (res << 16) + rand();
    return res % u;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    scanf("%d",&m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", b + i);
    }
    long long res = 0;
    res += get(a, b, n, m);
    res -= get(b, a, m, n);
    cout << res << endl;
    return 0;
}