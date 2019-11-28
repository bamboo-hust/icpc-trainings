#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 1e8;

int a[N];
int b[N];
int trace[N];

void update(int i, int v, int last) {
    for (; i < N; i += i & -i) {
        if (a[i] < v) {
            a[i] = v;
            b[i] = last;
        }
    }
}

int get(int i, int &pre) {
    int res = 0;
    for (; i; i -= i & -i) if (res < a[i]) {
        res = a[i];
        pre = b[i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cerr << setprecision(12) << fixed;
    vector< pair<double, int> > a;
    for (int i = 1; i < N; ++i) {
        a.push_back({sin(i), i});
    }
    sort(rbegin(a), rend(a));

    int res = 0;
    int finish = 0;
    for (auto it : a) {
        int pre = 0;
        int cur = get(it.second, pre) + 1;
        update(it.second, cur, it.second);
        trace[it.second] = pre;
        if (res < cur) {
            res = cur;
            finish = it.second;
        }
    }

    cout << res << endl;
    cout << "{";
    for (int i = finish; i > 0; i = trace[i]) {
        cout << i << ",}"[trace[i] == 0];
    }

    return 0;
}