#include <bits/stdc++.h>

using namespace std;

const int N = 220;
const int INF = 1e9;

struct Edge {
    int to, cost;
};

struct Node {
    int u;
    int first;
    int second;

    bool operator < (const Node &o) const {
        if (first != o.first) return first > o.first;
        if (second != o.second) return second > o.second;
        return u < o.u;
    }
};

int n, m;
vector<Edge> a[N];
int d1[N], d2[N];
double res = -1;

bool push(Node &u, int l) {
    int f = 0;
    if (u.second > l) {
        swap(u.second, l);
        f = 1;
    }
    if (u.first > u.second) {
        swap(u.first, u.second);
        f = 1;
    }
    return f;
}

void go(int source) {
    priority_queue< pair < int, int > > Q;
    for (int i = 1; i <= n; ++i) {
        d1[i] = d2[i] = INF;
    }
    d1[source] = 0;
    d2[source] = INF;
    Q.push(make_pair(0, source));
    
    while (!Q.empty()) {
        pair < int, int > P = Q.top(); Q.pop();
        if(d1[P.second] != -P.first)    continue;
        int u = P.second;
        for(int i=0; i<a[u].size(); i++){
            int v = a[u][i].to;
            int cost = a[u][i].cost;
            if(d1[v] > d1[u] + cost){
                d2[v] = d1[v];
                d1[v] = d1[u] + cost;
                Q.push(make_pair(-d1[v], v));
            }
            else{
                if(d2[v] > d1[u] + cost){
                    d2[v] = d1[u] + cost;
                }
            }


        }
    }
    for (int i = 1; i <= n; i++) {
        if (d1[i] == INF || i == source || d2[i] == INF) {
            continue;
        }
        res = max(res, 1. * d2[i] / d1[i]);
    }
}

int main() {
   // freopen("a.in", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back({v, w});
        a[v].push_back({u, w});
    }
    cout << a[1].size() << endl;
    for (int i = 1; i <= n; i++) {
        go(i);
    }
    if (res < 0) {
        puts("-1");
    } else {
        printf("%0.6f\n", res);
    }
    return 0;
}