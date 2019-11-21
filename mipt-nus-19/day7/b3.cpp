#include <bits/stdc++.h>

using namespace std;
#define f first
#define s second

int const N = 2e5 + 5;
int const MAX = 1e9 + 5;


struct Vertex
{
	int nearest, cost, id;
	Vertex(){};
	Vertex(int _cost, int _nearest, int _id) {
		cost = _cost;
		nearest = _nearest;
		id = _id;
	}
	bool operator < (const Vertex &p) const {
		if (cost != p.cost) {
			return cost < p.cost;
		}
		if (nearest != p.nearest) {
			return nearest < p.nearest;
		}
		return id < p.id;
	}
};

int n, is_shop[N];
vector < pair < int, int > > a[N];
pair < int, int > closest[N];

struct BIT
{
	int tree[N];
	void update(int x, int val) {
		while (x < N) {
			tree[x] += val;
			x += x & (-x);
		}
	}
	int get(int x) {
		int res = 0;
		while (x) {
			res += tree[x];
			x -= x & (-x);
		}
		return res;
	}
};

BIT tree;

void find_closest() {
	priority_queue < Vertex > que;
	for (int i = 1; i <= n; i++) {
		if (is_shop[i] == 0) {
			closest[i] = make_pair(MAX, i);
			continue;
		}
		closest[i] = make_pair(0, i);
		que.push(Vertex(0, -i, i));
	}

	while (!que.empty()) {
		Vertex top = que.top(); que.pop();
		int cost = -top.cost;
		int u = top.id;
		int nearest = -top.nearest;
		if (closest[u] != make_pair(cost, nearest)) {
			continue;
		}
		for (pair < int, int > p : a[u]) {
			int v = p.f;
			int w = p.s;
			if (is_shop[v]) {
				continue;
			}
			if (closest[v] > make_pair(cost + w, nearest)) {
				closest[v] = make_pair(cost + w, nearest);
				que.push(Vertex(-closest[v].f, -closest[v].s, v));
			}
		}
	}

}

vector < pair < int, int > > val;
int cnt[N], ok[N], d[N], ans[N];

void get_centroid(int u, int pre, int size, int &centroid) {
	cnt[u] = 1;
	bool is_centroid = true;
	for (pair < int, int > p : a[u]) {
		int v = p.f;
		int w = p.s;
		if (v == pre || ok[v]) {
			continue;
		}
		get_centroid(v, u, size, centroid);
		cnt[u] += cnt[v];
		if (cnt[v] > size / 2) {
			is_centroid = false;
		}
	}
	if (size - cnt[u] > size / 2) {
		is_centroid = false;
	}
	if (is_centroid) {
		//cout << "centroid : " << u << " " << cnt[u] << endl;
		centroid = u;
	}
}

void init(int root, int u, int pre) {
	val.push_back(make_pair(d[u], u));
	val.push_back(make_pair(closest[u].f - d[u], closest[u].s));
	if (closest[u] > make_pair(d[u], root)) {
		ans[root]++;
	}
	if (u != root && closest[root] > make_pair(d[u], u)) {
		ans[u]++;
	}
	cnt[u] = 1;
	for (pair < int, int > p : a[u]) {
		int v = p.f;
		int w = p.s;
		if (v == pre || ok[v]) {
			continue;
		}
		d[v] = d[u] + w;
		init(root, v, u);
		cnt[u] += cnt[v];
	}
}

int get_pos(pair < int, int > p) {
	return lower_bound(val.begin(), val.end(), p) - val.begin();
}

void dfs(int u, int pre, int type) {
	if (type == 1) {
		int pos = get_pos(make_pair(d[u], u));
		ans[u] += tree.get(N - 1 - pos);
	}
	if (type == 2) {
		int pos = get_pos(make_pair(closest[u].f - d[u], closest[u].s));
		tree.update(N - 1 - pos, 1);
	}
	if (type == 3) {
		int pos = get_pos(make_pair(closest[u].f - d[u], closest[u].s));
		tree.update(N - 1 - pos, -1);
	}
	for (pair < int, int > p : a[u]) {
		int v = p.f;
		if (v == pre || ok[v]) {
			continue;
		}
		dfs(v, u, type);
	}
}

void update_answer(int centroid) {
	for (pair < int, int > p : a[centroid]) {
		int v = p.f;
		if (ok[v]) {
			continue;
		}
		dfs(v, centroid, 1);
		dfs(v, centroid, 2);
	}

	for (pair < int, int > p : a[centroid]) {
		int v = p.f;
		if (ok[v]) {
			continue;
		}
		dfs(v, centroid, 3);
	}
}


void get_answer(int root, int size) {
	if (size == 0) {
		return;
	}
	int centroid = root;
	get_centroid(root, 0, size, centroid);
	//cout << "root : " << root << " " << centroid << " " << size << " " << endl;
	val.clear();
	d[centroid] = 0;
	init(centroid, centroid, 0);
	sort(val.begin(), val.end());
	update_answer(centroid);
	reverse(a[centroid].begin(), a[centroid].end());
	update_answer(centroid);

	ok[centroid] = 1;
	int total = 0;
	for (pair < int, int > p : a[centroid]) {
		int v = p.f;
		if (ok[v]) {
			continue;
		}
		total += cnt[v];
		get_answer(v, cnt[v]);
	}
	assert(total == size - 1);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	//int step = 1;
	while (cin >> n) {
		//n = 100000;
		for (int i = 1; i <= n; i++) {
			a[i].clear();
			ans[i] = 0;
			ok[i] = 0;
		}
		//cout << n << endl;
		for (int i = 2; i <= n; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			//u = i; v = rand() % (i - 1) + 1; w = rand() % 10 + 1;
			//cout << u << " " << v << " " << w << endl;
			a[u].push_back(make_pair(v, w));
			a[v].push_back(make_pair(u, w));
		}

		for (int i = 1; i <= n; i++) {
			cin >> is_shop[i];
			//is_shop[i] = rand() % 2;
		}

		find_closest();

		get_answer(1, n);
		int res = 0;
		for (int i = 1; i <= n; i++) {
			//cout << i << " " << ans[i] << endl;
			res = max(res, ans[i]);
		}
		cout << res << "\n";
	}
}