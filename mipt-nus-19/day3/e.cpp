#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 2e5 + 5;

int n;
int x[N], y[N];

map< int, vector<int> > row, col;

LL solve1() {
    LL res = 0;
    for (const auto &r : row) {
        LL cur = 0;
        for (int c : r.second) {
            cur += col[c].size() - 1LL;
        }
        res = max(res, cur);
    }

    for (const auto &c : col) {
        LL cur = 0;
        for (int r : c.second) {
            cur += row[r].size() - 1LL;
        }
        res = max(res, cur);
    }
    return res;
}

LL solve2() {
    vector< pair<int, int> > a;
    for (int i = 0; i < n; ++i) {
        a.push_back(make_pair(x[i], y[i]));
    }
    sort(begin(a), end(a));

    LL res = 0;
    vector< pair<LL, int> > R, C;
    for (const auto &r : row) {
        LL sum_col = 0;
        for (int x : r.second) {
            sum_col += col[x].size() - 1;
        }
        R.push_back(make_pair(sum_col + r.second.size(), r.first));
    }
    for (const auto &c : col) {
        LL sum_row = 0;
        for (int y : c.second) {
            sum_row += row[y].size() - 1;
        }
        C.push_back(make_pair(sum_row + c.second.size(), c.first));
    }
    sort(begin(R), end(R));
    sort(begin(C), end(C));
    vector<int> pos(row.size(), col.size() - 1);
    set< pair<LL, int> > S;
    for (int i = 0; i < R.size(); ++i) {
        S.insert(make_pair(R[i].first + C[pos[i]].first - 1, i));
    }
    while (!S.empty()) {
        LL sum = S.rbegin()->first;
        LL id = S.rbegin()->second;
        S.erase(--S.end());
        if (!binary_search(begin(a), end(a), make_pair(R[id].second, C[pos[id]].second))) {
            return sum;
        }
        if (pos[id] > 0) {
            --pos[id];
            S.insert(make_pair(R[id].first + C[pos[id]].first - 1, id));
        }
    }
    return 0;
}

LL calc() {
    LL res = 0;
    for (int i = 0; i < n; ++i) {
        res += 1LL * (row[x[i]].size() - 1) * (col[y[i]].size() - 1);
    }
    //cerr << "calc " <<res << endl;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        row[x[i]].push_back(y[i]);
        col[y[i]].push_back(x[i]);
    }

    LL res = 0;
    res = max(res, solve1());
    cerr << "solve1 " << res << endl;
    res = max(res, solve2());
    cerr << "solve2 " << res << endl;
    res += calc();

    cout << res << endl;
}