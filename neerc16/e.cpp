#include <bits/stdc++.h>

using namespace std;
#define f first
#define s second

int const N = 1e5 + 5;
long long const MAX = 2e9 + 1;

long long sum_all[N], sum_t[N];
pair < long long, long long > a[N];

int main() {
    ios_base::sync_with_stdio(0);
    freopen("expect.in", "r", stdin);
    freopen("expect.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        char type;
        cin >> type;
        cin >> a[i].f >> a[i].s;
        if (type == '-') {
            a[i].s *= -1;
        }
    }
    sort (a + 1, a + n + 1);
    int sum = 0;
    vector < pair < long long, long long > > segment;
    for (int i = 1; i <= n; i++) {
        sum += a[i].s;
        if (i < n && sum < 0) {
            //cout << "seg " << -sum << " " << a[i + 1].f - a[i].f << endl;
            segment.push_back(make_pair(-sum, a[i + 1].f - a[i].f));
        }
    }
    int size = segment.size();
    segment.push_back(make_pair(-1, 0));
    sort (segment.begin(), segment.end());
    for (int i = 1; i < segment.size(); i++) {
        sum_t[i] = sum_t[i - 1] + segment[i].s;
        sum_all[i] = sum_all[i - 1] + segment[i].f * segment[i].s;
    }
    for (int i = 1; i <= q; i++) {
        long long b;
        cin >> b;
        if (sum + b < 0) {
            cout << "INFINITY" << endl;
            continue;
        }
        int pos = lower_bound(segment.begin(), segment.end(), make_pair(b, 0ll)) - segment.begin(); 
        long long ans = sum_all[size] - sum_all[pos - 1] - (sum_t[size] - sum_t[pos - 1]) * b;
        cout << ans << endl;
    }

}