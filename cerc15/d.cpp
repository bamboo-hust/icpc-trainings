#include <bits/stdc++.h>

using namespace std;

int const MOD = 1e9 + 7;


int pow_mod(int x, int y) {
    if (y < 0) {
        return 0;
    }
    if (y == 0) {
        return 1;
    }
    long long u = pow_mod(x, y / 2);
    u = u * u % MOD;
    if (y % 2) {
        u = u * x % MOD;
    }
    return u;
}

int main() {
    int n, m, sum = 0;
    cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        char p;
        cin >> p;
        int x = p - '0';
        sum = (sum * 10 + x) % m;
        if (sum == 0) {
            cnt++;
        }
    }

    if (sum) {
        cnt = 0;
    }

    cout << pow_mod(2, cnt - 1) << endl;

}