#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, k;

struct Data {
    int id, x, y;
    Data() {
        id = x = y = 0;
    }
    Data(int id, int x, int y) {
        this->id = id;
        this->x = x;
        this->y = y;
    }
};

vector<Data> a[N];
int t[N * 4], add[N * 4];

void update(int node, int l, int r, int x, int y, int v) {
    if (x > r || y < l) {
        return;
    }
    if (x <= l && r <= y) {
        t[node] += v;
        add[node] += v;
        return;
    }
    int m = (l + r) >> 1;
    update(node << 1, l, m, x, y, v);
    update(node << 1 | 1, m + 1, r, x, y, v);
    t[node] = max(t[node << 1], t[node << 1 | 1]) + add[node];
}

int main() {
    int foo;
    scanf("%d %d %d", &foo, &n, &k);
    foo += k;
    for (int i = 1; i <= n; i++) {
        int x, y, yy, xx;
        scanf("%d %d %d %d", &x, &y, &xx, &yy);
        xx += k - 1;
        yy += k - 1;
        a[x].push_back(Data(1, y, yy));
        a[xx + 1].push_back(Data(-1, y, yy));
    }
    int res = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < a[i].size(); j++) {
            Data u = a[i][j];
            update(1, 1, foo, u.x, u.y, u.id);
        }
        res = max(res, t[1]);
    }
    cout << res << endl;
    return 0;
}