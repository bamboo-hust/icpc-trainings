#include <bits/stdc++.h>

using namespace std;

const int N = 2019;

int cache[N][N];
int n;

int max_so_far = 0;
int max_x, max_y;

int cnt;

int get(int i, int j) {
    if (i < 1 || j < 1 || i > n || j > n) return 0;

    int &res = cache[i][j];
    if (res) return res;

    ++cnt;
    assert(cnt <= 3 * n + 210);

    cout << "? " << i << ' ' << j << endl;
    cin >> res;

    if (max_so_far < res) {
        max_so_far = res;
        max_x = i; max_y = j;
    }

    return res;
}

void get_max_col(int col, int up, int down, int &x, int &y) {
    //cerr << "get_max_col " << col << ' ' << up << ' ' << down << endl;
    x = up; y = col;
    int cur = get(x, y);
    for (int i = up + 1; i <= down; ++i) {
        if (cur < get(i, col)) {
            cur = get(i, col);
            x = i;
        }
    }
}

void get_max_row(int row, int left, int right, int &x, int &y) {
    //cerr << "get_max_row " << row << ' ' << left << ' ' << right << endl;
    x = row; y = left;
    int cur = get(x, y);
    for (int i = left + 1; i <= right; ++i) {
        if (cur < get(row, i)) {
            cur = get(row, i);
            y = i;
        }
    }
}

void get_max_neighbor(int x, int y, int &u, int &v) {
    u = x; v = y;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (get(u, v) < get(x + i, y + j)) {
                u = x + i; v = y + j;
                //return; // SURE?
            }
        }
    }
}

void answer(int x, int y) {
    cout << "! " << x << ' ' << y << endl;
    exit(0);
}

int main() {
    cin >> n;
    int left = 1, right = n;
    int up = 1, down = n;
    while (left < right || up < down) {
        int x, y, u, v;
        if (right - left > down - up) {
            int m = left + right >> 1;
            get_max_col(m, up, down, x, y);
            get_max_neighbor(x, y, u, v);
            if (x == u && y == v) answer(x, y);
            if (max_y < m) {
                right = m - 1;
            } else {
                left = m + 1;
            }
        } else {
            int m = up + down >> 1;
            get_max_row(m, left, right, x, y);
            get_max_neighbor(x, y, u, v);
            if (x == u && y == v) answer(x, y);
            if (max_x < m) {
                down = m - 1;
            } else {
                up = m + 1;
            }
        }
    }
    answer(up, left);
}