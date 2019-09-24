#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int LIMIT = 20;

vector<int> a[N], forbid[N];
int match[N];
bool was[N];
int n;
bool is_tall[N];
int mentor[N];

void init() {
    memset(match, -1, sizeof match);
}

void addEdge(int u, int v) {
    a[u].push_back(v);
}

bool dfs(int u) {
    for (int v : a[u]) if (!was[v]) {
        was[v] = true;
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int maximumMatching() {
    vector<int> buffer;
    for (int i = 0; i < n; ++i) if (is_tall[i]) buffer.push_back(i);
    bool stop = false;
    int ans = 0;
    do {
        stop = true;
        for (int i = 0; i < n; ++i) was[i] = false;
        for (int i = (int)buffer.size() - 1; i >= 0; --i) {
            int u = buffer[i];
            if (dfs(u)) {
                ++ans;
                stop = false;
                buffer[i] = buffer.back();
                buffer.pop_back();
            }
        }
    } while (!stop);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> is_tall[i] >> mentor[i];
        --mentor[i];
    }
    
    for (int i = 0; i < n; ++i) {
        if (is_tall[i] != is_tall[mentor[i]]) {
            if (is_tall[i]) {
                forbid[i].push_back(mentor[i]);
            } else {
                forbid[mentor[i]].push_back(i);
            }
        }
    }

    for (int i = 0; i < n; ++i) if (is_tall[i]) {
        sort(begin(forbid[i]), end(forbid[i]));
        if (forbid[i].size() > n / 10) {
            for (int j = 0; j < n && a[i].size() < LIMIT; ++j) if (!is_tall[j]) {
                if (!binary_search(begin(forbid[i]), end(forbid[i]), j)) {
                    addEdge(i, j);
                }
            }
        } else {
            for (int it = 0; it < 100; ++it) {
                int j = rand() % n;
                if (!is_tall[j] && !binary_search(begin(forbid[i]), end(forbid[i]), j)) {
                    addEdge(i, j);
                }
            }
        }
    }

    init();
    int num_matched = maximumMatching();
    if (num_matched < n / 2) {
        cout << "impossible\n";
        return 0;
    }

    vector<int> ans_tall, ans_short;
    for (int i = 0; i < n; ++i) if (!is_tall[i]) {
        ans_tall.push_back(match[i] + 1);
        ans_short.push_back(i + 1);
    }
    for (int v : ans_tall) cout << v << ' '; cout << endl;
    for (int v : ans_short) cout << v << ' '; cout << endl;
}