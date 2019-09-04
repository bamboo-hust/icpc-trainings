#include <bits/stdc++.h>

using namespace std;

int get(long long n) {
    //cerr << n << endl;
    if (n == 1) return 0;
    int p = 0;
    while ((1LL << p) <= n) p += 1;
    p -= 1;
    if ((1LL << p) == n) p -= 1;
    return !get(n - (1LL << p));
}

int main() {
    long long n; cin >> n;
    cout << get(n + 1);
    cout << get(n + 2);
    cout << get(n + 3);
    /*
    cerr << endl;
    for (int i = 1; i <= 10; ++i) cerr << get(i) << endl;
    */
    return 0;
}