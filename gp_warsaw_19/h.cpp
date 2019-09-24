#include <bits/stdc++.h>

#define double long double

using namespace std;

const int N = 3e5 + 5;
const double INF = 1e9;

vector<int> cand[N];
vector<int> a[N];
double E[N];
double power[N];
int n, m;

void gen1() {
    n = 18;
    for (int i = 2; i < n; ++i) {
        a[1].push_back(i); a[i].push_back(1);
        a[i].push_back(n); a[n].push_back(i);
        m += 2;
    }
}

void gen2() {
    n = 1000;
    m = 3000;
    set< pair<int, int> > edges;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        do {
            u = rand() % n + 1;
            v = rand() % n + 1;
        } while (u == v || edges.count(make_pair(u, v)));
        a[u].push_back(v);
        a[v].push_back(u);
    }

}

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    //gen2();

    power[0] = 1.0;
    for (int i = 1; i < N; ++i) {
        power[i] = power[i - 1] / 4.0;
    }

    set< pair<double, int> > Q;
    for (int i = 1; i <= n; ++i) E[i] = INF;

    E[n] = 0.0;
    Q.insert(make_pair(0.0, n));
    while (!Q.empty()) {
        int v = Q.begin()->second; Q.erase(Q.begin());
        for (int u : a[v]) {
            double Eu = E[u];
            if (cand[u].empty()) {
                Eu = 1.5 + E[v];
            } else {
                Eu -= power[cand[u].size()] * (0.5 + E[cand[u][0]] - E[v]);
            }
            if (E[u] > Eu) {
                cand[u].push_back(v);
                if (E[u] < INF) Q.erase(make_pair(E[u], u));
                E[u] = Eu;
                Q.insert(make_pair(E[u], u));
            }
        }
    }

    cout << setprecision(14) << fixed << E[1] << endl;
}