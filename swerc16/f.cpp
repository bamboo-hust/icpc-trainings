#include <bits/stdc++.h>

using namespace std;

int const N = 1e5 + 5;

struct Employee {
    int r, t, id;
    Employee(){};
    Employee(int _r, int _t, int _id) {
        r = _r;
        t = _t;
        id = _id;
    }
};

Employee e[N];

bool cmp(Employee p, Employee q) {
    return p.r < q.r;
}

struct BIT {
    long long tree[N];
    void update(int x, int val) {
        while (x < N) {
            tree[x] += val;
            x += x & (-x);
        }
    }

    long long get(int x) {
        long long res = 0;
        while (x) {
            res += tree[x];
            x -= x & (-x);
        }
        return res;
    }
};


BIT T;

long long ans[N];

int n, in[N], out[N], tot;
vector < int > a[N];


void dfs(int u, int pre) {
    in[u] = ++tot;
    for (int v : a[u]) {
        if (v == pre) {
            continue;
        }
        dfs(v, u);
    }
    out[u] = tot;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    int root = 0;
    for (int i = 1; i <= n; i++) {
        int p, rank, time;
        cin >> p >> rank >> time;
        if (p == -1) {
            root = i;
        } else {
            a[p].push_back(i);
        }
        e[i] = Employee(rank, time, i);
    }

    dfs(root, -1);
    sort(e + 1, e + n + 1, cmp);
    for (int i = 1; i <= n;) {
        int pos = i;
        while (pos <= n && e[pos].r == e[i].r) {
            pos++;
        }

        for (int j = i; j < pos; j++) {
            int starts = in[e[j].id];
            int ends = out[e[j].id];
            //cout << "get : " << starts << " " << ends << " " << T.get(ends) << endl;
            ans[e[j].id] = T.get(ends) - T.get(starts - 1);
        }

        for (int j = i; j < pos; j++) {
            //cout << "update : " << in[e[j].id] << " " << e[j].t << endl;
            T.update(in[e[j].id], e[j].t);
        }

        i = pos;
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
}