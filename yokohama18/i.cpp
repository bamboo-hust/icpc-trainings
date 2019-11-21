#include <bits/stdc++.h>

using namespace std;

const int N = 1028;

using Vec = bitset<N>;

vector< bitset<N> > a;

int n, m;

vector< Vec > get_canonical_basis(const vector< Vec > &a, vector< pair<int, int> > &ids) {
    vector< Vec > B(N);
    int row_id = 0;
    for (Vec v : a) {
        for (int i = 0; i < N; ++i) {
            if (v[i]) {
                if (B[i][i]) {
                    v ^= B[i];
                } else {
                    B[i] = v;
                    ids.push_back(make_pair(row_id, i));
                    break;
                }
            }
        }
        ++row_id;
    }

    for (int i = 1; i < B.size(); ++i) if (B[i][i]) {
        for (int j = 0; j < i; ++j) {
            if (B[j][i]) {
                B[j] ^= B[i];
            }
        }
    }

    return B;
}

vector< pair<int, Vec> > can_use[N];
vector<Vec> B[N];
vector<Vec> all;

int get_size(vector<Vec> &B) {
    int res = 0;
    for (int i = 0; i < B.size(); ++i) {
        res += B[i][i];
    }
    return res;
}

void solve(vector<Vec> &B, Vec v) {
    bool positive = false;
    if (get_size(all)== get_size(B)) {
        positive = true;
    }

    Vec x = 0;
    for (int i = 0; i < m; ++i) {
        if (v[i]) {
            x ^= B[i];
        }
    }

    for (int i = 0; i < m; ++i) {
        v.flip(i);
        x ^= B[i];

        if (x == v) {
            // dependent
            if (positive) {
                cout << "0";
            } else {
                cout << "-";
            }
        } else {
            // independent
            if (positive) {
                cout << "+";
            } else {
                cout << "0";
            }
        }

        v.flip(i);
        x ^= B[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char u; cin >> u;
            a[i][j] = u - '0';
        }
    }
    vector< pair<int, int> > ids;
    all = get_canonical_basis(a, ids);

    cout << "All" << endl;
    for (int bit = 0; bit < m; ++bit) if (all[bit][bit]) {
        for (int pos = 0; pos < m; ++pos) cout << all[bit][pos];
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < n; ++i)  {
        bool in_basis = false;
        for (int j = 0; j < ids.size(); ++j) {
            if (ids[j].first == i) {
                in_basis = true;
                break;
            }
        }
        if (in_basis) continue;
        Vec v = a[i];
        for (int j = 0; j < m; ++j) {
            if (v[j] == 1) {
                can_use[j].push_back(make_pair(i, v));
                //if (can_use[j].size() > 2) can_use[j].pop_back();
                v ^= all[j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cerr << "calc base " << i << endl;
        B[i] = all;
        int bit_pos = -1;
        for (int j = 0; j < ids.size(); ++j) {
            if (ids[j].first == i) {
                bit_pos = ids[j].second;
                break;
            }
        }
        if (bit_pos == -1) {
            // not in original basis
            // do nothing
        } else {
            // find something in can_use to replace
            bool found = false;
            for (int it = 0; it < can_use[i].size(); ++it) {
                if (can_use[i][it].first != i) {
                    B[i][bit_pos] = can_use[i][it].second;
                    found = true;
                }
            }
            cerr << "found=" << found << endl;
            if (found) {
                for (int k = bit_pos + 1; k < N; ++k) if (B[i][k][k]){
                    if (B[i][bit_pos][k]) {
                        B[i][bit_pos] ^= B[i][k];
                    }
                }
            } 
            /*
            else 
            {*/
                //B[i][bit_pos].reset();
                vector<Vec> aa;
                for (int j = 0; j < n; ++j) if (i != j) aa.push_back(a[j]);
                vector< pair<int, int> > foo;
                B[i] = get_canonical_basis(aa, foo);
            //}
        }
    }

    cerr << "here\n";

    for (int i = 0; i < n; ++i) {
        cout << "B " << i << endl;
        for (int bit = 0; bit < m; ++bit) if (B[i][bit][bit]) {
            for (int pos = 0; pos < m; ++pos) cout << B[i][bit][pos];
            cout << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < n; ++i) {
        solve(B[i], a[i]);
    }
}