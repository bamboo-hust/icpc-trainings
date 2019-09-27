#include <bits/stdc++.h>

using namespace std;

const int N = 2048;
const int M = 2048;
const int UNI = 0;
const int BOTH = 1;

vector< pair<int, int> > a[N];
vector< pair<int, int> > in_edge[N];
vector< pair<int, int> > saveA[N];

int from[M], to[M], forw[M], backward[M];
bool used[M];
bool visited[N];
int n, m;

int adj(int u, int e) {
    return from[e] ^ to[e] ^ u;
}

vector<int> cur_path;
bool reached[N];
void dfs(int u, int target, vector<int> &path) {
    //cerr << "dfs " << u << ' ' << target << endl;
    reached[u] = true;
    if (path.size()) return;
    if (u == target) {
        //cerr << "finised " << endl;
        path = cur_path;
        assert(path.size());
        return;
    }
    //while (a[u].size() && used[a[u].back().second]) a[u].pop_back();
    //cerr << "mid dfs " << u << ' ' << a[u].size() << endl;
    while (a[u].size()) {
        int e = a[u].back().second;
        int v = adj(u, e);
        a[u].pop_back();
        if (used[e]) {
            //cerr << "dfs used "<< u << ' ' <<v<<endl;
            continue;
        }
        //cerr << "dfs try " << u << ' ' << v << endl;
        if (reached[v]) continue;
        cur_path.push_back(e);
        dfs(v, target, path);
        if (path.size()) return;
        cur_path.pop_back();
    }
}

vector<int> find_one_cycle(int u, int edge_id) {
    //cerr << "try find_one_cycle " << u << ' ' << adj(u, edge_id) << endl;
    for (int i = 1; i <= n; ++i) saveA[i] = a[i];
    used[edge_id] = true;
    cur_path.clear();
    vector<int> cycle;
    for (int i = 1; i <= n; ++i) reached[i] = false;
    dfs(u, adj(u, edge_id), cycle);
    used[edge_id] = false;
    for (int i = 1; i <= n; ++i) a[i] = saveA[i];
    //cerr << "done dfs " << endl;
    if (cycle.empty()) return vector<int>();
    cycle.push_back(edge_id);
    return cycle;
}

void include_cycle(vector<int> &res, queue<int> &Q, int u, const vector<int> &cycle) {
    //cerr << "begin include_cycle " << cycle.size() << endl;
    int cur = 1;
    if (cur == u) {
        res.insert(res.begin(), cycle.begin(), cycle.end());
    } else {
        for (int i = 0; i < res.size(); ++i) {
            //cerr << "cur " << cur << endl;
            int nxt = adj(cur, res[i]);
            cur = nxt;
            if (cur == u) {
                //cerr << "found place to insert" << endl;
                res.insert(res.begin() + i + 1, cycle.begin(), cycle.end());
                break;
            }
        }
    }
//    cerr << "res\n";
//    cur = 1;
//    for (int v : res) {
//        cerr << cur << ' ' << adj(cur, v) << endl;
//        cur = adj(cur, v);
//    }

    for (int i = 0; i < cycle.size(); ++i) {
        used[cycle[i]] = true;
        u = adj(u, cycle[i]);
        if (!visited[u]) {
            visited[u] = true;
            Q.push(u);
        }
    }
    //cerr << "done include_cycle " << cycle.size() << endl;
}

vector<int> find_euler_cycle() {
    queue<int> Q;
    Q.push(1);
    visited[1] = true;
    vector<int> res;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        //cerr << "start from " << u << endl;
        vector<int> remain;
        while (in_edge[u].size()) {
            auto e = in_edge[u].back();
            in_edge[u].pop_back();
            if (used[e.second]) continue;
            //cerr << "using edge " << u << ' ' << adj(u, e.second) << endl;
            vector<int> cycle = find_one_cycle(u, e.second);
            if (cycle.empty()) {
                //cerr << "empty cycle " << endl;
                //return vector<int>();
                remain.push_back(e.second);
                continue;
            }
            include_cycle(res, Q, u, cycle);
            assert(res.size() >= cycle.size());
        }
        while (a[u].size() && used[a[u].back().second]) a[u].pop_back();
        while (remain.size() && used[remain.back()]) remain.pop_back();
        if (a[u].size() || remain.size()) {
            //cerr << "fail " << u << ' ' << a[u].size() << ' ' << remain.size() << endl;
            return vector<int>();
        }
    }
    //cerr << "found cycle " << res.size() << endl;
    return res;
}

vector<int> find_euler_cycle(int limit) {
    ///cerr << "find_euler_cycle limit=" << limit << endl;
    for (int i = 1; i <= n; ++i) {
        a[i].clear();
        in_edge[i].clear();
        saveA[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
        if (max(forw[i], backward[i]) <= limit) {
            a[from[i]].push_back(make_pair(BOTH, i));
            a[to[i]].push_back(make_pair(BOTH, i));
            in_edge[from[i]].push_back(make_pair(BOTH, i));
            in_edge[to[i]].push_back(make_pair(BOTH, i));
        } else if (forw[i] <= limit) {
            a[from[i]].push_back(make_pair(UNI, i));
            in_edge[to[i]].push_back(make_pair(UNI, i));
        } else if (backward[i] <= limit) {
            a[to[i]].push_back(make_pair(UNI, i));
            in_edge[from[i]].push_back(make_pair(UNI, i));
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (a[i].size() - )
    }

    for (int i = 1; i <= n; ++i) {
        sort(begin(in_edge[i]), end(in_edge[i]));
    }
    for (int i = 1; i <= n; ++i) {
        visited[i] = false;
        reached[i] = false;
    }
    for (int i = 1; i <= m; ++i) {
        used[i] = false;
    }

    return find_euler_cycle();
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> from[i] >> to[i] >> forw[i] >> backward[i];
    }

    int l = 1, r = 1 << 10;
    int mincost = 1 << 10;
    vector<int> res;
    while (l <= r) {
        int mid = l + r >> 1;
        vector<int> cur = find_euler_cycle(mid);
        assert(cur.size() <= m);
        if (cur.size() == m) {
            for (int i = 1; i <= m; ++i) assert(used[i]);
            mincost = mid;
            res = cur;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (mincost > 1000) {
        cout << "NIE" << endl;
        return 0;
    }
    cout << mincost << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << ' ';
    }
    cout << endl;
    return 0;
}