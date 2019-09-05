#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

int const N = 2e5 + 5;
int const BASE = 1000;

struct Point {
    int x, y, z;
    Point(){};
    Point(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

int n, root[N], ok[N];

pair < int, int > c[N];
vector < int > a[N];
map < int, int > maps[N];

pair < Point, Point > b[N];


void print(int type, bool cycle) {
    if (type == 1) {
        if (cycle) {
            cout << "True closed chains" << endl;
            return;
        } else {
            cout << "No true closed chains" << endl;
        }
        return;
    }
    if (cycle) {
        cout << "Floor closed chains" << endl;
        return;
    }
    cout << "No floor closed chains" << endl;

}

int get_root(int u) {
    if (root[u] == 0) {
        return u;
    }
    return root[u] = get_root(root[u]);
}

int get_3(Point p) {
    return p.x * BASE * BASE + p.y * BASE + p.z;
}

int get_2(Point p) {
    return p.x * BASE + p.y;
}


bool dfs(int u, int pre) {
    ok[u] = 1;
    for (int v : a[u]) {
        if (v == pre) {
            continue;
        }
        if (ok[v] == 1) {
            return true;
        }
        if (dfs(v, u)) {
            return true;
        }
    }
    return false;
}

void solve(int type) {
    map < int , int > num;
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (type == 1) {
            c[i].f = get_3(b[i].f);
            c[i].s = get_3(b[i].s);
        } else {
            c[i].f = get_2(b[i].f);
            c[i].s = get_2(b[i].s);
        }
    }

    for (int i = 1; i <= 2 * n; i++) {
        root[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (num[c[i].f] == 0) {
            num[c[i].f] = ++cnt;
        }
        if (num[c[i].s] == 0) {
            num[c[i].s] = ++cnt;
        }
    }

    for (int i = 1; i <= cnt; i++) {
        a[i].clear();
        ok[i] = 0;
        maps[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        int u = num[c[i].f];
        int v = num[c[i].s];
        if (u != v && maps[u][v] == 0) {
            maps[u][v] = maps[v][u] = 1;
            a[u].push_back(v);
            a[v].push_back(u);
        }
    }

    bool cycle = dfs(1, -1);
    print(type, cycle);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        b[i].f = Point(x1, y1, z1);
        b[i].s = Point(x2, y2, z2);
    }
    solve(1);
    solve(2);
}