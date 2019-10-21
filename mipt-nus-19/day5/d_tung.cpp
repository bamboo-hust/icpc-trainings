#include <bits/stdc++.h>

using namespace std;


int const N = 1e4 + 5;
int const NN = 105;

int const MOD = 998244353;

char a[NN][NN];
vector < int > adj[N];
int n, m, ok[N], num_edge, num_vertex, tot = 0;
bool self_loop;



int get(int x, int y) {
	return (x - 1) * m + y;
}

void dfs(int u, int pre = 0) {
	num_vertex++;
	ok[u] = ++tot;
	for (int v : adj[u]) {
		if (v == pre) {
			continue;
		}
		if (ok[v]) {
			if (v == u) {
				self_loop = true;
			}
			continue;
		}
		dfs(v, u);
	}
	for (int v : adj[u]) {
		num_edge += (ok[u] >= ok[v]);
	}
}

void solve() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == '*') {
				int type = (a[i][j - 1] == '.') + (a[i][j + 1] == '.');
				int u = get(i, j - 1);
				int v = get(i, j + 1);
				if (type == 0) {
					cout << 0 << endl;
					return;
				}
				if (type == 1) {
					if (a[i][j - 1] == '.') {
						adj[u].push_back(u);
					} else {
						adj[v].push_back(v);
					}
				} else {
					adj[u].push_back(v);
					adj[v].push_back(u);
				}

				//cout << "u v : " << u << " " << v << endl;

				type = (a[i - 1][j] == '.') + (a[i + 1][j] == '.');
				u = get(i - 1, j);
				v = get(i + 1, j);
				if (type == 0) {
					cout << 0 << endl;
					return;
				}


				if (type == 1) {
					if (a[i - 1][j] == '.') {
						adj[u].push_back(u);
					} else {
						adj[v].push_back(v);
					}
				} else {
					adj[u].push_back(v);
					adj[v].push_back(u);
				}				
				// cout << "u v : " << u << " " << v << endl;
			}
		}
	}
	long long ans = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int u = get(i, j);
			if (ok[u]) {
				continue;
			}
			num_edge = num_vertex = 0;
			self_loop = false;
			dfs(u);
			if (num_edge > num_vertex) {
				cout << 0 << endl;
				return;
			}
			if (num_edge == num_vertex) {
				if (self_loop == false) {
					ans = ans * 2 % MOD;
				}
				continue;
			}
			assert(num_edge == num_vertex - 1);
			ans = ans * num_vertex % MOD;
		}
	}

	cout << ans << endl;

}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 0; i <= n + 1; i++) {
			for (int j = 0; j <= m + 1; j++) {
				a[i][j] = '*';
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
				adj[get(i, j)].clear();
				ok[get(i, j)] = 0;
			}
		}


		solve();
	}
}