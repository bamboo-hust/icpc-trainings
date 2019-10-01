#include <bits/stdc++.h>

using namespace std;

const int N = 50050;
const int M = 250500;

struct Edge {
    int u, v;
    int a, b;

    int adj(int w) {
        return u ^ v ^ w;
    }
} E[M];

struct Point {
    int64_t x, y;

    Point operator + (const Point &o) const { return Point{x + o.x, y + o.y}; }
    Point operator - (const Point &o) const { return Point{x - o.x, y - o.y}; }
    int64_t operator % (const Point &o) const { return x * o.y - y * o.x; }

    bool operator < (const Point &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

bool ccw(const Point &a, const Point &b, const Point &c) {
    return (b - a) % (c - a) >= 0;
}

using Polygon = vector<Point>;

int n, m;
vector<int> edges;
int was[N];
int timestamp;
vector<int> a[N];

vector<Polygon> hulls;

Polygon convex_hull(Polygon &a) {
    Polygon H;
    sort(begin(a), end(a));
    for (int i = 0; i < a.size(); ++i) {
        while (H.size() >= 2 && ccw(H[H.size() - 2], H[H.size() - 1], a[i])) H.pop_back();
        H.push_back(a[i]);
    }
    for (int i = (int)a.size() - 2, t = H.size(); i >= 0; --i) {
        while (H.size() > t && ccw(H[H.size() - 2], H[H.size() - 1], a[i])) H.pop_back();
        H.push_back(a[i]);
    }
    H.pop_back();
    cerr << "convex_hull\n";
    for (auto p : H) {
        cerr << p.x << ' ' << p.y << endl;
    }
    cerr << endl;
    return H;
}

void add_new_cycle(int root) {
    int start = edges.size() - 1;
    int cur_node = E[edges.back()].adj(root);
    cerr << "new cycle " << root << endl;
    while (cur_node != root) {
        start--;
        assert(start >= 0);
        cerr << cur_node << endl;
        cur_node = E[edges[start]].adj(cur_node);
        cerr << "here\n";
    }
    cerr << endl;
    int64_t sum_a = 0;
    int64_t sum_b = 0;
    for (int i = start; i < edges.size(); ++i) {
        sum_a += E[edges[i]].a;
        sum_b += E[edges[i]].b;
    }
    Polygon P;
    for (int i = start; i < edges.size(); ++i) {
        P.push_back(Point{sum_a - E[edges[i]].a, sum_b - E[edges[i]].b});
    }
    hulls.push_back(convex_hull(P));
}

void dfs(int u, int p = 0) {
    cerr << "dfs " << u << ' ' << p << endl;
    was[u] = ++timestamp;
    for (int e : a[u]) {
        int v = E[e].adj(u);
        if (v == p) continue;
        edges.push_back(e);
        if (was[v]) {
            if (was[v] < was[u]) add_new_cycle(v);
        } else {
            dfs(v, u);
        }
        edges.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> E[i].u >> E[i].v >> E[i].a >> E[i].b;
        a[E[i].u].push_back(i);
        a[E[i].v].push_back(i);
    }

    dfs(1);
}