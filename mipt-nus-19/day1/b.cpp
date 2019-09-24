#include <bits/stdc++.h>

using namespace std;

int main() {
    int s, b, n;
    cin >> s >> b >> n;
    int res = 0;
    vector<bool> can_go(n);
    for (int i = 1; i <= b; ++i) {
        string tour; cin >> tour;
        if (tour[s - 1] == '1') {
            for (int j = 0; j < tour.size(); ++j) {
                if (tour[j] == '1' && j != s - 1) {
                    can_go[j] = true;
                }
            }
        }
    }

    cout << accumulate(begin(can_go), end(can_go), 0) << endl;
}