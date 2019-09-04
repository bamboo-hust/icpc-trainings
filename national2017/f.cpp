#include <bits/stdc++.h>

using namespace std;

const int NDIGIT = 20;
const int D = 10;
const int N = 1111;
const int MOD = 1e9 + 7;

int C[N][N];
vector<int> digit;

long long memo[NDIGIT][2][2][1 << D];

long long inverse(int x) {
    long long res = 1;
    long long power = x;
    int p = MOD - 2;
    while (p > 0) {
        if (p & 1) {
            res = res * power % MOD;
        }
        power = power * power % MOD;
        p >>= 1;
    }
    return res;
}

long long dp(int i, bool smaller, bool nonzero, int mask) {
    long long &ans = memo[i][smaller][nonzero][mask];
    if (ans != -1) return ans;
    if (i == digit.size()) {
        return ans = nonzero && mask == 0;
    }
    ans = 0;
    for (int x = 0; x <= (smaller ? 9 : digit[i]); ++x) {
        int newmask = mask;
        if (nonzero || (x != 0)) {
            if (newmask >> x & 1) {
                newmask ^= 1 << x;
            }
        }
        ans += dp(i + 1, smaller || (x < digit[i]), nonzero || (x != 0), newmask);
    }
    return ans;
}

void prepare(long long limit) {
    long long x = limit;
    digit.clear();
    while (x > 0) {
        digit.push_back(x % 10);
        x /= 10;
    }
    reverse(digit.begin(), digit.end());
    memset(memo, -1, sizeof memo);
}

int comb(long long n, long long k) {
    long long ans = 1;
    for (long long i = n; i > n - k; --i) {
        ans = (ans * i) % MOD;
    }
    long long fact = 1;
    for (int i = 1; i <= k; ++i) {
        fact = fact * i;
        fact %= MOD;
    }
    return ans * inverse(fact) % MOD;
}

bool has(long long x, int mask) {
    while (x > 0) {
        int cur = x % 10;
        if (mask >> cur & 1) mask ^= 1 << cur;
        x /= 10;
    }
    return mask == 0;
}

long long calc(long long A, long long B, int mask) {
    long long ans = 0;
    for (long long i = A; i <= B; ++i) if (has(i, mask)) {
        ans += 1;
    }
    //if (ans != 0) cerr << "calc " << A << ' ' << B << ' ' << mask << ' ' << ans << endl;
    return ans;
}

long long full(long long A, long long B, int k, int d) {
    long long ans = 0;

    map<int, long long> cnt;
    prepare(B);
    for (int mask = 0; mask < (1 << D); ++mask) {
        cnt[mask] += dp(0, 0, 0, mask);
    }
    if (A > 0) {
        prepare(A - 1);
        for (int mask = 0; mask < (1 << D); ++mask) {
            cnt[mask] -= dp(0, 0, 0, mask);
        }
    }
/*
    for (int mask = 0; mask < (1 << D); ++mask) {
        assert(cnt[mask] == calc(A, B, mask));
    }
*/
    for (int mask = 0; mask < (1 << D); ++mask) if (__builtin_popcount(mask) == d) {
        for (int super = mask; super < (1 << D); ++super) if ((mask & super) == mask) {
            if ((__builtin_popcount(super) - d) & 1) {
                ans -= comb(cnt[super], k);
                ans %= MOD;
                ans += MOD;
                ans %= MOD;
            } else {
                ans += comb(cnt[super], k);
                ans %= MOD;
            }
        }
    }
    return ans;
}

long long naive(long long A, long long B, int k, int d) {
    long long ans = 0;
    for (int mask = 0; mask < (1 << D); ++mask) if (__builtin_popcount(mask) == d) {
        for (int super = mask; super < (1 << D); ++super) if ((mask & super) == mask) {
            if ((__builtin_popcount(super) - d) & 1) {
                ans -= comb(calc(A, B, super), k);
                ans %= MOD;
                ans += MOD;
                ans %= MOD;
            } else {
                ans += comb(calc(A, B, super), k);
                ans %= MOD;
            }
        }
    }
    return ans;
}

int main() {
    for (int i = 0; i < N; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            C[i][j] %= MOD;
        }
    }

    int T; cin >> T;
    while (T--) {
        long long A, B, k, d;
        cin >> A >> B >> k >> d;
        cout << full(A, B, k, d) << endl;
    }
    return 0;
}