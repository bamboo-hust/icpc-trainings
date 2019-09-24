#include <bits/stdc++.h>

using namespace std;

int main() {
    int64_t S, D;
    cin >> S >> D;
    int64_t res = 1;
    while (S % D) {
        D = D - S % D;
        ++res;
    }
    cout << res << endl;
}