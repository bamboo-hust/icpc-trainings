#include <bits/stdc++.h>

using namespace std;

int const N = 1e5 + 5;
int const MAX = 1e9 + 5;

int n, k, r;

struct BIT
{
    long long tree[N];
    void reset(int n) {
        for (int i = 0; i <= n; i++) {
            tree[i] = 0;
        }
    }   
    void update(int x, int val) {
        x++;
        while (x <= n) {
            tree[x] += val;
            x += x & (-x);
        }
    }

    long long get(int x) {
        x++;
        long long res = 0;
        while (x) {
            res += tree[x];
            x -= x & (-x);
        }
        return res;
    }
};

BIT t1, t2;
vector < int > s_val;

int a[N];

int get_pos(int x) {
    return upper_bound(s_val.begin(), s_val.end(), x) - s_val.begin() - 1;
}


long long calc(int id, int x) {
    int pos = get_pos(x);
    long long sum_small = t1.get(pos);
    long long sum_large = 1ll * (id - t2.get(pos)) * x;
    return sum_small + sum_large;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k >> r;
        s_val.clear();
        t1.reset(n);
        t2.reset(n);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            s_val.push_back(a[i]);
        }

        sort(s_val.begin(), s_val.end());
        s_val.resize(unique(s_val.begin(), s_val.end()) - s_val.begin());

        for (int i = 1; i <= r; i++) {
            int val = get_pos(a[i]);
            t1.update(val, a[i]);
            t2.update(val, 1);
        }


        for (int i = r + 1; i <= n; i++) {
            int val = get_pos(a[i]);
            t1.update(val, a[i]);
            t2.update(val, 1);
            if (k == 1) {
                cout << t1.get(n - 1) << " ";
            } else {
                int l = 0;
                int r = MAX;
                while (r - l > 1) {
                    int x = (l + r) >> 1;
                    if ((calc(i, x) - x) >= 1ll * (k - 1) * x) {
                        l = x;
                    } else {
                        r = x;
                    }
                }
                //cout << calc(i, l) - l << endl;
                cout << calc(i, l) / k << " ";   
            }
        }
        cout << endl;
    }
}