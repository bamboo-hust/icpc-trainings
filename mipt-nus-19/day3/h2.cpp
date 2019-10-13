#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int M = 72;
const int P = 36;

bitset<M> a[N];
int sign[M];
int power[M];

vector< pair<int, int> > cols[P];

int n, m;

bitset<M> basis[M];
bitset<M> basis2[M];
bitset<M> important;

void add_vector(bitset<M> basis[], bitset<M> v) {
    for (int i = 0; i < M; ++i) {
        if (v[i]) {
            if (!basis[i][i]) {
                basis[i] = v;
                break;
            }
            v ^= basis[i];
        }
    }
}

void prepare_basis() {
    for (int i = 0; i < M; ++i) basis2[i].reset();
    for (int i = 0; i < M; ++i) {
        bitset<M> v = basis[i];
        for (int j = 0; j < M; ++j) {
            if (!important[j]) {
                v[j] = 0;
            }
        }
        add_vector(basis2, v);
    }
}

bool contains(bitset<M> v) {
    prepare_basis();
    for (int j = 0; j < M; ++j) {
        if (!important[j]) v[j] = 0;
    }
    for (int i = 0; i < M; ++i) {
        if (v[i]) {
            if (!basis2[i][i]) {
                return false;
            }
            v ^= basis2[i];
        }
    }
    return true;
}

long long pow3(long long n) {
    long long res = 1;
    while (n > 0) {
        res *= 3;
        n--;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            a[i][j] = (s[j] == '1');
        }
    }
    for (int i = 0; i < m; ++i) cin >> sign[i] >> power[i];

    for (int i = 0; i < m; ++i) {
        cols[power[i]].push_back({sign[i], i});
    }

    for (int i = 0; i < P; ++i) {
        sort(rbegin(cols[i]), rend(cols[i]));
        if (cols[i].size() == 2) {
            for (int row = 0; row < n; ++row) {
                if (a[row][cols[i][0].second]) {
                    a[row].flip(cols[i][1].second);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        add_vector(basis, a[i]);
    }

    bitset<M> v;
    long long res = 0;
    for (int i = P - 1; i >= 0; --i) if (cols[i].size()) {
        if (cols[i].size() == 1) {
            int c = cols[i][0].second;
            if (cols[i][0].first == +1) {
                important[c] = 1;
                v[c] = 1;
                if (contains(v)) {                    
                    res += pow3(i);
                } else {
                    important[c] = 0;
                    v[c] = 0;
                }
            } else {
                important[c] = 1;
                v[c] = 0;
                if (contains(v)) {
                    // good!
                } else {
                    important[c] = 0;
                    v[c] = 1;
                    res -= pow3(i);
                }
            }
        } else {
            int plus = cols[i][0].second;
            int diff = cols[i][1].second;

            important[plus] = important[diff] = 1;
            v[plus] = v[diff] = 1;
            if (contains(v)) {
                res += pow3(i);
            } else {
                v[plus] = 1; v[diff] = 0;
                important[plus] = 0;
                if (contains(v)) {
                    // good!
                } else {
                    important[plus] = important[diff] = 0;
                    v[plus] = v[diff] = 0;
                    res -= pow3(i);
                }
            }
        }
    }

    cout << res << endl;
}