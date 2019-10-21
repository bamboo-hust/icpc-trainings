#include <bits/stdc++.h>

using namespace std;

const int N = 1000;

int L[N];
int R[N];
int color[N];
int n;
vector<int> V;

int solve_duc() {
    vector<int> remain;
    for (int i = 1; i <= n; ++i) remain.push_back(i);
    while (!remain.empty()) {
        vector<int> now;
        vector<int> nxt;
        for (int i = 0; i < remain.size(); ++i) {
            bool ok = true;
            for (int j = 0; j < remain.size(); ++j) if (i != j) {
                if (L[remain[j]] <= L[remain[i]] && R[remain[i]] <= R[remain[j]]) {
                    ok = false;
                    break;
                } 
            }
            if (ok) {
                now.push_back(remain[i]);
            } else {
                nxt.push_back(remain[i]);
            }
        }
        sort(begin(now), end(now), [&] (int x, int y) { return L[x] < L[y]; });
        for (int i : now) {
            for (int x = L[i]; x <= R[i]; ++x) {
                color[x] = i;
            }
        }
        if (remain.size() == nxt.size()) break;
        remain = nxt;
    }
    for (int i : remain) {
        for (int x = L[i]; x <= R[i]; ++x) {
            color[x] = i;
        }
    }
    set<int> got;
    for (int i = 0; i < N; ++i) {
        if (color[i]) got.insert(color[i]);
    }
    return got.size();
}

int solve_duc2() {
    vector<int> remain;
    for (int i = 1; i <= n; ++i) remain.push_back(i);
    while (!remain.empty()) {
        vector<int> now;
        vector<int> nxt;
        for (int i = 0; i < remain.size(); ++i) {
            bool ok = true;
            for (int j = 0; j < remain.size(); ++j) if (i != j) {
                if (L[remain[j]] <= L[remain[i]] && R[remain[i]] <= R[remain[j]]) {
                    ok = false;
                    break;
                } 
            }
            if (ok) {
                now.push_back(remain[i]);
            } else {
                nxt.push_back(remain[i]);
            }
        }
        sort(begin(now), end(now), [&] (int x, int y) { return L[x] > L[y]; });
        for (int i : now) {
            for (int x = L[i]; x <= R[i]; ++x) {
                color[x] = i;
            }
        }
        if (remain.size() == nxt.size()) break;
        remain = nxt;
    }
    for (int i : remain) {
        for (int x = L[i]; x <= R[i]; ++x) {
            color[x] = i;
        }
    }
    set<int> got;
    for (int i = 0; i < N; ++i) {
        if (color[i]) got.insert(color[i]);
    }
    return got.size();
}

int solve_tung() {
    vector<int> order;
    for (int i = 1; i <= n; ++i) order.push_back(i);
    sort(begin(order), end(order), [&] (int x, int y) { 
        if (L[x] != L[y]) return L[x] < L[y];
        return R[x] > R[y];
    });
    memset(color, 0, sizeof color);

    for (int i : order) {
        for (int x = L[i]; x <= R[i]; ++x) {
            color[x] = i;
        }
    }

    set<int> got;
    for (int i = 0; i < N; ++i) {
        if (color[i]) got.insert(color[i]);
    }
    return got.size();
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> L[i] >> R[i];
        V.push_back(L[i]);
        V.push_back(R[i]);
    }
    sort(begin(V), end(V));
    V.resize(unique(begin(V), end(V)) - begin(V));
    for (int i = 1; i <= n; ++i) {
        L[i] = lower_bound(begin(V), end(V), L[i]) - begin(V);
        R[i] = lower_bound(begin(V), end(V), R[i]) - begin(V);
    }
    cout << max(solve_tung(), max(solve_duc(), solve_duc2())) << endl;
}