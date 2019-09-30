//
// Created by lad on 9/27/19.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 55;
const int K = 12;
const int X[] = {0, 1, 0, -1};
const int Y[] = {1, 0, -1, 0};
const int INF = 1e9;

int h, w, k;
int s, t, tMove, tCheck;
char a[N][N];
int minDist[N][N][N][N];
int used[N][N];
vector<pair<int, int>> lsRoom[K];
map<char, int> mapColor;

inline bool inside(int u, int v) {
    return u >= 0 && u < h && v >= 0 && v < w;
}

void buildMinDist(int rootU, int rootV) {
    for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) used[i][j] = 0, minDist[rootU][rootV][i][j] = INF;
    queue<pair<int, int>> q;
    q.push({rootU, rootV});
    used[rootU][rootV] = 1;
    minDist[rootU][rootV][rootU][rootV] = 0;
    while (!q.empty()) {
        int u, v;
        tie(u, v) = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int uu = u + X[dir];
            int vv = v + Y[dir];
            if (!inside(uu, vv) || used[uu][vv] || a[uu][vv] == '.') continue;
            used[uu][vv] = 1;
            q.push({uu, vv});
            minDist[rootU][rootV][uu][vv] = minDist[rootU][rootV][u][v] + 1;
        }
    }
}

int countAdj(int u, int v) {
    int res = 0;
    for (int i = 0; i < 4; i++) {
        int uu = u + X[i];
        int vv = v + Y[i];
        if (!inside(uu, vv) || a[uu][vv] == '.') continue;
        res++;
    }
    return res;
}

int minCostForOneColor[K][K][K];
int dp[K][K][1 << K];

void initDp(int room) {
    int sz = lsRoom[room].size();
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            minCostForOneColor[room][i][j] = INF;
            for (int mask = 0; mask < (1 << sz); mask++) {
                dp[i][j][mask] = (mask == 0 ? 0 : INF);
            }
        }
    }
    for (int i = 0; i < sz; i++) {
        int u, v;
        tie(u, v) = lsRoom[room][i];
        dp[i][i][1 << i] = minDist[s][t][u][v];
    }
    for (int mask = 0; mask < (1 << sz); mask++) {
        for (int i = 0; i < sz; i++) {
            if (!(mask >> i & 1)) continue;
            for (int j = 0; j < sz; j++) {
                if (!(mask >> j & 1)) continue;
                if (dp[i][j][mask] >= INF) continue;
                for (int k = 0; k < sz; k++) {
                    if ((mask >> k & 1)) continue;

                    int ui, vi;
                    int uj, vj;
                    int uk, vk;
                    tie(ui, vi) = lsRoom[room][i];
                    tie(uj, vj) = lsRoom[room][j];
                    tie(uk, vk) = lsRoom[room][k];

                    dp[i][k][mask | (1 << k)] = min(dp[i][k][mask | (1 << k)], dp[i][j][mask] + minDist[uj][vj][uk][vk]);
                }
            }
        }
    }
    int lastMask = (1 << sz) - 1;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            int u, v;
            tie(u, v) = lsRoom[room][j];

            minCostForOneColor[room][i][j] = min(minCostForOneColor[room][i][j], dp[i][j][lastMask] + minDist[u][v][s][t]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> h >> w >> k;
    cin >> s >> t >> tMove >> tCheck;
    s--, t--;
    for (int i = 0; i < h; i++) cin >> a[i];
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] != '.') buildMinDist(i, j);
        }
    }
    int numColor = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] == '.') continue;
            if (mapColor.count(a[i][j])) continue;
            mapColor[a[i][j]] = numColor++;
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] == '.') continue;
            int foo = countAdj(i, j);
            if (foo == 1) lsRoom[mapColor[a[i][j]]].push_back({i, j});
        }
    }
    for (int i = 0; i < numColor; i++) {
        initDp(i);
    }
     
    return 0;
}