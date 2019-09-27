//
// Created by quanglm1998 on 24/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n;
int a[N];
vector<int> pos[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    int q;
    cin >> q;
    while (q--) {
        int len;
        cin >> len;
        vector<int> ls(len);
        for (int &u : ls) cin >> u;
        int last = 0;
        for (int u : ls) {
            int id = upper_bound(pos[u].begin(), pos[u].end(), last) - pos[u].begin();
            if (id == pos[u].size()) last = n + 1;
            else last = pos[u][id];
        }
        cout << (last <= n ? "TAK" : "NIE") << '\n';
    }
    return 0;
}