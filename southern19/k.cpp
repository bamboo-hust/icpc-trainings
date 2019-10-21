#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 6;

int n;
int a[N];
int b[N];
int min_till[N];
int max_till[N];
vector<int> Q[N];
int64_t res;

void update(int i) {
    for (++i; i < N; i += i & -i) b[i]++;
}

int get(int i) {
    int res = 0;
    for (++i; i; i -= i & -i) res += b[i];
    return res;
}

void solve() {
    for (int i = n; i >= 1; --i) {
        min_till[i] = i + 1;
        while (min_till[i] <= n && a[i] < a[min_till[i]]) min_till[i] = min_till[min_till[i]];
    }

    for (int i = 1; i <= n; ++i) {
        max_till[i] = i - 1;
        while (max_till[i] >= 1 && a[i] > a[max_till[i]]) max_till[i] = max_till[max_till[i]];
    }

    for (int i = 1; i <= n; ++i) {
        Q[min_till[i] - 1].push_back(i - 1);
        res -= i;
    }

    memset(b, 0, sizeof b);

    for (int i = 1; i <= n; ++i) {
        update(max_till[i]);
        while (!Q[i].empty()) {
            res += get(Q[i].back());
            Q[i].pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i];
    //n = 1e6; for (int i = 1; i <= n; ++i) a[i] = i; random_shuffle(a + 1, a + 1 + n);

    solve();
    reverse(a + 1, a + 1 + n);
    solve();

    cout << res + n << endl;
}