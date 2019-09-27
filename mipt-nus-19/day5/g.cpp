//
// Created by quanglm1998 on 26/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

int n;
string s[2];
vector<int> res[2];

void moveLeft(int id, int u) {
    res[u].push_back((id - 2 + n) % n);
    s[u][(id - 2 + n) % n] = s[u][(id - 1 + n) % n] = '1';
    res[u].push_back((id - 1 + n) % n);
    s[u][id] = s[u][(id - 1 + n) % n] = '0';
}

void goLeft(int id, int u) {
    while (id >= 1) {
        if (s[u][id - 1] == '1') {
            res[u].push_back(id - 1);
            s[u][id - 1] = s[u][id] = '0';
            return;
        }
        if (id == 1) return;
        if (s[u][id - 2] == '1') return;
        moveLeft(id, u);
        id -= 2;
    }
}

void solve(int u) {
    for (int i = 0; i < n; i++) {
        if (s[u][i] == '0') continue;
        goLeft(i, u);
    }
    if (n % 2 == 0) return;
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (s[u][i] == '1') found++;
    }
    while (found >= 2) {
        if (s[u][0] == '1') {
            moveLeft(0, u);
            goLeft(n - 2, u);
        } else {
            moveLeft(1, u);
            goLeft(n - 1, u);
        }
        found -= 2;
        for (int i = 0; i < n; i++) {
            if (s[u][i] == '1') goLeft(i, u);
        }
    }
    if (found == 1 && s[u][0] == '0') {
        moveLeft(1, u);
        goLeft(n - 1, u);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    cin >> s[0] >> s[1];
    n = s[0].size();
    for (int i = 0; i <= 1; i++) solve(i);
    cout << res[0].size() + res[1].size() << '\n';
    for (int u : res[0]) cout << u << '\n';
    for (int i = (int)res[1].size() - 1; i >= 0; i--) cout << res[1][i] << '\n';
    return 0;
}