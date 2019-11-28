#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

int r, c;
int a[N][N], cache[N];
int nextCSteps[N];

int nextOneStep(int x, int y) {
    pair<int, int> res(0, 0);
    for (int delta = -1; delta <= 1; delta++) {
        int xx = (x + delta + r) % r;
        int val = a[xx][(y + 1) % c];
        res = max(res, {val, xx});
    }
    return res.second;
}

void moveNaive(int &x, int &y, int k) {
    while (k--) {
        // cout << x << ' ' << y << endl;
        x = nextOneStep(x, y);
        y = (y + 1) % c;
    }
}

void moveSmart(int &x, int &y, int k) {
    if (k < c) {
        moveNaive(x, y, k);
        return;
    }
    k -= (c - y);
    moveNaive(x, y, c - y);
    assert(y == 0);

    fill(cache, cache + r, -1);
    cache[x] = 0;
    int cnt = 0;
    while (k >= c) {
        cnt++;
        x = nextCSteps[x];
        k -= c;
        if (cache[x] != -1) {
            int circleLen = cnt - cache[x];
            k %= circleLen * c;
            break;
        }
        cache[x] = cnt;
    }
    while (k >= c) {
        x = nextCSteps[x];
        k -= c;
    }
    // cout << "smart " << x << ' ' << y << ' ' << k << endl;
    moveNaive(x, y, k);
}

void init() {
    for (int i = 0; i < r; i++) {
        int x = i, y = 0;
        moveNaive(x, y, c);
        assert(!y);
        nextCSteps[i] = x;
    }
}

bool inside(int x, int ll, int rr) {
    while (x < ll) x += r;
    return x <= rr;
}

void update(int x, int y) {
    int lastId = x;
    int lastY = y;
    moveNaive(lastId, lastY, c - y);
    cout << "update " << x << ' ' << y << ' ' << lastId << endl;
    assert(lastY == 0);
    int low = x, high = x;
    for (int i = y - 1; i >= 0; i--) {
        int ll = low, hh = high;
        if (hh - ll + 1 >= 3) {
            if (!inside(nextOneStep(low % r, i), ll, hh)) low++;
            else if (inside(nextOneStep((low - 1 + r) % r, i), ll, hh)) low--;

            if (!inside(nextOneStep(high % r, i), ll, hh)) high--;
            else if (inside(nextOneStep((high + 1) % r, i), ll, hh)) high++;
        } else {
            low = ll - 1; high = rr + 1;
            
        }
        
        cout << "change " << i << ' ' << low << ' ' << high << endl;        
        if (low > high) return;
        if (high - low + 1 >= r) {
            for (int i = 0; i < r; i++) nextCSteps[i] = lastId;
            return;
        }
        if (low < 0) {
            low += r; high += r;
        }
        if (low >= r) {
            low -= r; high -= r;  
        }
    }
    for (int i = low; i <= high; i++) nextCSteps[i % r] = lastId;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> c;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> a[i][j];
    init();

    int m;
    cin >> m;
    int curX = 0, curY = 0;
    while (m--) {
        string op;
        cin >> op;
        if (op == "move") {
            int k; cin >> k;
            // for (int i = 0; i < r; i++) cout << nextCSteps[i] << ' ';
            //     cout << endl;
            moveSmart(curX, curY, k);
            cout << curX + 1 << ' ' << curY + 1 << '\n';
        } else {
            int x, y, e; cin >> x >> y >> e;
            x--, y--;
            a[x][y] = e;
            // for (int i = 0; i < r; i++) {
            //     for (int j = 0; j < c; j++) cout << setw(9) << a[i][j] << ' ';
            //         cout << endl;
            // }
            update((x - 1 + r) % r, (y - 1 + c) % c);
            update((x + 0 + r) % r, (y - 1 + c) % c);
            update((x + 1 + r) % r, (y - 1 + c) % c);
        }   
    }
    return 0;
}