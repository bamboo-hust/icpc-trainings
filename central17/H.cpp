#include <bits/stdc++.h>

using namespace std;

const int oo = 2e9;

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

const int N = 1e5;

int n, k;
int used[N];
int in[N];
int res[2][N];

int main() {
    scanf("%d %d", &n, &k);
    n *= 2;
    DinicFlow f(n * 2 + 2, 0, n * 2 + 1);
    for (int i = 1; i <= n; i++) {
        f.addEdge(0, i, 1);
        f.addEdge(i + n, n * 2 + 1, 1);
    }
    for (int i = 1; i <= k; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        f.addEdge(u, v + n, 1);
        f.addEdge(v, u + n, 1);
    }
    int foo = f.maxFlow();
    foo /= 2;
    for (int i = 1; !used[i] && i <= n; i++) {
        for (int j = 0; j < f.a[i].size(); j++) {
            int id = f.a[i][j];
            int to = f.e[id].y;
            if (to <= n * 2 && to > n && f.e[id].flow == 1) {
                if (used[i] == 0 && used[to - n] == 0) {
                    used[i] = to - n;
                    used[to - n] = i;
                }
            }
        }
    }
    puts("YES");
    printf("%d\n", foo);
    int cur = 0;
    vector <int> rest;
    for (int i = 1; i <= n; i++) {
        if (in[i]) {
            continue;
        }
        if (used[i] == 0) {
            rest.push_back(i);
            continue;
        }
        cur++;
        in[i] = 1;
        in[used[i]] = 1;
        res[0][cur] = i;
        res[1][cur] = used[i];
    }
    for (int i = 0; i < rest.size(); i++) {
        cur++;
        res[0][cur] = rest[i];
        res[1][cur] = rest[i + 1];
        i++;
    }
    for (int i = 1; i < n; i++) {
        int foo = res[1][1];
        for (int j = 1; j < cur; j++) {
            res[1][j] = res[1][j + 1];
        }
        res[1][cur] = res[0][cur];
        for (int j = cur; j > 2; j--) {
            res[0][j] = res[0][j - 1];
        }
        res[0][2] = foo;
        for (int j = 1; j <= cur; j++) {
            printf("%d ", res[0][j]);
        }
        printf("\n");
        for (int j = 1; j <= cur; j++) {
            printf("%d ", res[1][j]);
        }
        printf("\n");
    }
    return 0;
}