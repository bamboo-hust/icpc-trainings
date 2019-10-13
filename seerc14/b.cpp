#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int LOG = 20;

int n, k, maxLen;
char s[N];

struct SuffixArray {
    int n;
    char *s;
    int sa[N], tmp[N], pos[N];
    int cnt[N];
    SuffixArray(char *t) {
        s = t;
        n = strlen(s + 1);
        buildSA();
    }

    void buildSA() {
        for (int i = 1; i <= n; i++) {
            sa[i] = i;
            pos[i] = s[i];
        }
        int len = 1;

        auto cmp = [&](int u, int v) {
            if (pos[u] != pos[v]) return pos[u] < pos[v];
            return (u + len <= n && v + len <= n) ? pos[u + len] < pos[v + len] : u > v;
        };

        auto radix = [&](int delta) {
            memset(cnt, 0, sizeof cnt);
            for (int i = 1; i <= n; i++) {
                cnt[i + delta <= n ? pos[i + delta] : 0]++;
            }
            for (int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
            for (int i = n; i > 0; i--) {
                int id = sa[i];
                tmp[cnt[id + delta <= n ? pos[id + delta] : 0]--] = id;
            }
            for (int i = 1; i <= n; i++) sa[i] = tmp[i];
        };

        while (1) {
            radix(len);
            radix(0);
            tmp[1] = 1;
            for (int i = 2; i <= n; i++) {
                tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
            }
            for (int i = 1; i <= n; i++) {
                pos[sa[i]] = tmp[i];
            }
            if (tmp[n] == n) break;
            len <<= 1;
        }
    }
};

int nxt[LOG][N];

bool check(int u, const SuffixArray &sa) {
    for (int i = 1; i <= n; i++) {
        int len = (sa.pos[i] <= u ? maxLen : maxLen - 1);
        nxt[0][i] = i + len;
        nxt[0][i + n] = min(n * 2, i + n + len);
    }
    for (int i = 1; (1 << i) <= k; i++) {
        for (int j = 1; j <= n * 2; j++) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        }
    }
    for (int i = 1; i <= n; i++) {
        int u = i;
        for (int j = LOG - 1; j >= 0; j--) {
            if (k >> j & 1) {
                u = nxt[j][u];
            }
        }
        if (u >= i + n) return 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("b.in", "r", stdin);
    cin >> n >> k;
    cin >> (s + 1);
    maxLen = (n - 1) / k + 1;
    if (maxLen == 1) {
        char maxChar = '1';
        for (int i = 1; i <= n; i++) {
            maxChar = max(maxChar, s[i]);
        }
        cout << maxChar << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) s[i + n] = s[i];
    SuffixArray sa(s);
    int low = 0, high = n * 2 + 1;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid, sa)) high = mid;
        else low = mid;
    }
    for (int i = sa.sa[high]; i < sa.sa[high] + maxLen; i++) {
        cout << s[i];
    }
    cout << endl;
    return 0;
}