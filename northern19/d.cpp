#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

const int N = 1e5 + 5;

const int BASE = 47;
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
    return Hash{a.n + b.n, 1LL * a.x * b.x % MX, 1LL * a.y * b.y % MY};
}

Hash operator - (const Hash &a, const Hash &b) {
    return Hash{a.n, (a.x - b.x + MX) % MX, (a.y - b.y + MY) % MY};
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
Hash inv_power[L];

int start_pos[L];
int end_pos[L];
vector<int> ls;

int upper[L];
int depth[L];

//map<Hash, int> node_of;
gp_hash_table<Hash, int, HashHash> node_of;

int sz;

int n;

string s[N];
vector<Hash> suffix_hash[N];

int inverse(int a, int mod) {
    int n = mod - 2;
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = 1LL * res * a % mod;
        }
        a = 1LL * a * a % mod;
        n >>= 1;
    }
    return res;
}

void init_hash() {
    power[0] = Hash{0, 1, 1};
    for (int i = 1; i < L; ++i) {
        power[i] = power[i - 1] * BASE;
        inv_power[i].x = inverse(power[i].x, MX);
        inv_power[i].y = inverse(power[i].y, MY);
    }
}

bool add(const string &s, int id) {
    int u = 1;
    for (int i = 1; i < s.size(); ++i) {
        char c = s[i] - 'a';
        if (!to[u][c]) to[u][c] = ++sz;
        H[to[u][c]] = H[u] * BASE + (c + 1);
        if (term[u]) {
            upper[to[u][c]] = u;
        } else {
            upper[to[u][c]] = upper[u];
        }
        depth[to[u][c]] = depth[u] + 1;
        u = to[u][c];
        cerr << u << ' ' << upper[u] << endl;
        // cerr << "node " << id << ' ' << i << ' ' << u << endl;
        cerr << "node_of " << s << ' ' << u << ' ' << H[u].n << ' ' << H[u].x << endl;
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
        add(s[i], i);
    }

    for (int i = 1; i <= n; ++i) {
        suffix_hash[i].resize(s[i].size() + 1);
        Hash cur{0, 0, 0};
        suffix_hash[i][s[i].size()] = cur;
        for (int j = s[i].size() - 1; j >= 1; --j) {
            cur = Hash{1, s[i][j] - 'a' + 1, s[i][j] - 'a' + 1} * power[s[i].size() - j - 1] + cur;
            suffix_hash[i][j] = cur;
            //cerr << "suffix_hash " << i << ' ' << j << ' ' << suffix_hash[i][j].x << ' ' << suffix_hash[i][j].y << ' ' << suffix_hash[i][j].z << endl;
        }
    }

    ls.clear();
    dfs(1);

    gp_hash_table<Hash, bool, HashHash> Q;

    for (int i = 1; i <= n; ++i) {
        int u = 1;
        for (int j = 1; j + 1 < s[i].size(); ++j) {
            char c = s[i][j] - 'a';
            u = to[u][c];
            //cerr << "go " << i << ' ' << j << ' ' << u << ' ' << term[u] << endl;
            if (term[u]) {
                Q[suffix_hash[i][j + 1]] = true;
                //was[suffix_hash[i][j + 1]] = true;
            }
        }
    }

    while (!Q.empty()) {
        if (double(clock()) / CLOCKS_PER_SEC > 0.9) return true;
        Hash u = Q.begin()->first; Q.erase(u);
        int node = node_of[u];
        cerr << u.x << endl;
        if (term[node]) return false;
        cerr << "node " << node << endl;
        for (int p = upper[node]; p; p = upper[node]) {
            cerr << "upper " << p << endl;
            int len = depth[node] - depth[p];
            Hash prefix_hash = u * inv_power[len];
            prefix_hash = prefix_hash * power[len];
            Hash v = u - prefix_hash;
            if (Q.find(v) != Q.end()) continue;
            if (node_of.find(v) != node_of.end()) {
                //was[suffix_hash[t][u.n + 1]] = true;
                Q[v] = true;
            }
        }
        for (int i = start_pos[node]; i < end_pos[node]; ++i) {
            int t = ls[i];
            //if (was[suffix_hash[t][u.n + 1]]) return false;
            if (Q.find(suffix_hash[t][u.n + 1]) != Q.end()) continue;
            if (node_of.find(suffix_hash[t][u.n + 1]) != node_of.end()) {
                //was[suffix_hash[t][u.n + 1]] = true;
                Q[suffix_hash[t][u.n + 1]] = true;
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
        sort(s + 1, s + 1 + n);
        int m = unique(s + 1, s + 1 + n) - s - 1;
        if (m != n) {
            cout << "NO\n";
        } else 
        {
            n = m;
            cout << (solve() ? "YES" : "NO") << '\n';
        }

        for (int i = 1; i <= n; ++i) s[i] = "";
        for (int i = 1; i <= sz; ++i) for (int j = 0; j < 26; ++j) to[i][j] = 0;
        for (int i = 1; i <= sz; ++i) term[i] = upper[i] = depth[i] = 0;
        for (int i = 1; i <= n; ++i) suffix_hash[i].clear();
    }
}