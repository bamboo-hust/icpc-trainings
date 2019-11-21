#include <bits/stdc++.h>

using namespace std;
#define f first
#define s second


int const N = 1e5 + 5;

pair < int, int > a[N];

struct BIT {
    int tree[N];
    void update(int x, int val) {
        while (x < N) {
            tree[x] += val;
            x += x & (-x);
        }
    }

    int get(int x) {
        int res = 0;
        while (x) {
            res += tree[x];
            x -= x & (-x);
        }
        return res;
    }
};

BIT tree1, tree2;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].f;
        a[i].s = i;
        tree1.update(i, 1);
        tree2.update(N - 1 - i, 1);
    }
    sort(a + 1, a + n + 1);
    long long ans = 0;
    for (int i = 1; i <= n;) {
        int pos = i;
        while (pos <= n && a[pos].f == a[i].f) {
            pos++;
        }
        int first_pos = i;
        int last_pos = pos - 1;
        while (first_pos <= last_pos) {
            int left_cost = tree1.get(a[first_pos].s - 1);
            int right_cost = tree2.get(N - 1 - (a[last_pos].s + 1));
            if (left_cost <= right_cost) {
                ans += left_cost;
                tree1.update(a[first_pos].s, -1);
                tree2.update(N - 1 - a[first_pos].s, -1);
                first_pos++;
            } else {
                ans += right_cost;
                tree1.update(a[last_pos].s, -1);
                tree2.update(N - 1 - a[last_pos].s, -1);
                last_pos--;
            }
        }
        i = pos;
    }

    cout << ans << endl;
}