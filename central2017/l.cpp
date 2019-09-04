#include <bits/stdc++.h>

using namespace std;

const int L = 12;
const int N = 5e4 + 5;

string s[N];

int to[N * L][33];
int mask[N * L];
int size;

void addString(string &s) {
    //cerr << "addString " << s << endl;
    int curNode = 1;
    for (int i = 0; i < s.size(); ++i) {
        int c = s[i] - 'a';
        mask[curNode] |= 1 << c;
        if (to[curNode][c] == 0) {
            //cerr << "edge " << curNode << ' ' << size+1 << ' ' << c << endl;
            to[curNode][c] = ++size;
        }
        curNode = to[curNode][c];   
    }
}

vector<int> a[33];
bool hasCycle;
bool was[33], inStack[33];

void dfs(int u) {
    was[u] = inStack[u] = true;
    for (int i = 0; i < a[u].size(); ++i) {
        int v = a[u][i];
        if (inStack[v]) {
            hasCycle = true;
        }
        if (!was[v]) dfs(v);
    }
    inStack[u] = false;
}

int n;

bool solve(string &s) {
    for (int i = 0; i < 33; ++i) a[i].clear();

    int curNode = 1;
    for (int i = 0; i < s.size(); ++i) {
        int cur = s[i] - 'a';
        for (int other = 0; other < 26; ++other) if (mask[curNode] >> other & 1) {
            if (cur != other) {
                //cerr << s << " " << char('a'+cur) << "->" << char('a'+other) << endl;
                a[cur].push_back(other);
            }
        }
        curNode = to[curNode][cur];
    }

    for (int i = 0; i < 33; ++i) was[i] = inStack[i] = false;
    hasCycle = false;
    for (int i = 0; i < 26; ++i) if (!was[i]) dfs(i);
    return !hasCycle;
}

int main() {
    ios::sync_with_stdio(false);
    size = 1;
    cin >> n;
    vector<string> st;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        st.push_back(s[i]);
    }
    sort(st.begin(), st.end());
    set<string> rel;
    for (int i = 0; i < st.size(); ++i) {
        if (i > 0 && st[i - 1].size() < st[i].size() && st[i].substr(0, st[i - 1].size()) == st[i - 1]) continue;
        addString(st[i]);
        rel.insert(st[i]);
    }
    
    vector<string> ans;
    for (int i = 1; i <= n; ++i) {
        if (rel.count(s[i]) && solve(s[i])) {
            ans.push_back(s[i]);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}