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
		if (skipBlanks()) {	s.clear(); s += peekChar();
			while (!isBlank(nextChar())) s += peekChar(); }
		return *this; }

	inline IO& operator >> (double & d) { if ((*this) >> tmp) sscanf(tmp, "%lf", &d); return *this;	}

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

const int N = 400005;
pair<int, int> a[N];
int n;

struct InnerBIT {
    vector<int> index;
    int n;
    int *a;

    void addIndex(int i) { index.push_back(i); }
    inline int getIndex(int i) {
        int ans = lower_bound(index.begin(), index.end(), i) - index.begin();
        if (ans == index.size() || index[ans] != i) return ans;
        return ++ans;
    }
    void initialize() {
        sort(index.begin(), index.end());
        index.resize(unique(index.begin(), index.end()) - index.begin());
        n = index.size();
        if (n == 0) return;
        a = new int[n + 1];
        for (int i = 1; i <= n; ++i) a[i] = 0;
    }

    void update(int i) {
        for (i = getIndex(i); i <= n; i += i & -i) a[i] += 1;
    }
    int get(int i) {
        int ans = 0;
        for (i = getIndex(i); i; i -= i & -i) ans += a[i];
        return ans;
    }
};

InnerBIT BIT_2D[N];
int size;

void addIndex(int i, int j) {
    for (; i <= size; i += i & -i) BIT_2D[i].addIndex(j);
}
void initialize() {
    for (int i = 1; i <= size; ++i) BIT_2D[i].initialize();
}
void update(int i, int j) {
    for (; i <= size; i += i & -i) if (BIT_2D[i].n) BIT_2D[i].update(j);
}
int get(int i, int j) {
    int ans = 0;
    for (; i; i -= i & -i) if (BIT_2D[i].n) ans += BIT_2D[i].get(j);
    return ans;
}

void gen(int n) {
    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; ++i) x[i] = y[i] = i;
    random_shuffle(x.begin() + 1, x.end());
    random_shuffle(y.begin() + 1, y.end());
    for (int i = 1; i <= n; ++i) a[i] = make_pair(x[i], y[i]);

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ans += x[i] > x[j] || y[i] > y[j];
        }
    }
    cout << "naive " << ans << endl;

}

int main() {
    //ios::sync_with_stdio(false);
    
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        a[x] = make_pair(y, z);
    }
    
    //gen(n = 4000);
    size = n;

    for (int i = 1; i <= n; ++i) {
        addIndex(a[i].first, a[i].second);
    }
    initialize();

    long long ans = 1LL * n * (n - 1) / 2;
    
    for (int i = 1; i <= n; ++i) {
        ans -= get(a[i].first, a[i].second);
        update(a[i].first, a[i].second);
    }
    
    cout << ans << endl;
    //cerr << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}