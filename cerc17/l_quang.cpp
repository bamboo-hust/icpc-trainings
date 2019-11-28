#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int MAX = 1550;

int n;
int sum[MAX * 2][MAX * 2];
int cnt[MAX * 2][MAX * 2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char type;
        int x, y, d;
        cin >> type >> x >> y >> d;
        x += MAX, y += MAX;
        d /= 2;
        if (type == 'A') {
            sum[x - d][y - d]++;
            sum[x - d][y + d]--;
            sum[x + d][y - d]--;
            sum[x + d][y + d]++;
        } else {
            cnt[x - d + 1][y]++;
            cnt[x + 1][y - d]--;
            cnt[x + 1][y + d]--;
            cnt[x + d + 1][y]++;
        }
    }
    for (int i = 0; i < MAX * 2; i++) {
        for (int j = 0; j < MAX * 2; j++) {
            if (i > 0) sum[i][j] += sum[i - 1][j];
            if (j > 0) sum[i][j] += sum[i][j - 1];
            if (i > 0 && j > 0) sum[i][j] -= sum[i - 1][j - 1];
     
            if (i > 0) {
                if (j > 0) cnt[i][j] += cnt[i - 1][j - 1];
                if (j + 1 < MAX * 2) cnt[i][j] += cnt[i - 1][j + 1];
            }
            if (i > 2) cnt[i][j] -= cnt[i - 2][j];
        }
    }
    int res = 0;
    for (int i = 0; i + 1 < MAX * 2; i++) {
        for (int j = 0; j + 1 < MAX * 2; j++) {
            if (sum[i][j]) res += 4;
            else {
                if ((cnt[i + 1][j] && cnt[i][j + 1]) || (cnt[i][j] && cnt[i + 1][j + 1])) res += 4;
                else {
                    int tot = 0;
                    tot += !!cnt[i][j];
                    tot += !!cnt[i + 1][j];
                    tot += !!cnt[i][j + 1];
                    tot += !!cnt[i + 1][j + 1];
                    if (tot == 1) res += 2;
                    else if (tot >= 2) res += 3;
                }
            }
        }
    }
    cout << res / 4 << '.' << (res % 4 == 0 ? "00" : res % 4 == 1 ? "25" : res % 4 == 2 ? "50" : "75") << endl;
    return 0;
}