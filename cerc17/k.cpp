#include <bits/stdc++.h>

using namespace std;

const int N = 512;
const int NUM = 7;
const int M = 1000;
const int INF = 1e9;

int n;
string s[N];
int isGood[N][NUM];
int dp[N][M];
int p3[NUM];

int encode(const vector<int> &u) {
    int res = 0;
    for (int v : u) {
        res = res * 3;
        res += v;
    }
    return res;
}

vector<int> decode(int u) {
    vector<int> res;
    for (int i = 0; i + 1 < NUM; i++) {
        res.push_back(u % 3);
        u /= 3;
    }
    reverse(res.begin(), res.end());
    return res;
}

int getMask(const vector<int> &now, int mask, int open, int close) {
    if (open == close) return mask;
    if (open) {
        if (now[open - 1] == 2) return -1;
        mask += p3[NUM - open - 1];
    }
    if (close) {
        if (now[close - 1] == 0) return -1;
        mask -= p3[NUM - close - 1];
    }
    return mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> s[i];

    p3[0] = 1;
    for (int i = 1; i < NUM; i++) p3[i] = p3[i - 1] * 3;

    for (int i = 1; i <= n; ++i) {
        vector<int> possible;
        string best = s[i];
        for (int rotation = 0; rotation < 7; ++rotation) {
            string cur = s[i].substr(rotation) + s[i].substr(0, rotation);
            if (best < cur) {
                best = cur;
                possible.clear();
                possible.push_back(rotation);
            } else if (best == cur) {
                possible.push_back(rotation);
            }
        }
        for (int x : possible) {
            isGood[i][x] = 1;
        }
    }

    int maxMask = encode({2, 2, 2, 2, 2, 2});
    for (int i = 0; i < maxMask; i++) {
        dp[n + 1][i] = INF;
    }
    dp[n + 1][0] = 0;


    for (int i = n; i > 0; i--) {
        for (int mask = 0; mask < maxMask; mask++) {
            dp[i][mask] = INF;
            vector<int> now = decode(mask);
            int tot = 0;
            for (int i = 0; i + 1 < NUM; i++) {
                tot = (tot + (i + 1) * now[i]) % NUM;
            }

            for (int open = 0; open < NUM; open++) {
                int nxtTot = (tot + open) % NUM;
                if (!isGood[i][nxtTot]) continue;

                for (int close = 0; close < NUM; close++) {
                    int nxtMask = getMask(now, mask, open, close);
                    if (nxtMask == -1) continue;
                    if (dp[i + 1][nxtMask] == INF) continue;
                    dp[i][mask] = min(dp[i][mask], dp[i + 1][nxtMask] + (open > 0));
                }
            }
        }
    }
    cout << dp[1][0] << endl;
    return 0;
}