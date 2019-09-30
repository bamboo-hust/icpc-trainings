//
// Created by quanglm1998 on 27/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
const int K = 1010;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}

int n, m, k;
pair<int, int> a[K];

void gen() {
    n = rand() % 100 + 1;
    m = rand() % 100 + 1;
    k = rand() % n + 1;
//    cout << n << ' ' << m << ' ' << k << endl;
    for (int i = 1; i <= k; i++) {
        a[i].first = rand() % n + 1;
        a[i].second = rand() % m + 1;
//        cout << a[i].first << ' ' << a[i].second << endl;
    }
}

const int NOW = 200;

int sum[NOW][NOW];

int naive() {
    memset(sum, 0, sizeof sum);
    for (int i = 1; i <= k; i++) {
        sum[a[i].first][a[i].second]++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }

    auto get = [&](int x, int y, int xx, int yy) {
        return sum[xx][yy] - sum[x - 1][yy] - sum[xx][y - 1] + sum[x - 1][y - 1];
    };
    int res = 0;
    for (int x = 1; x <= n; x++) {
        for (int xx = x; xx <= n; xx++) {
            for (int y = 1; y <= m; y++) {
                for (int yy = y; yy <= m; yy++) {
                    int sum = get(x, y, xx, yy);
                    res += (sum > 0);
                }
            }
        }
    }
//    cout << res << endl;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        cin >> a[i].first >> a[i].second;
    }
    srand(time(0));

while (1) {
//    cerr << "start" << endl;
//    gen();
//    int ans = naive();
    sort(a + 1, a + k + 1);
    k = unique(a + 1, a + k + 1) - a - 1;
    int res = 0;
    for (int i = 1; i <= k; i++) {
        auto cmp = [](pair<int, int> u, pair<int, int> v) {
            if (u.second != v.second) return u.second < v.second;
            return u.first < v.first;
        };
        sort(a + 1, a + i, cmp);
        vector<pair<int, int>> left;
        left.push_back({a[i].first, 0});
        for (int j = 1; j < i; j++) {
            if (a[j].second > a[i].second) break;
            while (!left.empty() && left.back().first <= a[j].first) left.pop_back();
            left.push_back(a[j]);
        }
        left.push_back({0, a[i].second});


        vector<pair<int, int>> right;
        right.push_back({a[i].first, m + 1});
        for (int j = i - 1; j > 0; j--) {
            if (a[j].second < a[i].second) break;
            while (!right.empty() && right.back().first <= a[j].first) right.pop_back();
            right.push_back(a[j]);
        }
        right.push_back({0, a[i].second});

//        cerr << "left" << endl;
//        for (auto u : left) cerr << u.first << ' ' << u.second << endl;
//        cerr << "right" << endl;
//        for (auto u : right) cerr << u.first << ' ' << u.second << endl;

        vector<int> vals;
        for (auto u : left) vals.push_back(u.first);
        for (auto u : right) vals.push_back(u.first);
        sort(vals.begin(), vals.end());
        vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
        reverse(vals.begin(), vals.end());
        int curLeft = 0, curRight = 0;
        for (int it = 1; it < vals.size(); it++) {
            while (curLeft < left.size() && left[curLeft].first > vals[it]) curLeft++;
            while (curRight < right.size() && right[curRight].first > vals[it]) curRight++;
            int len = vals[it - 1] - vals[it];
            int l = left[curLeft - 1].second;
            int r = right[curRight - 1].second;
//            cerr << vals[it] << ' ' << len << ' ' << l << ' ' << r << endl;
            int now = mul(a[i].second - l, r - a[i].second);
            now = mul(now, len);
            now = mul(now, n - a[i].first + 1);
            res = add(res, now);
//            cerr << now << endl;
        }
    }
    cout << res << endl;
    return 0;
//        if (res != ans) {
//            cout << n << ' ' << m << ' ' << k << endl;
//            for (int i = 1; i <= k; i++) cout << a[i].first << ' ' << a[i].second << endl;
//            cout << res << ' ' << ans << endl;
//            return 0;
//        }
}

    return 0;
}