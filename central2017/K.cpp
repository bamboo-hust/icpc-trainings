#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    if (n % 2 == 1 || m % 2 == 1) {
        puts("IMPOSSIBLE");
        return 0;
    } 
    n /= 2, m /= 2;
    if (m < n) {
        puts("IMPOSSIBLE");
        return 0;
    }
    long long b = m - n;
    long long a = n - b;
    if (a < 0 || b < 0) {
        puts("IMPOSSIBLE");
        return 0;
    }
    cout << b << " " << a << endl;
    return 0;
}