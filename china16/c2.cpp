#include <bits/stdc++.h>

using namespace std;

const int N = 1024;

int a[N];
int n;
vector<int> V;
vector<int> pos[N];

int lab[N];
int comsize[N];
int max_size;

bool status[N];

int root(int u) {
    if (lab[u] == -1) return u;
    return lab[u] = root(lab[u]);
}

void join(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    lab[u] = v;
    comsize[v] += comsize[u];
}

void debug() {
    for (int i = 0; i < n; ++i) {
        cout << status[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << comsize[root(i)] << ' ';
    }
    cout << endl << endl;
}

void turn_on(int i) {
    if (status[i]) return;
    status[i] = true;
    comsize[i] = 1;
    if (i > 0 && status[i - 1]) {
        join(i - 1, i);
    }
    if (i + 1 < n && status[i + 1]) {
        join(i, i + 1);
    }
    max_size = max(max_size, comsize[root(i)]);
    debug();
}

void reset_dsu() {
    for (int i = 0; i < n; ++i) {
        lab[i] = -1;
        comsize[i] = 0;
        status[i] = false;
    }
    max_size = 0;
}

void create_pos() {
    for (int i = 0; i < n; ++i) {
        pos[a[i]].push_back(i);
    }
}

void compress() {
    V = vector<int>(a, a + n);
    sort(begin(V), end(V));
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(begin(V), end(V), a[i]) - begin(V);
    }
}

void read_input() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
}

int main() {
    ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        read_input();
        compress();
        create_pos();

        int res = 0;

        for (int i = n - 1; i >= 0; --i) {
            reset_dsu();
            vector<bool> can_use(n, true);
            vector<int> cnt(V.size());
            int num_distinct = 0;
            for (int j = i; j < n; ++j) {
                cnt[a[j]]++;
                if (cnt[a[j]] == 1) {
                    ++num_distinct;
                    for (int p : pos[a[j]]) {
                        if (p >= i) break;
                        can_use[p] = false;
                    }
                }
            }
            for (int j = 0; j < i; ++j) if (can_use[j]) {
                turn_on(j);
            }
            cerr << "first phase " << i << endl;
            
            vector<bool> turned_on_prefix(V.size());
            vector<int> last_turned_on_suffix(V.size());
            for (int j = n - 1; j >= i; --j) {
                if (num_distinct == j - i + 1) res = max(res, num_distinct + max_size);
                // remove j
                cnt[a[j]]--;
                if (cnt[a[j]] == 0) --num_distinct;
                if (!turned_on_prefix[a[j]]) {
                    for (int p : pos[a[j]]) {
                        if (p >= i) break;
                        turn_on(p);
                    }
                }
                auto it = lower_bound(begin(pos[a[j]]), end(pos[a[j]]), j);
                while (it != end(pos[a[j]]) && (*it) < last_turned_on_suffix[a[j]]) {
                    turn_on(*it);
                    ++it;
                }
                last_turned_on_suffix[a[j]] = j;
            }
        }

        for (int i = 0; i < n; ++i) {
            pos[a[i]].clear();
        }

        cout << "Case #" << tc << ": " << res << '\n';
    }
}