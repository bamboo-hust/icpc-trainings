#include <bits/stdc++.h>

using namespace std;

const int N = 300005;
const int MOD = 998244353;

int a[N];
int n;

int pre[N];
int dp[N];
int sum[N];
int mex;

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = 1LL * res * a % MOD;
        }
        a = 1LL * a * a % MOD;
        n >>= 1;
    }
    return res;
}

int calc_mex() {
    vector<bool> was(n + 1);
    for (int i = 1; i <= n; ++i) was[a[i]] = true;
    for (int i = 0; i <= n; ++i) if (!was[i]) return i;
    assert(false);
}

void calc_prev() {
    int j = -1;
    vector<int> cnt(n + 1);
    int num = 0;
    for (int i = 1; i <= n; ++i) {
        cnt[a[i]]++;
        if (a[i] < mex && cnt[a[i]] == 1) {
            num++;
        }
        if (num >= mex) {
            if (j == -1) j = 0;
            while (num >= mex && j < i && (a[j + 1] >= mex || cnt[a[j + 1]] > 1)) {
                ++j;
                cnt[a[j]]--;
                if (a[j] < mex && cnt[a[j]] == 0) {
                    --num;
                }
            }
        }
        pre[i] = j;
        //cerr << "pre " << i << ' ' << pre[i] << endl;
    }
}

void calc_dp() {
    dp[0] = 1;
    sum[0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i] = 0;
        if (pre[i] != -1) {
            dp[i] = sum[pre[i]];
        }
        sum[i] = sum[i - 1] + dp[i];
        if (sum[i] >= MOD) sum[i] -= MOD;
        //cerr << "dp " << i << ' ' << dp[i] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        mex = calc_mex();
        //cerr << "mex=" << mex << endl;
        if (mex == 0) {
            cout << pow(2, n - 1) << '\n';
            continue;
        }
        calc_prev();
        calc_dp();
        cout << dp[n] << '\n';
    }

    return 0;
}