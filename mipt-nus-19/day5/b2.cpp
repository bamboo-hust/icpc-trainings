#include <bits/stdc++.h>

using namespace std;

int const N = 3e5 + 5;
int const MAX = 1e9 + 5;
int const NN = 20;

int a[N], n, c[N], root[N];
int maxs[NN][N], mins[NN][N];

// struct Edge
// {	
// 	int u, v, w;
// 	Edge(){};
// 	Edge(int _u, int _v, int _w) {
// 		u = _u; v = _v; w = _w;
// 	}
// };

vector < int > pos[N];


int get_max(int p, int q) {
	if (a[p] < a[q]) {
		return q;
	}
	return p;
}

int get_min(int p, int q) {
	if (a[p] < a[q]) {
		return p;
	}
	return q;
}

int get_max_range(int p, int q) {
	if (p > q) {
		return 0;
	}
	int lo = log2(q - p + 1);
	return get_max(maxs[lo][p], maxs[lo][q - (1 << lo) + 1]);
}

int get_min_range(int p, int q) {
	if (p > q) {
		return n + 1;
	}
	int lo = log2(q - p + 1);
	return get_min(mins[lo][p], mins[lo][q - (1 << lo) + 1]);
}


int get_root(int u) {
	if (u == root[u]) {
		return u;
	}
	return root[u] = get_root(root[u]);
}


void get_pos(vector < int > posi, int i, int &component, long long &ans) {
	posi.push_back(n + 1);
	int cur_max = 0;
	int cur_weight = MAX;
	int optimal = 0;
	for (int j = 1; j < posi.size(); j++) {
		cur_max = get_max(cur_max, get_max_range(posi[j - 1] + 1, posi[j] - 1));
		if (cur_weight > a[posi[j]] - a[cur_max] && cur_max != 0) {
			optimal = cur_max;
			cur_weight = a[posi[j]] - a[cur_max];
		}
	}

	int cur_min = n + 1;
	for (int j = posi.size() - 2; j >= 0; j--) {
		cur_min = get_min(cur_min, get_min_range(posi[j] + 1, posi[j + 1] - 1));
		if (cur_weight > a[cur_min] - a[posi[j]] && cur_min != n + 1) {
			optimal = cur_min;
			cur_weight = a[cur_min] - a[posi[j]];
		}
	}

	int k = c[optimal];
	//cout << k << " " << i << endl;

	int u = get_root(k);
	int v = get_root(i);
	if (u == v) {
		return;
	}
	if (u > v) {
		swap(u, v);
	}
	root[u] = v;
	ans += cur_weight;
	component--;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	//t = 10;
	while (t--) {
		cin >> n;
	//	n = 5;
		a[0] = -MAX; a[n + 1] = MAX;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
	//		a[i] = rand() % 10 + 1;
			maxs[0][i] = mins[0][i] = i;
	//		cout << a[i] << " ";
		}
	//	cout << endl;

		for (int j = 1; j < NN; j++) {
			for (int i = 1; i <= n - (1 << (j - 1)); i++) {
				maxs[j][i] = get_max(maxs[j - 1][i], maxs[j - 1][i + (1 << (j - 1))]);
				mins[j][i] = get_min(mins[j - 1][i], mins[j - 1][i + (1 << (j - 1))]);
			}
		}

		int component = n;
		for (int i = 1; i <= n; i++) {
			c[i] = i;
		}
		long long ans = 0, step = 0;
		while (component > 1) {
			step++;
			for (int i = 1; i <= n; i++) {
				pos[i].clear();
				pos[i].push_back(0);
				root[i] = i;
			}
			for (int i = 1; i <= n; i++) {
				pos[c[i]].push_back(i);
			}

			for (int i = 1; i <= n; i++) {
				if (pos[i].size() <= 1) {
					continue;
				}
				get_pos(pos[i], i, component, ans);
			}

			for (int i = 1; i <= n; i++) {
				c[i] = get_root(c[i]);
			}
		}
		cout << ans << "\n";
		//cout << step << endl;
	}
}