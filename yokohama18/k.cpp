#include <bits/stdc++.h>

using namespace std;

const int N = 11111;

int orig[N];
int B[N];
multiset<int> remain;
int output[N];
int n;

struct BIT {
    int a[N];
    int n;

    BIT() {
        memset(a, 0, sizeof a);
        n = 0;
    }

    int size() {
        return n;
    }

    void inc(int i, int v) {
        for (; i < N; i += i & -i) a[i] += v;
    }

    int get(int i) {
        int res = 0;
        for (; i; i -= i & -i) res += a[i];
        return res;
    }

    void insert(int i) {
        inc(i, 1);
        ++n;
    }

    void erase(int i) {
        inc(i, -1);
        --n;
    }

    int find_by_order(int k) {
        int res = 0;
        int cur = 0;
        for (int i = 13; i >= 0; --i) {
            if (cur + (1 << i) < N && res + a[cur + (1 << i)] <= k) {
                cur += 1 << i;
                res += a[cur];
            }
        }
        return cur + 1;
        /*
        int l = 0, r = N - 1;
        int res = 0;
        while (l <= r) {
            int mid = l + r >> 1;
            if (get(mid) >= k + 1) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return res;
         */
    }

    int order_of_key(int k) {
        return get(k - 1);
    }
};

int solve(const multiset<int> &b) {
//    cerr << "begin solve " << played << ' ' << b.size() << ": ";
//    for (int v : b) cerr << v << ' '; cerr << endl;

    int res = 0;
    auto it = b.begin();
    for (int v : remain) {
        while (it != b.end() && *it <= v) ++it;
        if (it == b.end()) {
            return res;
        }
        res += (*it) > v;
        ++it;
    }
//    cerr << "result = " <<res << endl;
    return res;
}

void find_answer() {
    for (int i = 0; i < n; ++i) {
        remain.insert(orig[i]);
    }
    multiset<int> b;
    BIT S;
    for (int i = 0; i < n; ++i) {
        b.insert(B[i]);
        S.insert(B[i]);
    }

    int res = solve(b);
    for (int i = 0; i < n; ++i) {
        int pick = 0;
        auto min_to_win = b.upper_bound(orig[i]);
        remain.erase(remain.find(orig[i]));

        if (min_to_win != b.end()) {
//            cerr << "win case\n";
            int l = S.order_of_key(*min_to_win), r = (int)S.size() - 1;
            while (l <= r) {
                int mid = l + r >> 1;
                int x = S.find_by_order(mid);
                b.erase(b.find(x));
                int best = solve(b) + 1;
//                cerr << "mid=" << mid << " x=" << x << " best=" << best << endl;

                if (best >= res) {
                    pick = x;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
                b.insert(x);
            }
        }
        if (pick == 0) {
//            cerr << "lose case\n";
            int l = 0, r = min_to_win == b.end() ? (int(S.size()) - 1) : S.order_of_key(*min_to_win) - 1;
            while (l <= r) {
                int mid = l + r >> 1;
                auto x = S.find_by_order(mid);
                b.erase(b.find(x));
                int best = solve(b);
//                cerr << "mid=" << mid << " x=" << x << " best=" << best << endl;
                if (best >= res) {
                    pick = x;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
                b.insert(x);
            }
        }
        assert(pick > 0);
        b.erase(b.find(pick));
        S.erase(pick);
        output[i] = pick;
        res -= pick > orig[i];
    }
}

void read() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> orig[i];
    for (int i = 0; i < n; ++i) cin >> B[i];
}

void gen() {
    n = 5000;
    for (int i = 0; i < n; ++i) {
        orig[i] = rand() % 10000 + 1;
        B[i] = rand() % 10000 + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);

    read();
    //gen();
    find_answer();
//    for (int i = 0; i < 10000; ++i) {
//        cerr << "test #" << i << endl;
//        gen();
//    }

    for (int i = 0; i < n; ++i) cout << output[i] << ' ';
    cout << endl;

    return 0;
}