#include <bits/stdc++.h>

using namespace std;

int const N = 1510;

char appear[5][N * 2][N * 2];

inline void mark(int xf, int yf, int xs, int ys, int type) {
    if (yf > ys) {
        swap(xf, xs);
        swap(yf, ys);
    }
    appear[type][yf + N][xf + N]++;
    if (type == 0 || type == 2) {
        xs++;
    } else {
        xs--;
    }
    ys++;

    appear[type][ys + N][xs + N]--;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int n;
    cin >> n;
    //n = 2e5;
    for (int i = 1; i <= n; i++) {
        char type;
        int x, y, d;
        cin >> type >> x >> y >> d;
        //d = 1000; x = rand() % 1000 - rand() % 1000; y = rand() % 1000 - rand() % 1000; type = 'A';
        d /= 2;
        if (type == 'A') {
            for (int j = y - d, Y = j + N, x1 = x - d + N, x2 = x + d + N; j <= y + d - 1; j++, Y++) {
                appear[4][Y][x1]++;
                appear[4][Y][x2]--;
            }
            continue;
        }
        mark(x - d, y, x - 1, y + d - 1, 0);
        mark(x - d, y - 1, x - 1, y - d, 3);
        mark(x, y - d, x + d - 1, y - 1, 2);
        mark(x + d - 1, y, x , y + d - 1, 1);

        int xmin = x - d + (d - 1) + 1 + N;
        int xmax = x + d - (d - 1) - 1 + N;
        for (int j = d - 1, Y = y + j + N; j >= 0; j--, Y--) {
            appear[4][Y][xmin]++;
            appear[4][Y][xmax]--;
            xmin--; xmax++;
        }

        xmin = x - d - (-1) + N;
        xmax = x + d + (-1) + N;
        for (int j = -1, Y = y + j + N; j >= -d + 1; j--, Y--) {
            appear[4][Y][xmin]++;
            appear[4][Y][xmax]--;
            xmin++; xmax--;
        }
//        return 0;
    }

    for (int j = 1; j < 2 * N; j++) {
        for (int i = 1; i + 1 < 2 * N; i++) {
            appear[4][j][i] += appear[4][j][i - 1];
            appear[0][j][i] += appear[0][j - 1][i - 1];
            appear[2][j][i] += appear[2][j - 1][i - 1];
            appear[1][j][i] += appear[1][j - 1][i + 1];
            appear[3][j][i] += appear[3][j - 1][i + 1];
        }
    }

    double ans = 0;
    for (int i = 0; i < 2 * N; i++) {
        for (int j = 0; j < 2 * N; j++) {
            if (appear[4][j][i] > 0) {
                ans++;
                continue;
            }
            int type1 = (appear[0][j][i] != 0) + (appear[2][j][i] != 0);
            int type2 = (appear[1][j][i] != 0) + (appear[3][j][i] != 0);
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