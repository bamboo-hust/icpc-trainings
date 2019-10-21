#include <bits/stdc++.h>

using namespace std;

int const N = 55;

int n , m = 11, mid;
char a[N][N];



int count(int x) {
    int cnt = 0;
    for (int j = 1; j <= m; j++) {
        cnt += a[x][j] == '-';
    }
    return cnt;
}

int count_seat(int x, int y) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = x; j <= y; j++) {
            cnt += a[i][j] == '-';
        }
    }
    return cnt;
}

int get_dis(int x) {
    return min(min(abs(x - 1), abs(x - mid)), abs(x - n));
}

bool cmp(int p, int q) {
    if (count(p) != count(q)) {
        return count(p) > count(q);
    }
    if (get_dis(p) != get_dis(q)) {
        return get_dis(p) < get_dis(q);
    }
    return p < q;
}

bool pick(int res_id, int x, int y, bool choose_left, char guess) {
    int type = (a[res_id][x] == '-') + (a[res_id][y] == '-');
    if (type == 0) {
        return false;
    }
    if (type == 2) {
        if (choose_left) {
            a[res_id][x] = guess;
            return true;
        }
        a[res_id][y] = guess;
        return true;
    }
    if (a[res_id][x] == '-') {
        a[res_id][x] = guess;
        return true;
    }
    a[res_id][y] = guess;
    return true;
}

void book(char guess) {
    vector < int > row_id;
    if (count(2) || count(mid + 1)) {
        row_id.push_back(2);
        row_id.push_back(mid + 1);
    } else {
        for (int i = 1; i <= n; i++) {
            row_id.push_back(i);
        }
    }

    sort(row_id.begin(), row_id.end(), cmp);
    int res_id = row_id[0];
    bool choose_left = false;
    if (count_seat(1, 5) >= count_seat(7, 11)) {
        choose_left = true;
    }

    if (pick(res_id, 5, 7, choose_left, guess)) {
        return;
    }
    if (pick(res_id, 3, 9, choose_left, guess)) {
        return;
    }
    if (pick(res_id, 1, 11, choose_left, guess)) {
        return;
    }
    if (pick(res_id, 6, 6, choose_left, guess)) {
        return;
    }
    if (pick(res_id, 2, 10, choose_left, guess)) {
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int k;
    cin >> n >> k;
    mid = n / 2 + 2;
    n += 3;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        book('a' + i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }
}