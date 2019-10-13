#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int M = 80;
const int BIT = 70;

char s[N][M];
int n, m;
int a[M], b[M];
bitset<BIT> base[BIT];
bitset<BIT> fixedPos;
bitset<BIT> val;
bitset<BIT> checkBase[BIT];
long long p3[BIT];

void addToBase(bitset<BIT> u) {
    for (int i = 0; i < BIT; i++) {
        if (u[i]) {
            if (!base[i][i]) {
                base[i] = u;
                return;
            }
            u ^= base[i];
        }
    }
}

bool check() {
    for (int i = 0; i < BIT; i++) checkBase[i].reset();
    for (int i = 0; i < BIT; i++) {
        if (!base[i][i]) continue;
        bitset<BIT> now = base[i];
        for (int j = 0; j < BIT; j++) {
            if (!fixedPos[j] || !now[j]) continue;
            if (checkBase[j][j]) now ^= checkBase[j];
            else {
                checkBase[j] = now;
                break;
            }
        }
    }
    bitset<BIT> cur;
    for (int i = 0; i < BIT; i++) {
        if (!fixedPos[i]) continue;
        if (cur[i] == val[i]) continue;
        if (!checkBase[i][i]) return 0;
        cur ^= checkBase[i];
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }
    p3[0] = 1;
    for (int i = 1; i < BIT; i++) {
        p3[i] = p3[i - 1] * 3;
    }

    for (int i = 0; i < n; i++) {
        bitset<BIT> cur;
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '0') continue;
            int id = 35 - b[j];
            id = id * 2 + (a[j] == -1);
            cur[id] = 1;
        }
        for (int j = 0; j < BIT; j += 2) {
            cur[j + 1] = cur[j + 1] ^ cur[j];
        }
        addToBase(cur);
    }
    long long res = 0;
    for (int i = 0; i < BIT; i += 2) {
        fixedPos[i] = fixedPos[i + 1] = 1;
        val[i] = val[i + 1] = 1;
        if (check()) {
            res += p3[35 - i / 2];
            continue;
        }
        fixedPos[i] = fixedPos[i + 1] = 0;
        val[i] = val[i + 1] = 0;

        fixedPos[i + 1] = 1;
        val[i + 1] = 0;
        if (check()) {
            continue;
        }
        fixedPos[i + 1] = 0;
        res -= p3[35 - i / 2];
    }  
    cout << res << endl;
    return 0;
}