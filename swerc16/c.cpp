#include <bits/stdc++.h>

using namespace std;

int main() {
    int d, r, t;
    cin >> d >> r >> t;
    for (int i = 4; i <= 1000; i++) {
        int a = 0;
        for (int j = 4; j <= i; j++) {
            a += j;
        }
        int b = 0;
        for (int j = 3; j <= i - d; j++) {
            b += j;
        }
        if (a + b == r + t) {
            cout << r - a << endl;
            return 0;
        }
    }
    return 0;
}