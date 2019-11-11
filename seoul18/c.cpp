#include <bits/stdc++.h>

using namespace std;

const int N = 1024;

double a[N];
int n;

double calc() {
    double res = a[0] + a[n - 1];
    for (int i = 1; i < n; ++i) {
        res += 2.0 * sqrt(a[i] * a[i - 1]);
    }
    return res;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    double res = calc();
    while (true) {
        bool changed = false;
        for (int i = 1; i < n; ++i) for (int j = 0; j < i; ++j){
            swap(a[i], a[j]);
            double cur = calc();
            if (res > cur) {
                res = cur;
                changed = true;
            } else {
                swap(a[i], a[j]);
            }
        }
        if (!changed) break;
    }
    cout << setprecision(6) << fixed << res << endl;
}