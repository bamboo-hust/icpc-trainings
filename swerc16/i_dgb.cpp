#include <bits/stdc++.h>

using namespace std;

const int MAXT = 512;
const int MAXN = 205;
const int INF = 1e9;

int a[MAXT][MAXN];
vector<int> path[MAXT];
int edge_id[MAXN][MAXN];
vector<int> edge_weights;
int duration[MAXT];

int num_edges;
int n, alice, rabbit, T;

int inverse[13];

void init_inverse() {
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 13; ++j) if (i * j % 13 == 1) {
            inverse[i] = j;
        }
    }
}

void read() {
    cin >> n >> alice >> rabbit >> T;
    for (int i = 0; i < T; ++i) {
        int p;
        cin >> duration[i] >> p;
        path[i].resize(p);
        for (int j = 0; j < p; ++j) {
            cin >> path[i][j];
            --path[i][j];
        }
    }
}

void init_edges() {
    memset(edge_id, -1, sizeof edge_id);
    for (int i = 0; i < T; ++i) {
        for (int j = 1; j < path[i].size(); ++j) {
            if (edge_id[path[i][j - 1]][path[i][j]] == -1) {
                cerr << "new edge " << path[i][j - 1] << ' ' << path[i][j] << ' ' << num_edges << endl;
                edge_id[path[i][j - 1]][path[i][j]] = edge_id[path[i][j]][path[i][j - 1]] = num_edges++;
            }
        }
    }
}

void prepare_a() {
    for (int i = 0; i < T; ++i) {
        for (int j = 1; j < path[i].size(); ++j) {
            (a[i][edge_id[path[i][j - 1]][path[i][j]]] += 1) %= 13;
        }
        a[i][num_edges] = duration[i];
    }
}

void swap_rows(int u, int v) {
    for (int i = 0; i <= num_edges; ++i) {
        swap(a[u][i], a[v][i]);
    }
}

vector<int> solve() {
    cerr << "matrix\n";
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j <= num_edges; ++j) {
            cerr << a[i][j] << ' ';
        }
        cerr << endl;
    }
    cerr << endl;

    int row = 0;
    vector<int> where(num_edges, -1);
    for (int col = 0; col < num_edges; ++col) {
        if (!a[row][col]) {
            for (int i = row + 1; i < T; ++i) {
                if (a[i][col]) {
                    swap_rows(row, i);
                    break;
                }
            }
        }
        if (!a[row][col]) {
            continue;
        }
        where[col] = row;
        for (int i = row + 1; i < T; ++i) if (a[i][col]) {
            int coeff = (a[i][col] * inverse[a[row][col]]) % 13;
            cerr << coeff << endl;
            for (int j = col; j <= num_edges; ++j) {
                a[i][j] -= a[row][j] * coeff % 13;  
                (a[i][j] += 13) %= 13;
            }
            assert(a[i][col] == 0);
        }
        ++row;

        cerr << "matrix\n";
        for (int i = 0; i < T; ++i) {
            for (int j = 0; j <= num_edges; ++j) {
                cerr << a[i][j] << ' ';
            }
            cerr << endl;
        }
        cerr << endl;
    }

    vector<int> ans(num_edges, 0);
    for (int i = num_edges - 1; i >= 0; --i) {
        ans[i] = a[where[i]][n] * inverse[a[where[i]][i]] % 13;
        for (int j = where[i] - 1; j >= 0; --j) {
            a[j][n] -= ans[i] * a[j][i] % 13;
            (a[j][n] += 13) %= 13;
        }
    }

    return ans;
}

int dijkstra() {
    --alice; --rabbit;
    
    set< pair<int, int> > Q;
    vector<int> d(n, INF);
    d[alice] = 0;
    Q.insert(make_pair(0, alice));
    while (!Q.empty()) {
        int u = Q.begin()->second;
        int du = Q.begin()->first;
        Q.erase(Q.begin());
        if (du != d[u]) continue;
        cerr << "queue " << u << ' ' << d[u] << endl;
        for (int v = 0; v < n; ++v) if (~edge_id[u][v]) {
            if (u == v) continue;
            int c = edge_weights[edge_id[u][v]];
            cerr << "update " << u << ' ' << v << ' ' << c << ' ' << d[u] << ' ' << d[v] << endl;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                Q.insert(make_pair(d[v], v));
            }
        }
    }
    cerr << rabbit << ' ' << d[rabbit] << endl;
    return d[rabbit];
}

int main() {
    ios::sync_with_stdio(false);

    read();
    init_edges();
    prepare_a();
    init_inverse();
    edge_weights = solve();

    for (int i = 0; i < num_edges; ++i) {
        cerr << i << ' ' << edge_weights[i] << endl;
    }

    int res = dijkstra();
    cout << res << endl;

    return 0;
}

new edge 0 1 0
new edge 1 2 1
new edge 0 3 2
new edge 3 1 3
new edge 2 3 4
new edge 0 2 5
new edge 2 4 6
new edge 4 1 7
matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
1 0 0 1 1 1 0 0 11
1 0 1 1 0 0 0 0 4
1 1 1 0 1 1 0 0 6
0 1 1 0 1 0 0 0 7
0 0 0 0 1 0 1 0 11
0 0 0 2 0 0 0 2 12

1
1
1
matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 12 0 1 1 1 0 0 11
0 12 1 1 0 0 0 0 4
0 0 1 0 1 1 0 0 6
0 1 1 0 1 0 0 0 7
0 0 0 0 1 0 1 0 11
0 0 0 2 0 0 0 2 12

12
12
1
matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 0 1 2 1 1 0 0 12
0 0 2 2 0 0 0 0 5
0 0 1 0 1 1 0 0 6
0 0 0 12 1 0 0 0 6
0 0 0 0 1 0 1 0 11
0 0 0 2 0 0 0 2 12

1
2
1
matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 0 0 2 0 0 0 0 6
0 0 0 2 11 11 0 0 6
0 0 0 0 0 0 0 0 0
0 0 0 12 1 0 0 0 6
0 0 0 0 1 0 1 0 11
0 0 0 2 0 0 0 2 12

1
6
1
matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 0 0 2 0 0 0 0 6
0 0 0 0 11 11 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 9
0 0 0 0 1 0 1 0 11
0 0 0 0 0 0 0 2 6

6
6
matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 0 0 2 0 0 0 0 6
0 0 0 0 11 11 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 12 0 0 9
0 0 0 0 0 12 1 0 11
0 0 0 0 0 0 0 2 6

1
matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 0 0 2 0 0 0 0 6
0 0 0 0 11 11 0 0 0
0 0 0 0 0 12 0 0 9
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 2
0 0 0 0 0 0 0 2 6

matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 0 0 2 0 0 0 0 6
0 0 0 0 11 11 0 0 0
0 0 0 0 0 12 0 0 9
0 0 0 0 0 0 1 0 2
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 2 6

matrix
1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1
0 0 1 0 1 1 0 0 6
0 0 0 2 0 0 0 0 6
0 0 0 0 11 11 0 0 0
0 0 0 0 0 12 0 0 9
0 0 0 0 0 0 1 0 2
0 0 0 0 0 0 0 2 6
0 0 0 0 0 0 0 0 0

0 0
1 0
2 0
3 0
4 0
5 1
6 0
7 0
queue 4 0
update 4 1 0 0 1000000000
update 4 2 0 0 1000000000
queue 1 0
update 1 0 0 0 1000000000
update 1 2 0 0 0
update 1 3 0 0 1000000000
update 1 4 0 0 0
queue 0 0
update 0 1 0 0 0
update 0 2 1 0 0
update 0 3 0 0 0
queue 2 0
update 2 0 1 0 0
update 2 1 0 0 0
update 2 3 0 0 0
update 2 4 0 0 0
queue 3 0
update 3 0 0 0 0
update 3 1 0 0 0
update 3 2 0 0 0
0 0
0

