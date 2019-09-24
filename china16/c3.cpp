#include <bits/stdc++.h>

using namespace std;

const int N = 1024;
const int LOG = 10;
const int V = 1e5 + 5;

int a[N];
int n;
int cnt[V];
int L[N], R[N];
int to[N];
vector<int> pos[V];

int pre[N];
int nxt[N];

struct RMQMin {
    int rmq[LOG][N];

    RMQMin(int a[N], int n) {
        for (int i = 1; i <= n; ++i) {
            rmq[0][i] = a[i];
        }
        for (int j = 1; j < LOG; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + (1 << j - 1)]);
            }
        }
    }

    int get(int l, int r) {
        int k = log2(r - l + 1);
        return min(rmq[k][l], rmq[k][r - (1 << k) + 1]);
    }
};

struct RMQMax {
    int rmq[LOG][N];

    RMQMax(int a[], int n) {
        for (int i = 1; i <= n; ++i) {
            rmq[0][i] = a[i];
        }
        for (int j = 1; j < LOG; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                rmq[j][i] = max(rmq[j - 1][i], rmq[j - 1][i + (1 << j - 1)]);
            }
        }
    }

    int get(int l, int r) {
        int k = log2(r - l + 1);
        return max(rmq[k][l], rmq[k][r - (1 << k) + 1]);
    }
};

int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) {
            pos[a[i]].push_back(i);
        }
        int res = 0;
        for (int r = n; r >= 1; --r) {
            int limit = n + 1;
            for (int i = r; i <= n; ++i) {
                if (cnt[a[i]]) {
                    limit = i;
                    break;
                }
                cnt[a[i]]++;
            }
            cerr << "limit " << r << ' ' << limit << endl;
            res = max(res, limit - r);
            for (int i = 1; i < r; ++i) {
                to[i] = lower_bound(begin(pos[a[i]]), end(pos[a[i]]), r) - begin(pos[a[i]]);
                if (to[i] == pos[a[i]].size()) {
                    to[i] = n + 1;
                } else {
                    to[i] = pos[a[i]][to[i]];
                }
            }
            for (int i = 1; i < r; ++i) {
                cerr << "to " << i << ' ' << to[i] << endl;
            }
            for (int i = 1; i < r; ++i) {
                L[i] = i - 1;
                while (L[i] > 0 && to[L[i]] >= to[i]) L[i] = L[L[i]];
            }
            for (int i = r - 1; i >= 1; --i) {
                R[i] = i + 1;
                while (R[i] < r && to[R[i]] >= to[i]) R[i] = R[R[i]];
            }

            for (int i = 1; i < r; ++i) {
                int it = lower_bound(begin(pos[a[i]]), end(pos[a[i]]), i) - begin(pos[a[i]]);
                pre[i] = it > 0 ? pos[a[i]][it - 1] : 0;
                nxt[i] = it + 1 < pos[a[i]].size() ? pos[a[i]][it + 1] : r;
            }

            RMQMin rmq_nxt(nxt, r - 1);
            RMQMax rmq_pre(pre, r - 1);

            for (int i = 1; i < r; ++i) {
                int left = i + 1, right = R[i];
                while (left <= right) {
                    int mid = left + right >> 1;
                    if (rmq_nxt.get(i, mid - 1) >= mid) {
                        R[i] = mid;
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }

            for (int i = 1; i < r; ++i) {
                int left = L[i], right = i - 1;
                while (left <= right) {
                    int mid = left + right >> 1;
                    if (rmq_pre.get(mid + 1, i) <= mid) {
                        L[i] = mid;
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
            }


            for (int i = 1; i < r; ++i) if (to[i] > r) {
                res = max(res, (R[i] - L[i] - 1) + (to[i] - r));
                if (res == 8) {
                    cerr << "wrong " << i << ' ' << L[i] << ' ' << R[i] << ' ' << to[i] << ' ' << r << endl;
                }
            }
            for (int i = r; i <= n; ++i) {
                cnt[a[i]] = 0;
            }
        }
        for (int i = 1; i <= n; ++i) {
            pos[a[i]].clear();
        }
        cout << "Case #" << tc << ": " << res << '\n';
    }
    return 0;
}