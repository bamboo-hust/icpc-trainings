#include <bits/stdc++.h>

using namespace std;

const int N = 50050;
const int M = 250500;

struct Edge {
    int u, v;
    int a, b;
    bool in_cycle;

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

    bool operator == (const Point &o) const {
        return x == o.x && y == o.y;
    }
};

bool ccw(const Point &a, const Point &b, const Point &c) {
    return (b - a) % (c - a) >= 0;
}
bool cw(const Point &a, const Point &b, const Point &c) {
    return (b - a) % (c - a) <= 0;
}

using Polygon = vector<Point>;

struct CmpSize {
    bool operator () (const Polygon &a, const Polygon &b) const {
        return a.size() < b.size();
    }
};

int n, m;
vector<int> edges;
int was[N];
int timestamp;
vector<int> a[N];

multiset<Polygon, CmpSize> hulls;

Polygon convex_hull(Polygon &a) {
    Polygon H;
    sort(begin(a), end(a));
    for (int i = 0; i < a.size(); ++i) {
        while (H.size() >= 2 && cw(H[H.size() - 2], H[H.size() - 1], a[i])) H.pop_back();
        if (H.empty() || a[i].y < H.back().y) H.push_back(a[i]);
    }
    return H;
}

Polygon merge(const Polygon &a, const Polygon &b) {
    if (a.empty()) return b;
    if (b.empty()) return a;
    Point cur = a[0] + b[0];
    int i = 1, j = 1;
    Polygon res;
    res.push_back(cur);
    while (i < a.size() || j < b.size()) {
        Point nxt;
        if (i == a.size()) {
            nxt = b[j] - b[j - 1];
            ++j;
        } else if (j == b.size()) {
            nxt = a[i] - a[i - 1];
            ++i;
        } else {
            if ((a[i] - a[i - 1]) % (b[j] - b[j - 1]) >= 0) {
                nxt = a[i] - a[i - 1];
                ++i;
            } else {
                nxt = b[j] - b[j - 1];
                ++j;
            }
        }
        cur = cur + nxt;
        while (res.size() >= 2 && cw(res[res.size() - 2], res[res.size() - 1], cur)) res.pop_back();
        if (res.empty() || res.back().y > cur.y) res.push_back(cur);
    }
    return res;
}

Polygon normalize(Polygon &c) {
    sort(begin(c), end(c));
    Polygon res;
    for (auto p : c) {
        while (res.size() >= 2 && cw(res[res.size() - 2], res.back(), p)) res.pop_back();
        if (res.empty() || res.back().y > p.y) res.push_back(p);
    }
    return res;
}

Polygon merge_naive(const Polygon &a, const Polygon &b) {
    Polygon c;
    for (auto p : a) for (auto q : b) c.push_back(p + q);
    return normalize(c);
}

void add_new_cycle(int root) {
    int start = edges.size() - 1;
    int cur_node = E[edges.back()].adj(root);
    while (cur_node != root) {
        start--;
        cur_node = E[edges[start]].adj(cur_node);
    }
    int64_t sum_a = 0;
    int64_t sum_b = 0;
    for (int i = start; i < edges.size(); ++i) {
        //cerr << "cycle " << root << ": " << E[edges[i]].u << ' ' << E[edges[i]].v << endl;
        sum_a += E[edges[i]].a;
        sum_b += E[edges[i]].b;
        E[edges[i]].in_cycle = true;
    }
    Polygon P;
    for (int i = start; i < edges.size(); ++i) {
        P.push_back(Point{sum_a - E[edges[i]].a, sum_b - E[edges[i]].b});
    }
    P = convex_hull(P);
    hulls.insert(P);
}

void dfs(int u, int p = 0) {
    was[u] = ++timestamp;
    for (int e : a[u]) {
        int v = E[e].adj(u);
        if (v == p) continue;
        edges.push_back(e);
        if (was[v]) {
            if (was[v] < was[u]) {
                add_new_cycle(v);
            }
        } else {
            dfs(v, u);
        }
        edges.pop_back();
    }
}

Polygon random_hull(int n) {
    const int LIM = 1000000;

    Polygon res;
    res.push_back(Point{rand() % LIM, rand() % LIM});

    for (int i = 0; i < n; ++i) {
        res.push_back(Point{res.back().x + rand() % LIM, res.back().y - rand() % LIM});
    }

    return normalize(res);
}

void stress_merge() {
    for (int it = 0; it < 1000000; ++it) {
        int n = rand() % 10000 + 1;
        int m = rand() % 10000 + 1;
        vector<Point> a = random_hull(m);
        vector<Point> b = random_hull(n);
        cerr << "checking " << a.size() << ' ' << b.size() << endl;
        assert(merge(a, b) == merge_naive(a, b));
    }
}

int main() {
    //stress_merge(); return 0;

    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> E[i].u >> E[i].v >> E[i].a >> E[i].b;
        a[E[i].u].push_back(i);
        a[E[i].v].push_back(i);
    }

    dfs(1);

    while (hulls.size() > 1) {
        auto it = hulls.begin();
        auto it2 = it; it2++;
        Polygon P = merge(*it, *it2);
        hulls.erase(hulls.begin());
        hulls.erase(hulls.begin());
        hulls.insert(P);
    }

    int64_t alpha = 0;
    int64_t beta = 0;
    for (int i = 1; i <= m; ++i) {
        if (!E[i].in_cycle) {
            alpha += E[i].a;
            beta += E[i].b;
        }
    }
    int64_t res = 9e18;
    for (Point p : *hulls.begin()) {
        res = min(res, (alpha + p.x) * (beta + p.y));
    }
    cout << res << endl;
}