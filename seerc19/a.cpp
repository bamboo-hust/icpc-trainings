#include <bits/stdc++.h>

using namespace std;

const int N = 400010;

int n, m;
int a[N];
vector<int> ls[N];
int res[N];

struct BIT {
    int t[N];
    void add(int x, int v) {
        while (x < N) {
            t[x] += v;
            x += x & -x;
        }
    }
    int get(int x) {
        int res = 0;
        while (x) {
            res += t[x];
            x -= x & -x;
        }
        return res;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
} t;

set<pair<int, int>> s;

bool inside(int u, pair<int, int> v) {
    return v.first <= u && u <= v.second;
}

void removeFromSet(pair<int, int> u) {
    t.add(u.first, -(u.second - u.first + 1) / 2);
    s.erase(u);
}

void addToSet(pair<int, int> u) {
    if (u.first > u.second) return;
    t.add(u.first, (u.second - u.first + 1) / 2);
    s.insert(u);
}

void remove(int u) {
    auto it = s.lower_bound({u + 1, 0});
    if (it == s.begin()) return;
    it--;
    auto range = *it;
    if (!inside(u, range)) return;
    removeFromSet(range);
    addToSet({range.first, u - 1});
    addToSet({u + 1, range.second});
}

void add(int u) {
    pair<int, int> curRange(u, u);
    if (a[u - 1] > a[u]) {
        auto it = s.lower_bound({u, 0});
        assert(it != s.begin());
        it--;
        auto range = *it;
        removeFromSet(range);
        curRange = {range.first, curRange.second};
    }
    if (a[u + 1] > a[u]) {
        auto it = s.lower_bound({u + 1, 0});
        assert(it != s.end());
        auto range = *it;
        removeFromSet(range);
        curRange = {curRange.first, range.second};
    }
    addToSet(curRange);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
        ls[a[i]].push_back(i);
        s.insert({i, i});
        s.insert({i + n, i + n});
    }
    for (int i = 1; i <= m; i++) {
        if (ls[i].empty()) {
            cout << -1 << ' ';
            continue;
        }
        // remove
        for (int u : ls[i]) {
            remove(u);
            remove(u + n);
        }
        
        // get res
        int firstPos = ls[i][0];
        cout << n - ls[i].size() + t.get(firstPos, firstPos + n) << ' ';
        // add   
        for (int u : ls[i]) {
            add(u);
            add(u + n);
        }
    }
    cout << endl;
    return 0;  
}