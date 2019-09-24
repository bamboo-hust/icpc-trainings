#include <bits/stdc++.h>

using namespace std;
static struct IO {
    char tmp[1 << 10];

    // fast input routines
    char cur;

//#define nextChar() (cur = getc_unlocked(stdin))
//#define peekChar() (cur)
    inline char nextChar() { return cur = getc_unlocked(stdin); }
    inline char peekChar() { return cur; }

    inline operator bool() { return peekChar(); }
    inline static bool isBlank(char c) { return (c < '-' && c); }
    inline bool skipBlanks() { while (isBlank(nextChar())); return peekChar() != 0; }

    inline IO& operator >> (char & c) { c = nextChar(); return *this; }

    inline IO& operator >> (char * buf) {
        if (skipBlanks()) {
            if (peekChar()) {
                *(buf++) = peekChar();
                while (!isBlank(nextChar())) *(buf++) = peekChar();
            } *(buf++) = 0; } return *this; }

    inline IO& operator >> (string & s) {
        if (skipBlanks()) { s.clear(); s += peekChar();
            while (!isBlank(nextChar())) s += peekChar(); }
        return *this; }

    inline IO& operator >> (double & d) { if ((*this) >> tmp) sscanf(tmp, "%lf", &d); return *this; }

#define defineInFor(intType) \
    inline IO& operator >>(intType & n) { \
        if (skipBlanks()) { \
            int sign = +1; \
            if (peekChar() == '-') { \
                sign = -1; \
                n = nextChar() - '0'; \
            } else \
                n = peekChar() - '0'; \
            while (!isBlank(nextChar())) { \
                n += n + (n << 3) + peekChar() - 48; \
            } \
            n *= sign; \
        } \
        return *this; \
    }

defineInFor(int)
defineInFor(unsigned int)
defineInFor(long long)

    // fast output routines

//#define putChar(c) putc_unlocked((c), stdout)
    inline void putChar(char c) { putc_unlocked(c, stdout); }
    inline IO& operator << (char c) { putChar(c); return *this; }
    inline IO& operator << (const char * s) { while (*s) putChar(*s++); return *this; }

    inline IO& operator << (const string & s) { for (int i = 0; i < (int)s.size(); ++i) putChar(s[i]); return *this; }

    char * toString(double d) { sprintf(tmp, "%lf%c", d, '\0'); return tmp; }
    inline IO& operator << (double d) { return (*this) << toString(d); }


#define defineOutFor(intType) \
    inline char * toString(intType n) { \
        char * p = (tmp + 30); \
        if (n) { \
            bool isNeg = 0; \
            if (n < 0) isNeg = 1, n = -n; \
            while (n) \
                *--p = (n % 10) + '0', n /= 10; \
            if (isNeg) *--p = '-'; \
        } else *--p = '0'; \
        return p; \
    } \
    inline IO& operator << (intType n) { return (*this) << toString(n); }

defineOutFor(int)
defineOutFor(long long)

#define endl ('\n')
#define cout __io__
#define cin __io__
} __io__;

const int N = 100010;
const int B_SIZE = 35 * sqrt(N) / 40;
const int N_BLOCK = N / B_SIZE + 10;

vector<int> vals;


struct Block {
    vector<pair<int, int>> ls;
    long long sum;
    int cnt;
    int l, r;
    Block() {
        cnt = sum = 0;
        l = N, r = 0;
    }
    void add(int id, int v) {
        ls.push_back({v, id});
        sum += vals[v];
        cnt++;
        l = min(l, id);
        r = max(r, id);
    }
    void build() {
        sort(ls.begin(), ls.end());
    }
} b[N_BLOCK];

int n, q;
int a[N];
int numBlock = 0;
long long dp[N_BLOCK][N_BLOCK];

long long prefSum[N_BLOCK][N];
int prefNum[N_BLOCK][N];

int curNum[N];
long long curSum[N];

long long getVal(int u, int lu, int ru, int v, int lv, int rv, int f = 0, int debug = 0) {
    long long sum = 0;
    int cnt = 0;
    int cur = 0;
    long long totSum = 0;
    int totCnt = 0;
    for (auto val : b[v].ls) {
        if (val.second < lv || val.second > rv) continue;
        totSum += vals[val.first];
        totCnt++;
    }
    long long res = 0;
    for (auto valU : b[u].ls) {
        if (valU.second < lu || valU.second > ru) continue;
        while (cur < b[v].ls.size() && b[v].ls[cur].first <= valU.first) {
            int now = b[v].ls[cur].first;
            int idNow = b[v].ls[cur].second;
            cur++;
            if (idNow < lv || idNow > rv) continue;
            sum += vals[now];
            cnt++;
        }
        res += 1ll * vals[valU.first] * cnt - sum;
        res += (totSum - sum) - 1ll * vals[valU.first] * (totCnt - cnt);
    }  
    return res;
}

long long getBlockBlock(int l, int r, int ll, int rr) {
    if (ll > rr) return 0ll;
    if (l > r) return 0ll;
    long long res = dp[r][rr];
    res -= (l > 0 ? dp[l - 1][rr] : 0);
    res -= (ll > 0 ? dp[r][ll - 1] : 0);
    res += (l > 0 && ll > 0) ? dp[l - 1][ll - 1] : 0;
    return res;
}

long long getTailBlock(int l, int r, int ll, int rr) {
    if (ll > rr) return 0ll;
    long long res = 0;
    for (int i = l; i <= r; i++) {
        long long sumSmaller = prefSum[rr][a[i]] - (ll > 0 ? prefSum[ll - 1][a[i]] : 0);
        long long sumBigger = prefSum[rr][vals.size() - 1] - (ll > 0 ? prefSum[ll - 1][vals.size() - 1] : 0) - sumSmaller;

        int cntSmaller = prefNum[rr][a[i]] - (ll > 0 ? prefNum[ll - 1][a[i]] : 0);
        int cntBigger = prefNum[rr][vals.size() - 1] - (ll > 0 ? prefNum[ll - 1][vals.size() - 1] : 0) - cntSmaller;
        res += 1ll * cntSmaller * vals[a[i]] - sumSmaller;
        res += sumBigger - 1ll * cntBigger * vals[a[i]];
    }
    return res;
}

void addTailBlockEvent(int l, int r, int ll, int rr) {
    if (ll > rr) return;
    if (l > r) return;

    long long res = 0;
    for (int i = l; i <= r; i++) {
        long long sumSmaller = prefSum[rr][a[i]] - (ll > 0 ? prefSum[ll - 1][a[i]] : 0);
        long long sumBigger = prefSum[rr][vals.size() - 1] - (ll > 0 ? prefSum[ll - 1][vals.size() - 1] : 0) - sumSmaller;

        int cntSmaller = prefNum[rr][a[i]] - (ll > 0 ? prefNum[ll - 1][a[i]] : 0);
        int cntBigger = prefNum[rr][vals.size() - 1] - (ll > 0 ? prefNum[ll - 1][vals.size() - 1] : 0) - cntSmaller;
        res += 1ll * cntSmaller * vals[a[i]] - sumSmaller;
        res += sumBigger - 1ll * cntBigger * vals[a[i]];
    }
    return res;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    cin >> n >> q;  
    // n = q = 100000;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        // a[i] = rand() % (int)1e8;
        vals.push_back(a[i]);
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    }

    numBlock = (n - 1) / B_SIZE + 1;
    for (int i = 0; i < n; i++) {
        b[i / B_SIZE].add(i, a[i]);
    }
    for (int i = 0; i < numBlock; i++) b[i].build();

    for (int i = 0; i < numBlock; i++) {
        for (int j = 0; j < numBlock; j++) {
            dp[i][j] = getVal(i, b[i].l, b[i].r, j, b[j].l, b[j].r);
            if (j > 0) dp[i][j] += dp[i][j - 1];
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (i > 0 && j > 0) dp[i][j] -= dp[i - 1][j - 1];
        }
    }

    for (int i = 0; i < numBlock; i++) {
        for (int j = b[i].l; j <= b[i].r; j++) {
            curNum[a[j]]++;
            curSum[a[j]] += vals[a[j]];
        }
        for (int j = 0; j < vals.size(); j++) {
            prefSum[i][j] = curSum[j];
            if (j > 0) prefSum[i][j] += prefSum[i][j - 1];

            prefNum[i][j] = curNum[j];
            if (j > 0) prefNum[i][j] += prefNum[i][j - 1];
        }
    }

	vector<int> ql(q), qr(q), qll(q), qrr(q);
    for (int i = 0; i < q; ++i) {
        cin >> ql[i] >> qr[i] >> qll[i] >> qrr[i];
	}

	for (int i = 0; i < q; ++i) {
		int l = ql[i];
		int r = qr[i];
		int ll = qll[i];
		int rr = qrr[i];
		l--, r--, ll--, rr--;
        int lBlock = l / B_SIZE;
        int rBlock = r / B_SIZE;
        int llBlock = ll / B_SIZE;
        int rrBlock = rr / B_SIZE;

	}

	for (int i = 1; i <= q; i++) {
        int l = ql[i];
        int r = qr[i];
        int ll = qll[i];
        int rr = qrr[i];
        l--, r--, ll--, rr--;
        int lBlock = l / B_SIZE;
        int rBlock = r / B_SIZE;
        int llBlock = ll / B_SIZE;
        int rrBlock = rr / B_SIZE;
        // l = rand() % n + 1;
        // r = rand() % n + 1;
        // ll = rand() % n + 1;
        // rr = rand() % n + 1;
        if (l > r) swap(l, r);
        if (ll > rr) swap(ll, rr);
        long long &res = ans[i];
        res += getBlockBlock(lBlock + 1, rBlock - 1, llBlock + 1, rrBlock - 1);

        if (lBlock != rBlock) {
            res += getTailBlock(l, b[lBlock].r, llBlock + 1, rrBlock - 1);
            res += getTailBlock(b[rBlock].l, r, llBlock + 1, rrBlock - 1);
        } else res += getTailBlock(l, r, llBlock + 1, rrBlock - 1);
        if (llBlock != rrBlock) {
            res += getTailBlock(ll, b[llBlock].r, lBlock + 1, rBlock - 1);
            res += getTailBlock(b[rrBlock].l, rr, lBlock + 1, rBlock - 1);
        } else res += getTailBlock(ll, rr, lBlock + 1, rBlock - 1);

        if (lBlock != rBlock && llBlock != rrBlock) {
            res += getVal(lBlock, l, b[lBlock].r, llBlock, ll, b[llBlock].r);
            res += getVal(lBlock, l, b[lBlock].r, rrBlock, b[rrBlock].l, rr);
            res += getVal(rBlock, b[rBlock].l, r, llBlock, ll, b[llBlock].r);
            res += getVal(rBlock, b[rBlock].l, r, rrBlock, b[rrBlock].l, rr);
        } else if (lBlock == rBlock && llBlock != rrBlock) {
            res += getVal(lBlock, l, r, llBlock, ll, b[llBlock].r);
            res += getVal(lBlock, l, r, rrBlock, b[rrBlock].l, rr);
        } else if (lBlock != rBlock && llBlock == rrBlock) {
            res += getVal(lBlock, l, b[lBlock].r, llBlock, ll, rr);
            res += getVal(rBlock, b[rBlock].l, r, llBlock, ll, rr);
        } else {
            res += getVal(lBlock, l, r, llBlock, ll, rr, 0, 1);
        }
    }
    return 0;
}
