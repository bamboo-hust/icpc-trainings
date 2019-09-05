#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    string L, R;
    cin >> L;
    cin >> R;
    string pad;
    int delta = R.size() - L.size();
    for (int i = 0; i < delta; ++i) pad += "0";
    L = pad + L;
    int prefix = 0;
    while (prefix < L.size() && L[prefix] == R[prefix]) {
        prefix += 1;
    }
    cout << L.size() - prefix << endl;
    return 0;
}