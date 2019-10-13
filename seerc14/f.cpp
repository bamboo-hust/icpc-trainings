#include <bits/stdc++.h>

using namespace std;

const int N = 60010;
const int B = sqrt(N / 2);
const int NB = N / B + 10;

int n, k, numBlock;
int a[N];

struct Block {
    int l, r, delta;
    vector<int> ls;
    void init() {
        l = n;
        r = -1;
        delta = 0;
        ls.clear();
    }
    void add(int u) {
        l = min(l, u);
        r = max(r, u);
    }
    void build() {
        ls.resize(r - l + 1);
        for (int i = l; i <= r; i++) {
            ls[i - l] = a[i];
        }
        sort(ls.begin(), ls.end());
    }
} b[NB];

void addInsideBlock(int u, int l, int r) {
    for (int i = l; i <= r; i++) a[i]++;
    b[u].build();
}

bool check(int u) {
    int tot = 0;
    for (int i = 0; i < numBlock; i++) {
        int now = upper_bound(b[i].ls.begin(), b[i].ls.end(), u - b[i].delta) - b[i].ls.begin();
        tot += now;
    }
    return tot * 2 > n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("f.in", "r", stdin);
    while (1) {
        cin >> n >> k;
        if (!n && !k) return 0;
        numBlock = (n - 1) / B + 1;
        vector<int> vals(n);
        for (int i = 0;  i < numBlock; i++) {
            b[i].init();
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            vals[i] = a[i];
            b[i / B].add(i);
        }
        for (int i = 0; i < numBlock; i++) {
            b[i].build();
        }
        sort(vals.begin(), vals.end());
        int curRes = vals[n / 2];
        while (k--) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int lBlock = l / B;
            int rBlock = r / B;
            if (lBlock == rBlock) addInsideBlock(lBlock, l, r);
            else {
                for (int i = lBlock + 1; i < rBlock; i++) b[i].delta++;
                addInsideBlock(lBlock, l, b[lBlock].r);
                addInsideBlock(rBlock, b[rBlock].l, r);
            }
            while (!check(curRes)) curRes++;
            cout << curRes << '\n';
        }
    }
    return 0;
}