#include <bits/stdc++.h>

using namespace std;

const int N = 10;

int a[N][N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string op;
    cin >> op;
    if (op == "Mia") {
        int tc;
        cin >> tc;
        while (tc--) {
            int sumXor = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    cin >> a[i][j];
                    if (a[i][j]) sumXor ^= (i << 3 | j);
                }
            }
            int res;
            cin >> res;
            res--;
            sumXor ^= res;
            a[sumXor >> 3][sumXor & 7] ^= 1;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    cout << a[i][j] << ' ';
                }
                cout << '\n';
            } 
            cout << "---\n";
        }
    } else {
        int tc;
        cin >> tc;
        while (tc--) {
            int sumXor = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    cin >> a[i][j];
                    if (a[i][j]) sumXor ^= (i << 3 | j);
                }
            }
            cout << sumXor + 1 << '\n';
            string foo;
            cin >> foo;
        }

    }
    return 0;
}