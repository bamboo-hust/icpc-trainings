#include <bits/stdc++.h>

using namespace std;

int const N = 1e5 + 5;

int a[N], n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 2; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << a[1] << endl;
    return 0;
}