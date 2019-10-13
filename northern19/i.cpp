#include <bits/stdc++.h>

using namespace std;

const int N = 19;

long long p[N];
long long w;

// o-->r remander <= d
long long get(long long r, long long d) {
    if (d < 0) return 0ll;
    long long rr = r / w;
    long long res = rr * (d + 1) + min(r - rr * w + 1, d + 1);
    return res;
}


// remainder <= d
long long getSum(long long d) {
    if (d < 0) return 0ll;
    long long res = 0;
    for (int len = 1; len <= 15; len++) {
        long long foo = 0;
        foo += get(p[len] - 1, d);
        foo -= get(p[len - 1] - 1, d);
        res += foo * len;
    }
    res += 16ll * ((p[15] % w) <= d);
    return res;
}

int getDigitWithNumber(long long u, long long k) {
    vector<int> digits;
    while (u) {
        digits.push_back(u % 10);
        u /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits[k - 1];
}

int getDigitWithLen(int l, long long k, long long d) {
    long long id = (k - 1) / l + 1;
    k -= (id - 1) * l;
    long long t = (p[l - 1] - d - 1) / w + 1;
    return getDigitWithNumber(w * (t + id - 1) + d, k);
}

int getDigitWithDK(long long d, long long k) {
    int l = -1;
    for (int len = 1; len <= 15; len++) {
        long long foo = 0;
        foo += get(p[len] - 1, d);
        foo -= get(p[len - 1] - 1, d);
        foo *= len;
        long long bar = 0;        
        bar += get(p[len] - 1, d - 1);
        bar -= get(p[len - 1] - 1, d - 1);
        bar *= len;
        foo -= bar;
        if (k > foo) k -= foo;
        else {
            l = len;
            break;
        }
    }
    if (l == -1) return getDigitWithLen(16, k, d);
    return getDigitWithLen(l, k, d);      
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    p[0] = 1;
    for (int i = 1; i < N; i++) p[i] = p[i - 1] * 10ll;
    int tc;
    cin >> tc;
    while (tc--) {
        long long k;
        cin >> w >> k;
        long long low = -1, high = w;
        while (high - low > 1) {
            long long mid = low + high >> 1ll;
            long long tot = getSum(mid);
            if (tot >= k) high = mid;
            else low = mid;
        }
        cout << getDigitWithDK(high, k - getSum(high - 1)) << '\n';
    }
    return 0;
}