#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

const int N = 1e5 + 5;

const int BASE = 31;
const int MX = 1e9 + 7;
const int MY = 1e9 + 3;

const int L = 250005;

struct Hash {
    int n;
    int x;
    int y;

    bool operator < (const Hash &o) const {
        if (n != o.n) return n < o.n;
        if (x != o.x) return x < o.x;
        return y < o.y;
    }

    bool operator == (const Hash &o) const {
        return (n == o.n && x == o.x && y == o.y);
    }
};

Hash operator * (const Hash &a, uint32_t b) {
    return Hash{a.n + 1, 1LL * a.x * b % MX, 1LL * a.y * b % MY};
}

Hash operator * (const Hash &a, const Hash &b) {
    return Hash{a.n + b.n, 1LL * a.x * b.x % MX, 1L * a.y * b.y % MY};
}

Hash operator + (const Hash &a, uint32_t b) {
    return Hash{a.n, (a.x + b) % MX, (a.y + b) % MY};
}

Hash operator + (const Hash &a, const Hash &b) {
    return Hash{a.n, (a.x + b.x) % MX, (a.y + b.y) % MY};
}

struct HashHash {
    size_t operator() (const Hash &o) const {
        return o.x;
    }
};

int to[L][26];
int term[L];
Hash H[L];
Hash power[L];

int start_pos[L];
int end_pos[L];
vector<int> ls;

//map<Hash, int> node_of;
gp_hash_table<Hash, int, HashHash> node_of;

int sz;

int n;

string s[N];
vector<Hash> suffix_hash[N];

void init_hash() {
    power[0] = Hash{0, 1, 1};
    for (int i = 1; i < L; ++i) {
        power[i] = power[i - 1] * BASE;
    }
}

bool add(const string &s, int id) {
    int u = 1;
    for (int i = 1; i < s.size(); ++i) {
        char c = s[i] - 'a';
        if (!to[u][c]) to[u][c] = ++sz;
        H[to[u][c]] = H[u] * BASE + (c + 1);
        u = to[u][c];
        // cerr << "node " << id << ' ' << i << ' ' << u << endl;
        // cerr << "node_of " << s << ' ' << H[u].n << ' ' << H[u].x << endl;
        node_of[H[u]] = u;
    }
    if (term[u]) {
        return false;
    }
    term[u] = id;
    
    return true;
}

void dfs(int u) {
    start_pos[u] = ls.size();
    if (term[u]) ls.push_back(term[u]);
    for (int c = 0; c < 26; ++c) {
        int v = to[u][c];
        if (!v) continue;
        dfs(v);
    }
    end_pos[u] = ls.size();
}

bool solve() {
    node_of.clear();
    sz = 1;
    for (int i = 1; i <= n; ++i) {
        if (!add(s[i], i)) {
            return false;
        }
    }

    for (int i = 1; i <= n; ++i) {
        suffix_hash[i].resize(s[i].size() + 1);
        Hash cur{0, 0, 0};
        suffix_hash[i][s[i].size()] = cur;
        for (int j = s[i].size() - 1; j >= 1; --j) {
            cur = Hash{1, s[i][j] - 'a' + 1, s[i][j] - 'a' + 1} * power[s[i].size() - j - 1] + cur;
            suffix_hash[i][j] = cur;
        }
    }

    ls.clear();
    dfs(1);

    queue<Hash> Q;
    gp_hash_table<Hash, bool, HashHash> was;

    for (int i = 1; i <= n; ++i) {
        int u = 1;
        for (int j = 1; j + 1 < s[i].size(); ++j) {
            char c = s[i][j] - 'a';
            u = to[u][c];
            //cerr << "go " << i << ' ' << j << ' ' << u << ' ' << term[u] << endl;
            if (term[u]) {
                Q.push(suffix_hash[i][j + 1]);
                was[suffix_hash[i][j + 1]] = true;
            }
        }
    }

    while (!Q.empty()) {
        Hash u = Q.front(); Q.pop();
        int node = node_of[u];
        if (term[node]) return false;
        for (int i = start_pos[node]; i < end_pos[node]; ++i) {
            int t = ls[i];
            if (!was[suffix_hash[t][u.n + 1]] && node_of.find(suffix_hash[t][u.n + 1]) != node_of.end()) {
                was[suffix_hash[t][u.n + 1]] = true;
                Q.push(suffix_hash[t][u.n + 1]);
            }
        }
    }

    return true;
}

int main() {
    init_hash();

    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            s[i] = '$' + s[i];
        }
        cout << (solve() ? "YES" : "NO") << '\n';

        for (int i = 1; i <= n; ++i) s[i] = "";
        for (int i = 1; i <= sz; ++i) for (int j = 0; j < 26; ++j) to[i][j] = 0;
        for (int i = 1; i <= sz; ++i) term[i] = 0;
        for (int i = 1; i <= n; ++i) suffix_hash[i].clear();
    }
}