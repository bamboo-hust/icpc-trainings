#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int deg[N];
int to[N];
bool use[N];
int n;

void gen() {
    n = 100000;
    for (int i = 1; i <= n; ++i) to[i] = rand() % n + n + 1;
    for (int i = n + 1; i <= 2 * n; ++i) to[i] = rand() % n + 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= 2 * n; ++i) cin >> to[i];

    //gen();

    for (int i = 1; i <= n; ++i) deg[to[i]]++;
    for (int i = 1; i <= n; ++i) use[i] = true;
    queue<int> Q;
    for (int i = n + 1; i <= 2 * n; ++i) {
        if (deg[i] == 0) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        use[u] = true;
        int v = to[u];
        if (!use[v]) continue;
        int w = to[v];
        use[v] = false;
        deg[w]--;
        if (deg[w] == 0) {
            Q.push(w);
        }
    }
    for (int i = 1; i <= 2 * n; ++i) {
        if (use[i]) {
            cout << i << ' ';
        }
    }
    cout << endl;
}