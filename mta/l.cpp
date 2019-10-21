#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int m, n, k;
vector<int> a[N];
pair<int, int> b[N];
vector< pair<int, int> > desks;
long long res = 0;

bool cmp(pair<int, int> u, pair<int, int> v) {
    if (u.first != v.first) return u.first < v.first;
    return u.second > v.second;
}

vector<int> vals;

const int V = 1e6;

int getPos(int u) {
    return lower_bound(vals.begin(), vals.end(), u) - vals.begin();
}

struct BIT {
    long long t[V];

    void add(int x, int v) {
        while (x < V) {
            t[x] += v;
            x += x & -x;
        }
    }

    long long get(int x) {
        long long res = 0;
        while (x) {
            res += t[x];
            x -= x & -x;
        }
        return res;
    }

    long long get(int l, int r) {
        return get(r) - get(l - 1);
    }
} sumT, idT;

long long getVal(int deskId) {
    long long sumSmaller = sumT.get(desks[deskId].first - 1);
    int cntSmaller = idT.get(desks[deskId].first - 1);
    long long sumBigger = sumT.get(desks[deskId].second + 1, V - 1);
    int cntBigger = idT.get(desks[deskId].second + 1, V - 1);
    return 1ll * cntSmaller * vals[desks[deskId].first] - sumSmaller 
            + sumBigger - 1ll * cntBigger * vals[desks[deskId].second];
}

void go(int l, int r, int optL, int optR) {
    int mid = l + r >> 1;
    int optM = optL;
    long long optVal = 1e18;


    for (int i = 1; i <= m; i++) {
        sumT.add(a[i][mid * 2], vals[a[i][mid * 2]]);
        sumT.add(a[i][mid * 2 + 1], vals[a[i][mid * 2 + 1]]);
        idT.add(a[i][mid * 2], 1);
        idT.add(a[i][mid * 2 + 1], 1);
    }

    for (int i = optL; i <= optR; i++) {
        long long now = getVal(i);
        if (now < optVal) {
            optVal = now;
            optM = i;
        }
    }

    for (int i = 1; i <= m; i++) {
        sumT.add(a[i][mid * 2], -vals[a[i][mid * 2]]);
        sumT.add(a[i][mid * 2 + 1], -vals[a[i][mid * 2 + 1]]);
        idT.add(a[i][mid * 2], -1);
        idT.add(a[i][mid * 2 + 1], -1);
    }

    res += optVal;
    if (l < mid) go(l, mid - 1, optL, optM);
    if (mid < r) go(mid + 1, r, optM, optR);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> b[i].first >> b[i].second;
    }
    sort(b + 1, b + k + 1, cmp);
    for (int i = 1; i <= k; i++) {
        if (desks.empty() || desks.back().second < b[i].second) desks.push_back(b[i]);
    }
    for (int i = 0; i < desks.size(); i++) {
        vals.push_back(desks[i].first);
        vals.push_back(desks[i].second);
    }

    for (int i = 1; i <= m; i++) {
        a[i].resize(n * 2);
        for (int j = 0; j < n * 2; j++) cin >> a[i][j];
        sort(a[i].begin(), a[i].end());
        for (int j = 0; j < n * 2; j++) vals.push_back(a[i][j]);
    }

    vals.push_back(0);
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (int i = 0; i < desks.size(); i++) {
        desks[i].first = getPos(desks[i].first);
        desks[i].second = getPos(desks[i].second);
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n * 2; j++) {
            a[i][j] = getPos(a[i][j]);
        }
    }

    go(0, n - 1, 0, desks.size() - 1);
    cout << res << endl;
    return 0;
}