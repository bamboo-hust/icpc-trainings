#include <bits/stdc++.h>

#define REP(i, N) for (int i = 0; i < (N); ++i)
#define llint long long
#define MOD 786433

using namespace std;

namespace FFT {
    const int MAX = 1 << 17;
    typedef llint value;
    typedef complex<double> comp;
    int N;
    comp omega[MAX];
    comp a1[MAX], a2[MAX];
    comp z1[MAX], z2[MAX];
    void fft(comp *a, comp *z, int m = N) {
        if (m == 1) {
            z[0] = a[0];
        } else {
            int s = N/m;
            m /= 2;
            fft(a, z, m);
            fft(a+s, z+m, m);
            REP(i, m) {
                comp c = omega[s*i] * z[m+i];
                z[m+i] = z[i] - c;
                z[i] += c;
            }
        }
    }
    void mult(value *a, value *b, value *c, int len) {
        N = 2*len;
        while (N & (N-1)) ++N;
        assert(N <= MAX);
        REP(i, N) a1[i] = 0;
        REP(i, N) a2[i] = 0;
        REP(i, len) a1[i] = a[i];
        REP(i, len) a2[i] = b[i];
        REP(i, N) omega[i] = polar(1.0, 2*M_PI/N*i);
        fft(a1, z1, N);
        fft(a2, z2, N);
        REP(i, N) omega[i] = comp(1, 0) / omega[i];
        REP(i, N) a1[i] = z1[i] * z2[i] / comp(N, 0);
        fft(a1, z1, N);
        REP(i, len) c[i] = round(z1[i].real());
    }
    void mult_mod(llint *a, llint *b, llint *c, int len, int mod) {
        static llint a0[MAX], a1[MAX];
        static llint b0[MAX], b1[MAX];
        static llint c0[MAX], c1[MAX], c2[MAX];
        REP(i, len) a0[i] = a[i] & 0xFFFF;
        REP(i, len) a1[i] = a[i] >> 16;
        REP(i, len) b0[i] = b[i] & 0xFFFF;
        REP(i, len) b1[i] = b[i] >> 16;
        FFT::mult(a0, b0, c0, len);
        FFT::mult(a1, b1, c2, len);
        REP(i, len) a0[i] += a1[i];
        REP(i, len) b0[i] += b1[i];
        FFT::mult(a0, b0, c1, len);
        REP(i, len) c1[i] -= c0[i] + c2[i];
        REP(i, len) c1[i] %= mod;
        REP(i, len) c2[i] %= mod;
        REP(i, len) c[i] = (c0[i] + (c1[i] << 16) + (c2[i] << 32)) % mod;
    }
}

const int N = 5e4 + 5;
llint ans[N], sum[N], a[N], p[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, k, q;
    cin >> n >> k >> q;
   
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        a[x] += 1;
    }

    for (int i = 0; i < N; ++i) p[i] = a[i];
    if (k > 1) {
	    ans[0] = 1;
	    while (k > 0) {
		if (k & 1) {
		    FFT::mult_mod(ans, p, ans, N, MOD);
		}
            k >>= 1;
            FFT::mult_mod(p, p, p, N, MOD);
	    }
	    //for (int i = 0; i < N; ++i) if (ans[i]) cout << i << ' ' << ans[i] << endl;
    } else {
	    for (int i = 0; i < N; ++i) ans[i] = a[i];		
    }
    sum[0] = ans[0];
    for (int i = 1; i < N; ++i) {
        sum[i] = sum[i - 1] + ans[i];
        sum[i] %= MOD;
    }
    while (q--) {
        int L, R; cin >> L >> R;
        cout << sum[R] - sum[L - 1] << '\n';
    }
    cerr << (double)clock() / CLOCKS_PER_SEC << endl;
}
