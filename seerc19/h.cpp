#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N];
vector<int> vals;
int used[N];
int par[N];
long long res[N];

bool check(int cnt) {
    memset(used, 0, sizeof used);
    memset(par, 0, sizeof par);
    for (int i = 0; i < cnt; i++) {
        int u = vals[i];
        int v = i + 1 < cnt ? vals[i + 1] : -1;
        par[v == -1 ? n : a[v]] = a[u];
        used[u] = 1;
    }
    int cur = 1;
    for (int i = 2; i <= n; i++) {
        if (par[i]) continue;
        while (used[cur]) cur++;
        used[cur] = 1;
        par[i] = a[cur];
    }
    for (int i = 2; i <= n; i++) if (par[i] >= i) return 0;
        return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n * 2 - 2; i++) cin >> a[i];
    sort(a + 1, a + n * 2 - 1);

    if (a[1] > 1) {
        for (int i = 1; i < n; i++) cout << -1 << ' ';
            cout << endl;
        return 0;
    }

    for (int i = 1; i <= n * 2 - 2; i++) {
        if (a[i] > a[i - 1]) vals.push_back(i);
    }

    int low = 0, high = vals.size() + 1;
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid)) high = mid;
        else low = mid;
    }
    
    multiset<int> small, big;
    long long sumSmall = 0, sumBig = 0;
   
    auto add = [&](multiset<int> &s, long long &sum, int u) {
        s.insert(u);
        sum += u;
    };

    auto remove = [&](int u) {
        if (small.count(u)) {
            sumSmall -= u;
            small.erase(small.find(u));
            return;
        }
        if (big.count(u)) {
            sumBig -= u;
            big.erase(big.find(u));
            return;
        }
        assert(0);
    };

    auto normalize = [&](int sum) {
        while (big.size() < sum) {
            int u = *small.rbegin();
            sumSmall -= u;
            small.erase(small.find(u));
            sumBig += u;
            big.insert(u);
        }
    };

    for (int i = 1; i <= n * 2 - 2; i++) {
        add(small, sumSmall, a[i]);
    }

    memset(res, -1, sizeof res);
    for (int i = 0; i < vals.size(); i++) {
        // cout << "in " << i << endl;
        remove(a[vals[i]]);    
        normalize(i + 1);
        // cout << small.size() << ' ' << big.size() << endl;
        // cout << sumSmall << ' ' << sumBig << endl;
        if (i + 1 >= high) res[i + 1] = sumBig; 
    }   
    for (int i = 1; i < n; i++) cout << res[i] << ' ';
        cout << endl;
    return 0;
}