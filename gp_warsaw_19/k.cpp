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


const int N = 300030;
const int B = 3 * sqrt(N);

int n, q;
int last_built;

string s;
vector<int> kmp;

int timestamp;
int tin[N];
int tout[N];

int built_parent[N];
int parent[N];
int subtree_size[N];

vector<int> a[N];
vector<int> roots;

void dfs(int u) {
    tin[u] = timestamp++;
    subtree_size[u] = 1;
    for (int v : a[u]) {
        dfs(v);
        subtree_size[u] += subtree_size[v];
    }
    tout[u] = timestamp;
}

bool is_ancestor(int u, int v) {
    if (v < 0) return false;
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

void update_kmp() {
    if (s.size() == 1) {
        kmp.push_back(0);
    } else {
        int j = kmp.back();
        while (j && s[j] != s.back()) j = kmp[j - 1];
        kmp.push_back(j + (s[j] == s.back()));
    }
}

int update_to_parent(int u) {
    if (u < last_built) return u;
    subtree_size[u]++;
    return update_to_parent(parent[u]);
}

void rebuild() {
    timestamp = 0;
    for (int u : roots) dfs(u);
}

void append(char c) {
    s += c;
    n = s.size();
    update_kmp();

    tin[n - 1] = tout[n - 1] = -1;

    parent[n - 1] = kmp[n - 1] - 1;
    if (parent[n - 1] < 0) {
        roots.push_back(n - 1);
    } else {
        if (n > 1) a[parent[n - 1]].push_back(n - 1);
    }

    if (last_built == 0 || n - last_built >= B) {
        rebuild();
        last_built = n;
    } else {
        built_parent[n - 1] = update_to_parent(n - 1);
    }
}

int query(int k) {
    --k;
    int res = subtree_size[k];
    if (k < last_built) {
        for (int u = last_built; u < n; ++u) {
            res += is_ancestor(k, built_parent[u]);
        }
    }
    return res;
}


int main() {
    //ios::sync_with_stdio(false); cin.tie(nullptr);

    int last = 0;
    cin >> q;
    for (int it = 0; it < q; ++it) {
        char cmd[5];
        cin >> cmd;
        if (cmd[0] == 'a') {
            char c; cin >> c;
            c = char('a' + (c - 'a' + last) % 26);
            append(c);
        } else {
            int k; cin >> k;
            k = (k - 1 + last) % n + 1;
            cout << (last = query(k)) << '\n';
        }
    }

    return 0;
}