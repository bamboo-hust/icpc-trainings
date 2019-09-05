#include <bits/stdc++.h>

using namespace std;

const int N = 1024;
const int MOD = 1000003;

void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int fail[N];
int to[N][26];
int ending[N];
int sz = 1;

int add(const string &s) {
    int node = 1;
    for (int i = 0; i < s.size(); ++i) {
        int &v = to[node][s[i] - 'a'];
        if (!v) v = ++sz;
        if (ending[node]) ending[v] = true;
        node = v;
    }
    ending[node] = true;
    return node;
}

void push() {
    queue<int> Q;
    Q.push(1);
    fail[1] = 1;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = 0; i < 26; ++i) {
            int &v = to[u][i];
            if (!v) {
                v = u == 1 ? 1 : to[fail[u]][i];
            } else {
                fail[v] = u == 1 ? 1 : to[fail[u]][i];
                ending[v] |= ending[fail[v]];
                Q.push(v);
            }
        }
    }
}

int L, R;

int normal[128];

void init() {
    for (char c = 'a'; c <= 'z'; ++c) normal[c] = c;
    for (char c = 'A'; c <= 'Z'; ++c) normal[c] = c - 'A' + 'a';
    for (char c = '0'; c <= '9'; ++c) normal[c] = c;
    normal['0'] = 'o';
    normal['1'] = 'i';
    normal['3'] = 'e';
    normal['5'] = 's';
    normal['7'] = 't';
}

int dp[22][N][8];
int n;

int get_mask(int mask, char c) {
    if ('a' <= c && c <= 'z') mask |= 1;
    if ('A' <= c && c <= 'Z') mask |= 2;
    if ('0' <= c && c <= '9') mask |= 4;
    return mask;
}

int main() {
    ios::sync_with_stdio(false);

    init();

    cin >> L >> R;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    sort(begin(s), end(s), [](const string &x, const string &y){return x.size() < y.size();});
    for (auto p : s) add(p);
    push();

    dp[0][1][0] = 1;
    for (int i = 0; i <= R; ++i) {
        for (int node = 1; node <= sz; ++node) {
            for (int mask = 0; mask < 8; ++mask) {
                if (dp[i][node][mask]) {
                    //cerr << i << ' ' << node << ' ' << mask << ' ' << dp[i][node][mask] << endl;
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (!ending[to[node][c - 'a']]) {
                            add(dp[i + 1][to[node][c - 'a']][get_mask(mask, c)], dp[i][node][mask]);
                        }
                    }
                    for (char c = 'A'; c <= 'Z'; ++c) {
                        if (!ending[to[node][c - 'A']]) {
                            add(dp[i + 1][to[node][c - 'A']][get_mask(mask, c)], dp[i][node][mask]);
                        }
                    }
                    for (char c = '0'; c <= '9'; ++c) {
                        if (normal[c] != c) {
                            if (!ending[to[node][normal[c] - 'a']]) {
                                add(dp[i + 1][to[node][normal[c] - 'a']][get_mask(mask, c)], dp[i][node][mask]);
                            }
                        } else {
                            add(dp[i + 1][1][get_mask(mask, c)], dp[i][node][mask]);
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = L; i <= R; ++i) {
        for (int node = 1; node <= sz; ++node) {
            add(ans, dp[i][node][7]);
        }
    }

    cout << ans << endl;

    return 0;
}