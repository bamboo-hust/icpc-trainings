#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

int n, m, w, h;
int d[N], a[N];
vector<int> res[N];
vector<int> events[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n >> w >> h;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    set<pair<int, int>> workingList, freeList;
    for (int i = 1; i <= m; i++) {
        freeList.insert({a[i], i});
    }
    for (int i = 1; i <= n; i++) {
        //pop old people
        while (!workingList.empty()) {
            auto u = *workingList.begin();
            if (u.first == i) {
                workingList.erase(u);
                if (a[u.second]) {
                    if (i + h > n) return (cout << -1 << endl, 0);
                    events[i + h].push_back(u.second);
                }
            } else break;
        }

        //add to free
        for (auto u : events[i]) {
            freeList.insert({a[u], u});
        }

        //add new people
        while (workingList.size() < d[i]) {
            if (freeList.empty()) return (cout << -1 << endl, 0);
            auto u = *freeList.rbegin();
            freeList.erase(u);
            a[u.second] -= w;
            res[u.second].push_back(i);
            workingList.insert({i + w, u.second});
        }

        if (workingList.size() != d[i]) return (cout << -1 << endl, 0);
    }
    while (!workingList.empty()) {
        auto u = *workingList.begin();
        if (u.first == n + 1) {
            workingList.erase(u);
            if (a[u.second]) {
                return (cout << -1 << endl, 0);
            }
        } else break;
    }
    if (!workingList.empty()) return (cout << -1 << endl, 0);
    for (int i = 1; i <= m; i++) if (a[i]) return (cout << -1 << endl, 0);

    cout << 1 << '\n';
    for (int i = 1; i <= m; i++) {
        for (int u : res[i]) cout << u << ' ';
        cout << '\n';
    }
    return 0;
}