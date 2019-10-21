#include <bits/stdc++.h>

using namespace std;

vector< map<string, int> > to;
vector<int> sum_size;
int n, t;

vector<string> split(const string &s) {
    vector<string> res;
    int last_slash = -1;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '/') {
            if (last_slash + 1 < i) res.push_back(s.substr(last_slash + 1, i - last_slash - 1));
            last_slash = i;
        }
    }
    return res;
}

void go(const vector<string> &path, int sz) {
    int u = 0;
    for (const string &dir : path) {
        if (to[u][dir] == 0) {
            to[u][dir] = to.size();
            to.push_back(map<string, int>());
        }
        u = to[u][dir];
    }
    if (sum_size.size() < to.size()) {
        sum_size.resize(to.size());
    }
    sum_size[u] += sz;
}

void dfs(int u) {
    for (const auto &it : to[u]) {
        dfs(it.second);
        sum_size[u] += sum_size[it.second];
    }
}

void answer(int u, string path) {
    int max_child = 0;

    if (to[u].empty()) {
        cout << "  ";
    } else {
        for (const auto &it : to[u]) {
            max_child = max(max_child, sum_size[it.second]);
        }
        if (max_child >= t) {
            cout << "- ";
        } else {
            cout << "+ ";
        }
    }
    cout << path << "/ " << sum_size[u] << '\n';
    if (max_child >= t) {
        for (const auto &it : to[u]) {
            answer(it.second, path + "/" + it.first);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    to.push_back(map<string, int>());
    for (int i = 1; i <= n; ++i) {
        string s;
        int sz;
        cin >> s >> sz;
        go(split(s), sz);
    }
    cin >> t;
    dfs(0);
    answer(0, "");
}