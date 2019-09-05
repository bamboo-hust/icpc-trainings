#include <bits/stdc++.h>

using namespace std;

const int oo = 1e9;
const int N = 111;

struct edge {
	int x, y, cap, flow;
};

struct DinicFlow {
	int n, S, T;
	vector < vector <int> > a;
	vector <int> cur, d;
	vector <edge> e;
	
	DinicFlow() {}
	DinicFlow(int n, int S, int T) {
		this -> n = n;
		this -> S = S;
		this -> T = T;
		a = vector < vector <int> >(n + 1);
		cur = vector <int>(n + 1);
		d = vector <int>(n + 1);
	}
	
	void addEdge(int x, int y, int cap) {
		edge e1 = {x, y, cap, 0};
		edge e2 = {y, x, 0, 0};
		a[x].push_back(e.size()); e.push_back(e1);
		a[y].push_back(e.size()); e.push_back(e2);
	}
	
	int bfs() {
		queue <int> q;
		for (int i = 1; i <= n; i++) d[i] = -1;
		q.push(S); d[S] = 0;
		while (!q.empty() && d[T] < 0) {
			int x = q.front(); q.pop();
			for (int i = 0; i < int(a[x].size()); i++) {
				int id = a[x][i], y = e[id].y;
				if (d[y] < 0 && e[id].flow < e[id].cap)
					q.push(y), d[y] = d[x] + 1;
			}
		}
		return d[T] >= 0;
	}
	
	int dfs(int x, int val) {
		if (!val) return 0;
		if (x == T) return val;
		for (; cur[x] < int(a[x].size()); cur[x]++) {
			int id = a[x][cur[x]], y = e[id].y;
			if (d[y] != d[x] + 1) continue;
			int pushed = dfs(y, min(val, e[id].cap - e[id].flow));
			if (pushed) {
				e[id].flow += pushed;
				e[id ^ 1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
	
	int maxFlow() {
		int res = 0;
		while (bfs()) {
			for (int i = 1; i <= n; i++) cur[i] = 0;
			while (1) {
				int val = dfs(S, oo);
				if (!val) break;
				res += val;
			}
		}
		return res;
	}	
};

char a[N][N];

int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        cin >> (a[i] + 1);
    }
    DinicFlow G(m + n + 2, m + n + 1, m + n + 2);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i][j] == '#') {
                G.addEdge(i, m + j, oo);
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        G.addEdge(m + n + 1, i, 1);
    }
    for (int i = 1; i <= n; ++i) {
        G.addEdge(m + i, m + n + 2, 1);
    }
    cout << G.maxFlow() << endl;
}