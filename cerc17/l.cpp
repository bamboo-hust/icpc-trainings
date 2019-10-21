#include <bits/stdc++.h>

using namespace std;

int const N = 1510;

int appear[5][N * 2][N * 2];

inline void mark(int xf, int yf, int xs, int ys, int type, int num_step) {
    if (yf > ys) {
        swap(xf, xs);
        swap(yf, ys);
    }
    appear[type][xf + N][yf + N]++;
    if (type == 0 || type == 2) {
        xs++;
    } else {
        xs--;
    }
    ys++;

    appear[xs + N][ys + N][type]--;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int n;
//    cin >> n;
    n = 2e5;
    for (int i = 1; i <= n; i++) {
        char type;
        int x, y, d;
        //cin >> type >> x >> y >> d;
        d = 1000; x = rand() % 1000 - rand() % 1000; y = rand() % 1000 - rand() % 1000; type = 'B';
        d /= 2;
        if (type == 'A') {
            for (int j = y - d; j <= y + d - 1; j++) {
                appear[4][x - d + N][j + N]++;
                appear[4][x + d + N][j + N]--;
            }
            continue;
        }
        mark(x - d, y, x - 1, y + d - 1, 0, d - 1);
        mark(x - d, y - 1, x - 1, y - d, 3, d - 1);
        mark(x, y - d, x + d - 1, y - 1, 2, d - 1);
        mark(x + d - 1, y, x , y + d - 1, 1, d - 1);

        for (int j = 0; j < d - 1; j++) {
            int xmin = x - d + j + 1;
            int xmax = x + d - j - 1;
            appear[4][xmin + N][y + j + N]++;
            appear[4][xmax + N][y + j + N]--;

        }
/*
        for (int j = -1; j >=  -d + 1; j--) {
            int xmin = x - d - j;
            int xmax = x + d + j;
            appear[4][xmin + N][y + j + N]++;
            appear[4][xmax + N][y + j + N]--;
        }
*/
//        return 0;
    }

    for (int j = 1; j < 2 * N; j++) {
        for (int i = 1; i + 1 < 2 * N; i++) {
            appear[4][i][j][4] += appear[4][i - 1][j][4];
            appear[i][j][0] += appear[i - 1][j - 1][0];
            appear[i][j][2] += appear[i - 1][j - 1][2];
            appear[i][j][1] += appear[i + 1][j - 1][1];
            appear[i][j][3] += appear[i + 1][j - 1][3];
        }
    }

    double ans = 0;
    for (int i = 0; i < 2 * N; i++) {
        for (int j = 0; j < 2 * N; j++) {
            if (appear[i][j][4] > 0) {
                ans++;
                continue;
            }
            int type1 = (appear[i][j][0] != 0) + (appear[i][j][2] != 0);
            int type2 = (appear[i][j][1] != 0) + (appear[i][j][3] != 0);
            if (type1 == 2 || type2 == 2) {
                ans++;
                continue;
            }
            if (type1 == 1 && type2 == 1) {
                ans += 1.0 * 3 / 4;
                continue;
            }
            if (type1 == 1 || type2 == 1) {
                ans += 1.0 / 2;
            }
        }
    }
    cout << setprecision(2) << fixed << ans << endl;
}