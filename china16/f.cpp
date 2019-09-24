#include <bits/stdc++.h>

using namespace std;

const int LEN = 400010;
const int LOG = 21;

int lg2[LEN];

struct SuffixArray {
    int n;
    char *s;
    int sa[LEN], tmp[LEN], pos[LEN];
    int len, cnt[LEN], lcp[LEN];
    int mn[LOG][LEN];

    SuffixArray(char *t) {
        s = t;
        n = strlen(t + 1);
        buildSA();
    }

    bool cmp(int u, int v) {
        if (pos[u] != pos[v]) return pos[u] < pos[v];
        return (u + len <= n && v + len <= n) ? pos[u + len] < pos[v + len] : u > v;
    }

    void radix(int delta) {
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; i++) {
            cnt[i + delta <= n ? pos[i + delta] : 0]++;
        }
        for (int i = 1; i < LEN; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n; i > 0; i--) {
            int id = sa[i];
            tmp[cnt[id + delta <= n ? pos[id + delta] : 0]--] = id;
        }
        for (int i = 1; i <= n; i++) {
            sa[i] = tmp[i];
        }
    }

    int rmq(int l, int r) {
        int lg = lg2[r - l + 1];
        return min(mn[lg][l], mn[lg][r - (1 << lg) + 1]);
    }

    void buildSA() {
        for (int i = 1; i <= n; i++) {
            sa[i] = i;
            pos[i] = s[i];
        }
        len = 1;
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
        
        len = 0;
        for (int i = 1; i <= n; i++) {
            if (pos[i] == n) continue;
            int j = sa[pos[i] + 1];
            while (s[i + len] == s[j + len]) len++;
            lcp[pos[i]] = len;
            if (len) len--;
        }
        
        for (int i = 1; i < n; i++) {
            mn[0][i] = lcp[i];
        }
        for (int i = 1; i < LOG; i++) {
            for (int j = 1; j + (1 << i) - 1 < n; j++) {
                mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + (1 << i - 1)]);
            }
        }

        // cout << (s + 1) << endl;
        // for (int i = 1; i <= n; i++) {
        //     for (int j = sa[i]; j <= n; j++) cout << s[j];
        //         cout << endl;
        // }
    }

    int pref[LEN], suff[LEN];

    pair<int, int> solve(int n1) {
        pair<int, int> res(n + 1, -1);
        int last = -1;
        for (int i = 1; i <= n; i++) {
            if (sa[i] <= n1) {
                pref[i] = last;
            } else last = i;
        }
        last = n + 1;
        for (int i = n; i > 0; i--) {
            if (sa[i] <= n1) {
                suff[i] = last;
            } else last = i;
        }

        for (int i = 1; i <= n; i++) {
            if (sa[i] <= n1) {
                int mx = 0;
                if (pref[i] != -1) mx = max(mx, rmq(pref[i], i - 1));
                if (suff[i] != n + 1) mx = max(mx, rmq(i, suff[i] - 1));
                mx++;
                if (mx < res.first && sa[i] + mx - 1 <= n1) {
                    res = {mx, sa[i]};
                }
            }
        }
        return res;
    }
};

int n;
char s[LEN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    lg2[1] = 0;
    for (int i = 2; i < LEN; i++) lg2[i] = lg2[i >> 1] + 1;
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        cout << "Case #" << test << ": ";
        cin >> n;
        int n1 = 0;
        string now = "";
        for (int i = 1; i <= n; i++) {
            string u;
            cin >> u;
            if (i == 1) n1 = u.size();
            now += "#";
            now += u;
        }
        for (int i = 0; i < now.size(); i++) {
            s[i] = now[i];
        }
        s[now.size()] = 0;
        SuffixArray sa(s);
        pair<int, int> res = sa.solve(n1);
        if (res.second == -1) cout << "Impossible\n";
        else {
            for (int i = 0; i < res.first; i++) {
                cout << s[i + res.second];
            }
            cout << '\n';
        }
    }
    return 0;
}