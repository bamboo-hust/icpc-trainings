#include <bits/stdc++.h>

using namespace std;

const int N = 10010;
const int H = 5010;
const int M = H;

bitset<N> removed[H];
int level[M], pos[M];

int64_t L[H], R[H];
int64_t sum[H], sum_weighted[H];
int n, w, maxh, m;

void read() {
    cin >> n >> w;
    cin >> maxh >> m;

    for (int i = 1; i <= m; ++i) {
        cin >> level[i] >> pos[i];
    }
}

bool do_remove(int h, int p) {
    for (int i = h - 2; i >= 1; i -= 2) {
        sum[i] -= n;
        sum_weighted[i] -= p * n * 2 - n;
    }
    for (int i = h - 1; i >= 1; i -= 2) {
        sum[i] -= n;
        sum_weighted[i] -= n * n;
    }
    removed[h].set(p);
    while (L[h] <= n && removed[h][L[h]]) L[h]++;
    while (R[h] >= 1 && removed[h][R[h]]) R[h]--;
    for (int i = min(h, maxh - 1); i >= 1; --i) {
        if (((L[i] - 1) * sum[i] * 2 >= sum_weighted[i]) || (sum_weighted[i] >= R[i] * sum[i] * 2)) {
            return true;
        }
    }
    return false;
}

int main() {
    freopen("jenga.in", "r", stdin);
    freopen("jenga.out", "w", stdout);
    read();

    for (int i = 1; i <= maxh; ++i) {
        L[i] = 1;
        R[i] = n;
        for (int j = i + 1; j <= maxh; j += 1) {
            sum[i] += n * n;
            sum_weighted[i] += 1LL * n * n * n;
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (do_remove(level[i], pos[i])) {
            cout << "yes\n" << i << endl;
            return 0;
        }
    }

    cout << "no\n";
}