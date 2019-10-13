#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define LL long long

using namespace __gnu_pbds;
using namespace std;

const int N = 2e5 + 5;
int n;
int x[N], y[N];

gp_hash_table< int, vector<int> > row, col;

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
    for (auto &it : row) sort(begin(it.second), end(it.second));

    gp_hash_table< int, vector< pair<LL, int> > > all_cnt_cols;
    for (const auto &c : col) {
        int y = c.first;
        LL sum_col = 0;
        for (int x : c.second) {
            sum_col += row[x].size() - 1;
        }
        all_cnt_cols[c.second.size()].push_back(make_pair(sum_col, y));
    }

    for (auto &it : all_cnt_cols) sort(rbegin(it.second), rend(it.second));

    LL res = 0;
    // cnt_row(x) * cnt_col(y) + sum_row(x) + sum_col(y)
    for (const auto &r : row) {
        int x = r.first;
        LL cnt_row = r.second.size();
        LL sum_row = 0;
        for (int y : r.second) {
            sum_row += col[y].size() - 1;
        }
        for (const auto &cnt_col_pair : all_cnt_cols) {
            int cnt_col = cnt_col_pair.first;
            for (const auto it : cnt_col_pair.second) {
                if (!binary_search(begin(r.second), end(r.second), it.second)) {
                    res = max(res, cnt_row * cnt_col + sum_row + it.first);
                    //cerr << x << ' ' << it.second << ' ' << cnt_row << ' ' << cnt_col << ' ' << sum_row << ' ' << it.first << ' ' << res << endl;
                    break;
                }
            }
        }
    }
    return res;
}

LL calc() {
    LL res = 0;
    for (int i = 0; i < n; ++i) {
        res += 1LL * (row[x[i]].size() - 1) * (col[y[i]].size() - 1);
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        row[x[i]].push_back(y[i]);
        col[y[i]].push_back(x[i]);
    }

    LL res = 0;
    res = max(res, solve1());
    //cerr << "solve1 " << res << endl;
    res = max(res, solve2());
    //cerr << "solve2 " << res << endl;
    res += calc();

    cout << res << endl;
}