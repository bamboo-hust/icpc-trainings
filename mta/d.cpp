#include <bits/stdc++.h>

using namespace std;
struct AhoCorasick {

    vector<int> fail;
    vector< map<char, int> > to;
    vector<bool> ending;
    vector<char> depth;
    int sz;
    
    AhoCorasick() {
        sz = 1;
        to.resize(2);
        fail.resize(2);
        depth.resize(2);
        ending.resize(2);
    }

    int to2(int u, int c) {
        while (u > 1 && !to[u].count(c)) {
            u = fail[u];
        }
        if (to[u].count(c)) return to[u][c];
        return 1;
    }

    int add(const string &s) {
        int node = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (!to[node].count(s[i] - 'A')) {
                to.push_back(map<char, int>());
                fail.push_back(0);
                depth.push_back(0);
                ending.push_back(0);
                to[node][s[i] - 'A'] = ++sz;
                depth[to[node][s[i] - 'A']] = depth[node] + 1;
            }
            node = to[node][s[i] - 'A'];
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
            for (map<char, int>::iterator it = to[u].begin(); it != to[u].end(); ++it) {
                char i = it->first;
                int &v = it->second;
                if (!v) {
                    v = u == 1 ? 1 : to2(fail[u], i);
                } else {
                    fail[v] = u == 1 ? 1 : to2(fail[u], i);
                    if (ending[fail[v]]) ending[v] = true;
                    Q.push(v);
                }
            }
        }
    }
} T;

string gen(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += char('A' + rand() % 2);
    }
    return s;
}

struct cmp {
    bool operator () (int a, int b) const {
        if (T.depth[a] != T.depth[b]) return T.depth[a] < T.depth[b];
        return a < b;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    //int n = 100000;
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        //string s = gen(30);
        //cerr << s << endl;
        T.add(s);
    }

    T.push();

    int q; cin >> q;
    //int q = 1000;
    while (q--) {
        string s; cin >> s;
        //string s = gen(1000);
        map<int, char, cmp> F;
        F[1] = 0;
        bool yes = false;
        for (int i = 0; i < s.size(); ++i) {
            map<int, char, cmp> G;
            for (map<int, char, cmp>::iterator it = F.begin(); it != F.end(); ++it) {
                int u = T.to2(it->first, s[i] - 'A');
                map<int, char, cmp>::iterator nxt = G.find(u);
                if (nxt == G.end()) {
                    G[u] = it->second;
                } else {
                    nxt->second = min(nxt->second, it->second);
                }
                if (it->second < 3) {
                    for (char c = 'A'; c <= 'Z'; ++c) if (c != s[i]) {
                        int u = T.to2(it->first, c - 'A');
                        map<int, char, cmp>::iterator nxt = G.find(u);
                        if (nxt == G.end()) {
                            G[u] = it->second + 1;
                            while (G.size() > 30) {
                                G.erase(G.begin());
                            }
                        } else {
                            nxt->second = min(nxt->second, char(it->second + 1));
                        }
                    }
                }
                
                while (G.size() > 30) {
                    G.erase(G.begin());
                }
                
            }
            F.swap(G);
            for (map<int, char, cmp>::iterator it = F.begin(); it != F.end(); ++it) if (T.ending[it->first]) {
                yes = true;
                break;
            }
            //cerr << F.size() << endl;
        }
        cout << (yes ? "YES" : "NO") << '\n';
    }
    return 0;
}