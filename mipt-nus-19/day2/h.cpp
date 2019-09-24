#include <bits/stdc++.h>

using namespace std;

char res[2][100];
char foo[2][40];

pair<int, int> getVal(int u) {
    u %= 16;
    if (u > 7) {
        return {1, 15 - u};
    } else {
        return {0, u};
    }
}

void output(int x, int y, int a, int b, int buy) {
    memset(foo, '.', sizeof foo);
    for (int i = x; i <= y; i++) {
        pair<int, int> now = getVal(i);
        foo[now.first][now.second] = '*';
    }
    for (int i = 0; i < 4; i++) {
        res[0][i] = foo[0][i];
        res[1][i] = foo[1][i];
    }
    for (int i = 4; i < 8; i++) {
        res[0][i + 1] = foo[0][i];
        res[1][i + 1] = foo[1][i];
    }
    memset(foo, '.', sizeof foo);
    for (int i = a; i <= b; i++) {
        pair<int, int> now = getVal(i);
        foo[now.first][now.second] = '*';
    }
    for (int i = 0; i < 4; i++) {
        res[0][14 + i] = foo[0][i];
        res[1][14 + i] = foo[1][i];
    }
    for (int i = 4; i < 8; i++) {
        res[0][14 + i + 1] = foo[0][i];
        res[1][14 + i + 1] = foo[1][i];
    }
    res[0][4] = res[1][4] = res[0][18] = res[1][18] = '|';
    res[0][9] = res[0][13] = ' ';
    res[1][9] = res[1][10] = res[1][11] = res[1][12] = res[1][13] = ' ';
    if (buy) {
        res[0][10] = 'b';
        res[0][11] = 'u';
        res[0][12] = 'y';
    } else {
        res[0][10] = 'e';
        res[0][11] = 'a';
        res[0][12] = 't';
    }
    for (int i = 0; i < 23; i++) {
        cout << res[0][i];
    }
    cout << '\n';
    for (int i = 0; i < 23; i++) {
        cout << res[1][i];
    }
    cout << '\n';
    cout << "---\n";
}

int main() {
    cout << "....|.... buy ****|****\n";
    cout << "....|....     ....|..**\n";
    cout << "---\n";
    for (int i = 0; i < 16; i++) {
        for (int j = i; j < i + 15; j++) {
            output(i, j, i + 1, j, 0);
            if (j - i + 1 <= 5) output(i, j, i, j + 10, 1);
        }
    }
    return 0;
}