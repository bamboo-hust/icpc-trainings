#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int B = sqrt(3 * N / 8);
const int N_BLOCK = N / B + 10;

int n, q;
int a[N];

struct Block {
    int l, r;
    long long sum;
    vector<pair<int, int>> ls;
    Block() {
        l = N, r = -1;
        sum = 0;
    }
    void add(int u) {
        l = min(l, u);
        r = max(r, u);
        ls.push_back({a[u], u});
        sum += a[u];
    }
    void build() {
        sort(ls.begin(), ls.end());
    }
} b[N_BLOCK];

long long sumA;
int numBlock;
long long res[N];
long long prefSum[N], val[N];
pair<int, int> c[N];

struct Query {
    int l, r, id;
};

vector<Query> queries[N_BLOCK];

void addQuery(int x, int y, int id) {
    if (x < 0 || y < 0) return;
    int bx = x / B;
    int by = y / B;
    if (bx) queries[bx - 1].push_back({0, y, id});
    if (by) queries[by - 1].push_back({b[bx].l, x, id});
    long long curRes = 0;
    long long totSum = 0, totCnt = 0;
    for (auto u : b[by].ls) {
        if (u.second <= y) {
            totSum += u.first;
            totCnt++;
        }
    }
    long long sum = 0, cnt = 0;
    int curX = 0, curY = 0;
    for (auto u : b[bx].ls) {
        if (u.second > x) continue;
        while (curY < b[by].ls.size() && b[by].ls[curY].first <= u.first) {
            if (b[by].ls[curY].second <= y) {
                sum += b[by].ls[curY].first;
                cnt++;
            }
            curY++;
        }
        curRes += cnt * u.first - sum;
        curRes += (totSum - sum) - (totCnt - cnt) * u.first;
    }
    if (id < 0) res[~id] -= curRes;
    else res[id] += curRes;
}   

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        c[i] = {a[i], i};
        b[i / B].add(i);
    }
    sort(c, c + n);
    numBlock = (n - 1) / B + 1;
    for (int i = 0; i < numBlock; i++) {
        b[i].build();
    }
    for (int i = 0; i < q; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        l1--, r1--, l2--, r2--;
        addQuery(r1, r2, i);
        addQuery(l1 - 1, r2, ~i);
        addQuery(r1, l2 - 1, ~i);
        addQuery(l1 - 1, l2 - 1, i);
    }
    for (int i = 0; i < n; i++) prefSum[i] = 0;
    for (int i = 0; i < numBlock; i++) {
        long long totSum = b[i].sum, totCnt = b[i].r - b[i].l + 1;
        int cur = 0;
        long long sum = 0, cnt = 0;
        for (int j = 0; j < n; j++) {
            while (cur < b[i].ls.size() && b[i].ls[cur].first <= c[j].first) {
                sum += b[i].ls[cur].first;
                cnt++;
                cur++;
            }
            val[c[j].second] = cnt * c[j].first - sum + (totSum - sum) - (totCnt - cnt) * c[j].first;
        }
        for (int j = 1; j < n; j++) {
            val[j] += val[j - 1];
        }
        for (int j = 0; j < n; j++) {
            prefSum[j] += val[j];
        }

        for (auto u : queries[i]) {
            long long now = prefSum[u.r] - (u.l ? prefSum[u.l - 1] : 0);
            if (u.id < 0) res[~u.id] -= now;
            else res[u.id] += now;
        }
    }   
    for (int i = 0; i < q; i++) cout << res[i] << '\n';
    return 0;
}