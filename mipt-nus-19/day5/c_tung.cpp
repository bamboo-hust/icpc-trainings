#include <bits/stdc++.h>

using namespace std;

int const N = 3e5 + 5;
int const MOD = 998244353;
struct Edge
{
	int u, v, id;
	Edge(){};
	Edge(int _u, int _v, int _id) {
		u = _u; v = _v; id = _id;
	}
};

vector < Edge > edges;
vector < int > que[N];

set < pair < int, int > > d[N];
set < int > color[N];
map < int, int > ans[N];
int root[N], n;

int get_root(int u) {
	if (u == root[u]) {
		return u;
	}
	return root[u] = get_root(root[u]);
}

void update(int u, int c, int id) {
	vector < pair < int, int > > vertexs;
	for (auto it = d[u].lower_bound(make_pair(c, 0)); it != d[u].end() && it -> first == c; it++) {
		int u = it -> second;
		if (ans[u][it -> first] == 0) {
			ans[u][it -> first] = id;
		}
		vertexs.push_back(make_pair(it -> first, it -> second));
	}

	for (pair < int, int > p : vertexs) {
		d[u].erase(d[u].find(p));
	}

}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		edges.push_back(Edge(u, v, i));
	}

	int q;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int num;
		cin >> num;
		while (num--) {
			int u;
			cin >> u;
			que[i].push_back(u);
			d[u].insert(make_pair(i, u));
			color[u].insert(i);
		}
	}

	for (int i = 1; i <= n; i++) {
		root[i] = i;
	}

	for (Edge e : edges) {
		int u = e.u;
		int v = e.v;
		int id = e.id;
		u = get_root(u);
		v = get_root(v);
		if (color[u].size() > color[v].size()) {
			swap(color[u], color[v]);
		}
		root[u] = v;

		for (int c : color[u]) {
			if (color[v].find(c) == color[v].end()) {
				continue;
			}
			update(u, c, id);
			update(v, c, id);
		}

		for (int c : color[u]) {
			color[v].insert(c);
		}

		if (d[u].size() > d[v].size()) {
			swap(d[u], d[v]);
		}

		for (pair < int, int > p : d[u]) {
			d[v].insert(p);
		}
	}


	for (int i = 1; i <= q; i++) {
		long long res = 1;
		for (int v : que[i]) {
			res = res * (ans[v][i] ? ans[v][i] : (n)) % MOD;
		}
		cout << res << "\n";
	}

}