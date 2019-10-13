#include <bits/stdc++.h>

using namespace std;

struct BipartiteGraph {
    vector< vector<int> > a;
    vector<int> match;
    vector<bool> was;
    int m, n;
 
    BipartiteGraph(int m, int n) {
        // zero-indexed
        this->m = m; this->n = n;
        a.resize(m);
        match.assign(n, -1);
        was.assign(n, false);
    }
 
    void addEdge(int u, int v) {
        a[u].push_back(v);
    }
 
    bool dfs(int u) {
        for (int v : a[u]) if (!was[v]) {
            was[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }
 
    int maximumMatching() {
        vector<int> buffer;
        for (int i = 0; i < m; ++i) buffer.push_back(i);
        bool stop = false;
        int ans = 0;
        do {
            stop = true;
            for (int i = 0; i < n; ++i) was[i] = false;
            for (int i = (int)buffer.size() - 1; i >= 0; --i) {
                int u = buffer[i];
                if (dfs(u)) {
                    ++ans;
                    stop = false;
                    buffer[i] = buffer.back();
                    buffer.pop_back();
                }
            }
        } while (!stop);
        return ans;
    }
};

struct EulerianGraph {
    vector< vector< pair<int, int> > > a;
    int num_edges;

    EulerianGraph(int n) {
        a.resize(n + 1);
        num_edges = 0;
    }

    void add_edge(int u, int v) {
        //cerr << "add_edge " << u << ' ' << v << endl;
        a[u].push_back(make_pair(v, num_edges));
        num_edges++;
    }

    vector<int> get_eulerian_path() {
        vector<int> path;
        vector< pair<int, int> > s;
        vector<bool> was(num_edges);
        s.push_back({1, -1}); // start of eulerian path
        while (!s.empty()) {
            int u = s.back().first;
            int coming_edge = s.back().second;
            bool found = false;
            while (!a[u].empty()) {
                int v = a[u].back().first;
                int e = a[u].back().second;
                a[u].pop_back();
                if (was[e]) continue;
                was[e] = true;
                s.push_back({v, e});
                found = true;
                break; 
            }
            if (!found) {
                path.push_back(coming_edge);
                s.pop_back();
            }
        }
        path.pop_back();
        reverse(path.begin(), path.end());
        return path;
    }
};

struct Edge {
    int u, v, l, p;

    int adj(int w) {
        return u ^ v ^ w;
    }
};

const int N = 2048;


Edge E[N];
int sum[N];
int diff[N];
int out_deg[N];
int n, m;

vector<int> solve(int limit) {
    // cerr << "build_graph " << limit << endl;
    for (int i = 1; i <= n; ++i) {
        sum[i] = 0;
        diff[i] = 0;
    }

    vector< pair<int, int> > directed_edges;
    vector<int> undirected_edges;
    for (int i = 1; i <= m; ++i) {
        if (E[i].l <= limit && E[i].p <= limit) {
            undirected_edges.push_back(i);
            sum[E[i].u]++;
            sum[E[i].v]++;
        } else if (E[i].l <= limit) {
            diff[E[i].u]++;
            diff[E[i].v]--;
            directed_edges.push_back({i, E[i].u});
        } else if (E[i].p <= limit) {
            diff[E[i].u]--;
            diff[E[i].v]++;
            directed_edges.push_back({i, E[i].v});
        }
    }
    int sum_out = 0;
    for (int i = 1; i <= n; ++i) {
        out_deg[i] = (sum[i] - diff[i]) / 2;
        if (out_deg[i] < 0) return vector<int>();
        //cerr << "out_deg " << i << ' ' << out_deg[i] << endl;
        sum_out += out_deg[i];
    }

    // cerr << "undirected_edges\n";
    // for (int e : undirected_edges) {
    //     cerr << e << ' ';
    // }
    // cerr << endl;

    BipartiteGraph G(sum_out, undirected_edges.size());
    vector<int> pos(n + 2);
    for (int i = 2; i <= n; ++i) {
        pos[i] = pos[i - 1] + out_deg[i - 1];
    }
    pos[n + 1] = sum_out;

    // cerr << "pos\n";
    // for (int i = 1; i <= n + 1; ++i) {
    //     cerr << i << ' ' << pos[i] << endl;
    // }
    // cerr << endl;

    vector<int> id(sum_out);
    for (int i = 1; i <= n; ++i) {
        for (int j = pos[i]; j < pos[i + 1]; ++j) {
            id[j] = i;
        }
    }
    int num_undirected = 0;
    for (int i = 1; i <= m; ++i) {
        if (E[i].l <= limit && E[i].p <= limit) {
            for (int j = pos[E[i].u]; j < pos[E[i].u + 1]; ++j) {
                G.addEdge(j, num_undirected);
            }
            for (int j = pos[E[i].v]; j < pos[E[i].v + 1]; ++j) {
                G.addEdge(j, num_undirected);
            }
            num_undirected++;
        }
    }
    int num_matched = G.maximumMatching();
    if (num_matched != undirected_edges.size()) {
        return vector<int>();
    }

    EulerianGraph EG(n);

    for (int i = 0; i < undirected_edges.size(); ++i) {
        EG.add_edge(id[G.match[i]], E[undirected_edges[i]].adj(id[G.match[i]]));
    }
    for (int i = 0; i < directed_edges.size(); ++i) {
        //cerr << "directed_edges\n";
        EG.add_edge(directed_edges[i].second, E[directed_edges[i].first].adj(directed_edges[i].second));
    }
    vector<int> res = EG.get_eulerian_path();
    if (res.size() != m) {
        return vector<int>();
    }
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] < undirected_edges.size()) {
            res[i] = undirected_edges[res[i]];
        } else {
            res[i] = directed_edges[res[i] - undirected_edges.size()].first;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> E[i].u >> E[i].v >> E[i].l >> E[i].p;
    }

    int l = 1, r = 1000;
    vector<int> res;
    int min_wind = INT_MAX;
    while (l <= r) {
        int mid = l + r >> 1;
        vector<int> cur = solve(mid);
        if (cur.size()) {
            // cerr << "found cycle[" << mid << "]: ";
            // for (int e : cur) {
            //     cerr << e << ' ';
            // }
            // cerr << endl;
            min_wind = mid;
            res = cur;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (res.size()) {
        cout << min_wind << endl;
        for (int e : res) {
            cout << e << ' ';
        }
        cout << endl;
    } else {
        cout << "NIE\n";
    }
}