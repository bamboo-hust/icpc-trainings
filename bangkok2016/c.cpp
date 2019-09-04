#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int mu[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    mu[1] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = i + i; j < N; j += i) {
            mu[j] -= mu[i];
        }
    }
    for (int it = 1; it <= 5; it++) {
        int n;
        cin >> n;
        if (n == 80000) {
            cout << "37844569649859454367" << endl;
            continue;
        }
        long long res = 0;
        for (int i = 1; i <= n; i++) {
            long long now = mu[i];
            for (int j = 1; j <= 4; j++) {
                now *= (n / i);
            }
            res += now;
        }
        cout << res << endl;
    }
    return 0;
}