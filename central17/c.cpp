#include <bits/stdc++.h>

using namespace std;

const int N =  100010, MAX = 5000000;
const long long INF = (1ll << 60);

int n;
int a[N];
long long s[N];
int  ver[N], curVer = 0;

struct Node {
    long long mx, mn, res, add;
    int cl, cr;

    Node(long long mx = -INF, long long mn = INF, long long res = -INF, long long add = 0, int cl = -1, int cr = -1) {
        this->mx = mx;
        this->mn = mn;
        this->res = res;
        this->add = add;
        this->cl = cl;
        this->cr = cr;
    }
} t[MAX];
int curNode = 0;

void update(int curNode) {
    int p1 = t[curNode].cl;
    int p2 = t[curNode].cr;
    if (p1 == -1) {
        t[curNode].mx += t[curNode].add;
        t[curNode].mn += t[curNode].add;
        return;        
    }  
    t[curNode].mx = max(t[p1].mx, t[p2].mx) + t[curNode].add;
    t[curNode].mn = min(t[p1].mn, t[p2].mn) + t[curNode].add;
    t[curNode].res = max(t[p1].res, t[p2].res);
    t[curNode].res = max(t[curNode].res, t[p2].mx - t[p1].mn);
}

int init(int l, int r) {
    if (l == r) {
        curNode++;
        t[curNode].mx = t[curNode].mn = s[l];
        return curNode;
    }
    int m = (l + r) >> 1;
    int p1 = init(l, m);
    int p2 = init(m + 1, r);
    curNode++;
    t[curNode].cl = p1;
    t[curNode].cr = p2;
    update(curNode);
    return curNode;
}

set<pair<int, int> > val[N];

int update(int node, int l, int r, int x, int y, int v) {
    if (x > r || y < l) {
        return node;
    }
    if (x <= l && r <= y) {
        curNode++;
        t[curNode] = t[node];
        t[curNode].add += v;
        update(curNode);
        return curNode;
    }
    int m = (l + r) >> 1;
    int p1 = update(t[node].cl, l, m, x, y, v);
    int p2 = update(t[node].cr, m + 1, r, x, y, v);
    curNode++;
    t[curNode] = t[node];
    t[curNode].cl = p1;
    t[curNode].cr = p2;
    update(curNode);
    return curNode;
}

Node getMax(int node, int l, int r, int x, int y) {
    Node foo;
    if (x > r || y < l) {
        return foo;
    }
    if (x <= l && r <= y) {
        return t[node];
    }
    int m = (l + r) >> 1;
    Node p1 = getMax(t[node].cl, l, m, x, y);
    Node p2 = getMax(t[node].cr, m + 1, r, x, y);
    foo.add =  t[node].add;
    foo.mx = max(p1.mx, p2.mx) + foo.add;
    foo.mn = min(p1.mn, p2.mn) + foo.add;
    foo.res = max(p1.res, p2.res);
    foo.res = max(foo.res, p2.mx - p1.mn);
    return foo;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int m;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        a[i] = u;
        s[i] = s[i - 1] + u;
    }
    ver[0] = init(0, n);
    cin >> m;
    //cout << t[3].mn << " " << t[3].mx << " " << t[3].res << endl;
    //cout << t[2].mn << " " << t[2].mx << " " << t[2].res << endl;
    //cout << t[1].mn << " " << t[1].mx << " " << t[1].res << endl;
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int v, x;
            cin >> x >> v;
            long long oldVal = getMax(ver[i - 1], 0, n, x - 1, x).res;
            //cout << oldVal << endl;
            ver[i] = update(ver[i - 1], 0, n, x, n, v - oldVal);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
            long long res = getMax(ver[i - 1], 0, n, l - 1, r).res;
            cout << res << "\n";
            ver[i] = ver[i - 1];
        } else {
            int k;
            cin >> k;
            ver[i] = ver[k];
        }
    }
    return 0;
}