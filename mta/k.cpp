#include <bits/stdc++.h>

using namespace std;

int main() {
    int64_t n;
    cin >> n;
    int64_t res = 1;
    for (int64_t a = 1; a * a <= n; ++a) {
        if (n % (a * a) == 0) {
            res = a * a;
        }
    }
    cout << res << endl;
}