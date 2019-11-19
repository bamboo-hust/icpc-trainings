#include <bits/stdc++.h>

using namespace std;

const int N = 128;

vector<int> a[N], b[N];
int n, m, h;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> h;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            if (s[j] == '1') {
                a[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < h; ++j) {
            if (s[j] == '1') {
                b[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (a[i].empty() != b[i].empty()) {
            cout << "-1" << endl;
            return 0;
        }
    }

    int kmax = 0;
    int kmin = 0;
    for (int i = 0; i < n; ++i) {
        kmax += a[i].size() * b[i].size();
        kmin += max(a[i].size(), b[i].size());
    }

    cout << kmax << endl;
    for (int x = 0; x < n; ++x) {
        for (int y : a[x]) for (int z : b[x]) {
            cout << x << ' ' << y << ' ' << z << '\n';
        }
    }

    cout << kmin << endl;
    for (int x = 0; x < n; ++x) {
        int diff = abs((int)a[x].size() - (int)b[x].size());
        if (a[x].size() < b[x].size()) {
            for (int i = 0; i < b[x].size(); ++i) {
                cout << x << ' ' << a[x][max(i - diff, 0)] << ' ' << b[x][i] << '\n';
            }
        } else {
            for (int i = 0; i < a[x].size(); ++i) {
                cout << x << ' ' << a[x][i] << ' ' << b[x][max(i - diff, 0)] << '\n';
            }
        }
    }

    return 0;
}