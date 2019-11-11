#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, k;
int a[N];
vector<pair<int, int>> events[N];
vector<pair<int, int>> queries[N];
long long res[N];

struct BIT {
    long long t[N];
    
    void init() {
        memset(t, 0, sizeof t);
    }

    void add(int x, int v) {
        while (x < N) {
            t[x] += v;
            x += x & -x;
        }
    }

    long long get(int x) {
        long long res = 0;
        while (x) {
            res += t[x];
            x -= x & -x;
        }
        return res;
    }
} t;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;

        //init
        t.init();
        for (int i = 0; i < N; i++) {
            events[i].clear();
            queries[i].clear();
        }

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        
        struct StackElement {
            int minVal, maxVal, num;
            bool operator == (const StackElement &u) const {
                return minVal == u.minVal && maxVal == u.maxVal;
            }
        };

        vector<StackElement> st;
        for (int i = 1; i <= n; i++) {
            st.push_back({a[i], a[i], 1});
            vector<StackElement> cur;
            for (auto val : st) {
                val.minVal = min(val.minVal, a[i]);
                val.maxVal = max(val.maxVal, a[i]);
                if (!cur.empty() && cur.back() == val) cur.back().num += val.num;
                else cur.push_back(val);
            }
            st.swap(cur);
            for (auto val : st) {
                events[val.minVal].push_back({val.maxVal, val.num});
                t.add(val.maxVal, val.num);
            }
        }
        for (int i = 1; i <= k; i++) {
            int l, r;
            cin >> l >> r;
            queries[l].push_back({r, i});
        }   
        for (int i = 1; i < N; i++) {
            for (auto query : queries[i]) {
                res[query.second] = t.get(query.first);
            }
            for (auto event : events[i]) {
                t.add(event.first, -event.second);
            }
        }
        for (int i = 1; i <= k; i++) {
            cout << res[i] << '\n';
        }
    }
    return 0;
}