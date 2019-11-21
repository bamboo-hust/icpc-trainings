#include <bits/stdc++.h>

using namespace std;

const int N = 510;

int n, m, p;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> p;
    vector<int> ls;
    for (int i = 1; i <= p; i++) {
        int u, v;
        cin >> u >> v;
        if (v > m) v++;
        ls.push_back(abs(v - (m + 1)) + n - u + 1);
    }
    sort(ls.begin(), ls.end());
    int cur = 0;
    for (int u : ls) {
        cur = max(u, cur + 1);
    }
    cout << cur << endl;
    return 0;
}