#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;
const int V = N * 2;

int to[N * 2][2];
vector<int> ending[N * 2];
int sz;

int unknown_pos[N];
vector< pair<string, int> > s;

int n;
int numComp;
vector<int> adj[V];
int low[V], num[V], root[V], cntTarjan;
vector<int> stTarjan;
int color[V];

void init() {
    memset(root, -1, sizeof root);
    memset(low, -1, sizeof low);
    memset(num, -1, sizeof num);
    memset(color, -1, sizeof color);
    cntTarjan = 0;
    stTarjan.clear();
}

void push_edge(int u, int v) {
    //cerr << "push_edge " << u << ' ' << v << endl;
    adj[u].push_back(v);
}

void tarjan(int u) {
    stTarjan.push_back(u);
    num[u] = low[u] = cntTarjan++;
    for (int v : adj[u]) {
        if (root[v] != -1) continue;
        if (low[v] == -1) tarjan(v);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        while (1) {
            int v = stTarjan.back();
            stTarjan.pop_back();
            root[v] = numComp;
            if (u == v) break;
        }
        numComp++;
    }
}

bool solve() {
    for (int i = 0; i < n * 2; ++i) if (root[i] == -1) {
        tarjan(i);
        //cerr << "tarjan " << i << ' ' << root[i] << endl;
    }
    for (int i = 0; i < n * 2; i += 2) {
        if (root[i] == root[i ^ 1]) return 0;
        color[i >> 1] = (root[i] < root[i ^ 1]);
    }
    return 1;
}

void update(int a, int b) {
    //cerr << "update " << a << ' ' << b << ' ' << s[a].first << ' ' << s[b].first << endl;
    int x = unknown_pos[a];
    int y = unknown_pos[b];
    if (x == -1) {
        swap(x, y);
        swap(a, b);
    }
    if (x == -1) {
        cout << "NO\n";
        exit(0);
    }
    if (y == -1) {
        if (x >= s[b].first.size()) {
            cout << "NO\n";
            exit(0);
        }
        if (s[b].first[x] == '0') {
            //cerr << "must be one " << s[a].first << endl;
            push_edge(a * 2 + 1, a * 2);
        } else {
            //cerr << "must be zero " << s[a].first << endl;
            push_edge(a * 2, a * 2 + 1);
        }
        return;
    }
    if (x == y) {
        push_edge(a * 2, b * 2 + 1);
        push_edge(b * 2, a * 2 + 1);
        push_edge(b * 2 + 1, a * 2);
        push_edge(a * 2 + 1, b * 2);
    } else if (max(x, y) < min(s[a].first.size(), s[b].first.size())) {
        push_edge((a * 2 + 1) ^ (s[b].first[x] - '0'), (b * 2) ^ (s[a].first[y] - '0'));
        push_edge((b * 2 + 1) ^ (s[a].first[y] - '0'), (a * 2) ^ (s[b].first[x] - '0'));
    } else {
        if (x > y) {
            swap(x, y);
            swap(a, b);
        }
        if (s[b].first[x] == '0') {
            //cerr << "must be one " << s[a].first << endl;
            push_edge(a * 2 + 1, a * 2);
        } else {
            //cerr << "must be zero " << s[a].first << endl;
            push_edge(a * 2, a * 2 + 1);
        }
    }
}

void add(const string &s, int id) {
    //cerr << "add " << s << ' ' << id << endl;
    int u = 1;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i] - '0';
        if (!to[u][c]) {
            to[u][c] = ++sz;
        }
        u = to[u][c];
        /*if (ending[u] != -1) {
            update(ending[u], id);
        }*/
        for (int id2 : ending[u]) if (id != id2) {
            update(id2, id);
        }
    }
    ending[u].push_back(id);
    if (ending[u].size() > s.size() * 2) {
        cout << "NO\n";
        exit(0);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    init();

    cin >> n;
    s.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i].first;
        s[i].second = i;
    }

    sort(begin(s), end(s), [](const pair<string, int> &a, const pair<string, int> &b){
        return a.first.size() < b.first.size();
    });

    for (int i = 0; i < n; ++i) {
        unknown_pos[i] = -1;
        for (int j = 0; j < s[i].first.size(); ++j) {
            if (s[i].first[j] == '?') {
                unknown_pos[i] = j;
                break;
            }
        }
    }

    sz = 1;
    for (int i = 0; i < n; ++i) {
        if (unknown_pos[i] != -1) {
            s[i].first[unknown_pos[i]] = '0';
            add(s[i].first, i);
            s[i].first[unknown_pos[i]] = '1';
            add(s[i].first, i);
            s[i].first[unknown_pos[i]] = '?';
        } else {
            add(s[i].first, i);
        }
    }

    if (solve()) {
        cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            if (unknown_pos[i] != -1) s[i].first[unknown_pos[i]] = color[i] + '0';
        }
        sort(begin(s), end(s), [](const pair<string, int> &a, const pair<string, int> &b){
            return a.second < b.second;
        });
        for (int i = 0; i < n; ++i) {
            cout << s[i].first << '\n';
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}