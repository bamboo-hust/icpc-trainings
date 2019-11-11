#include <bits/stdc++.h>

using namespace std;

const int N = 1024;
const int INF = 1e9;

struct Graph {
    vector< pair<int, int> > a[N];

    void add_edge(int u, int v, int c) {
        // x[u] - x[v] <= c
        a[v].push_back(make_pair(u, c));
    }

    int spfa(int s, int t) {
        queue<int> Q;
        bitset<N> inqueue;
        vector<int> d(N, INF);
        d[s] = 0;
        Q.push(s); inqueue[s] = 1;

        while (!Q.empty()) {
            int u = Q.front(); Q.pop(); inqueue[u] = 0;
            for (auto e : a[u]) {
                int v = e.first;
                int c = e.second;
                if (d[v] > d[u] + c) {
                    d[v] = d[u] + c;
                }
            }
        }

        return d[t];
    }
};

int rainnyDays(int n, vector< vector<int> > predictions) {
    for (int i = 1; i <= n; ++i) {
        G.add_edge(i, i - 1, 1);
        G.add_edge(i - 1, i, 0);
    }
    
    for (auto it : predictions) {
        int l = it[0];
        int r = it[1];
        int k = it[2];
        G.add_edge(r, l - 1, k);
        G.add_edge(l - 1, r, -k);
    }

    int max_sum = abs(G.spfa(0, n));
    int min_sum = abs(G.spfa(n, 0));

    return max_sum + min_sum;
}


int main() {
    cout << rainnyDays(3, {{1,2,1},{2,3, 1}}) << endl;;
}