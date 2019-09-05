#include <bits/stdc++.h>

using namespace std;

vector<int> solve(vector<int> p, int prefix) {
    //cerr << prefix << "| ";
    //for (int i = 1; i <= prefix; ++i) cerr << p[i] << ' '; cerr << endl;
    for (int i = 1; i <= prefix; ++i) if (p[i] != i) {
        if (p[p[i]] == 0) {
            p[p[i]] = i;
        } else if (p[p[i]] != i) {
            return vector<int>();
        }
    }
    for (int i = prefix + 1; i < p.size(); ++i) if (p[i] == 0) p[i] = i;
    return p;
}

const int N = 111;

int n, a[N];

bool check(vector<int> p) {
    for (int i = 1; i < p.size(); ++i) if (p[p[i]] != i) return false;
    return true;
}

vector<int> naive() {
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) p[i] = a[i];
    if (!next_permutation(p.begin() + 1, p.end())) return vector<int>();
    do {
        if (check(p)) return p;
    } while (next_permutation(p.begin() + 1, p.end()));
    return vector<int>();
}

int main() {
    //cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i];

    n = 8; for (int i = 1; i <= n; ++i) a[i] = i;
    do {    
        vector<int> ans;
        for (int prefix = n - 1; prefix >= 0; --prefix) {
            vector<int> p(n + 1);
            for (int i = 1; i <= prefix; ++i) p[i] = a[i];
            vector<bool> was(n + 1);
            for (int i = 1; i <= prefix; ++i) was[p[i]] = true;
            for (p[prefix + 1] = a[prefix + 1] + 1; p[prefix + 1] <= n; ++p[prefix + 1]) {
                if (!was[p[prefix + 1]]) {
                    was[p[prefix + 1]] = true;
                    vector<int> cur = solve(p, prefix + 1);
                    if (!cur.empty()) {
                        ans = cur;
                        break;
                    }
                }
            }
            if (!ans.empty()) break;
        }
        vector<int> ans_naive = naive();
        /*
        cerr << endl << "new test ";
        for (int i = 1; i <= n; ++i) cerr << a[i] << ' '; cerr << endl;
        cerr << "ans = ";
        for (int i = 1; i < ans.size(); ++i) cout << ans[i] << ' ';
        cout << endl;
        cerr << "god = ";
        
        for (int i = 1; i < ans_naive.size(); ++i) cerr << ans_naive[i] << ' ';
        cerr << endl;
        */
        assert(ans == ans_naive);
    } while (next_permutation(a + 1, a + 1 + n));
    return 0;
}