#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 110;
 
int n, m;
char s[N][N];
 
int encode(pair<int, int> u) {
    return u.first * m + u.second;
}
 
pair<int, int> decode(int u) {
    return {u / m, u % m};
}
 
struct EulerianGraph {    
    int numEdge, root;
    vector<pair<int, int>> adj[2][N * N];
    int used[N * N * 4];
    vector<int> res;

    EulerianGraph() {
        root = -1;
    }

    void addEdge(int u, int v, bool onFace) {
        if (root == -1 && onFace) root = u;
        adj[onFace][u].push_back({v, numEdge});
        adj[onFace][v].push_back({u, numEdge});
        numEdge++;
    }
    
    void dfs(int u, int onFace) {
        while (!adj[onFace][u].empty()) {
            int v = adj[onFace][u].back().first;
            int edgeId = adj[onFace][u].back().second;
            adj[onFace][u].pop_back();
            if (used[edgeId]) continue;
            used[edgeId] = 1;
            dfs(v, onFace ^ 1);
        }
        res.push_back(u);
    }

    void solve() {
        dfs(root, 1);
        for (int i = 1; i < res.size(); i++) {
            pair<int, int> now = decode(res[i]);
            cout << now.second << ' ' << now.first << '\n';
        }
    }
} eg;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n;
    m++, n++;
    int num = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'X') {
                num++;
                eg.addEdge(encode({i, j}), encode({i + 1, j + 1}), 1);
                eg.addEdge(encode({i + 1, j}), encode({i, j + 1}), 1); 
                eg.addEdge(encode({i, j}), encode({i + 1, j}), 0);
                eg.addEdge(encode({i, j + 1}), encode({i + 1, j + 1}), 0);  
            }
        }
    }
    cout << num * 4 - 1 << '\n';
    eg.solve();
    return 0;
}