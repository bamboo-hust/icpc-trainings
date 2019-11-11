#include <bits/stdc++.h>

using namespace std;

int const N = 105 + 5;

bool dp[N][2][N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    int n, dot1, g1, g2, g3;
    cin >> n >> dot1 >> g1 >> g2 >> g3;
    cin >> s;
    int pos1 = 0;
    while (pos1 < s.size() && s[pos1] == '#') {
        pos1++;
    }
    int pos2 = s.size() - 1;
    //cout << "pos2 : " << pos2 << endl;
    while (pos2 >= 0 && s[pos2] == '#') {
        pos2--;
    }

    if (pos1 == s.size()) {
        cout << 0 << endl;
        return 0;
    }
    s = s.substr(pos1, pos2 - pos1 + 1);

    s = '#' + s + '#';
  //  cout << "S : " << s << endl;
    vector < int > pos;
    int numdot = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#') {
            pos.push_back(i);
        }
        numdot += s[i] == '.';
    }

    dp[0][0][0][0] = 1;
    int last = (int)pos.size() - 1;
    for (int i = 0; i < last; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k < pos.size(); k++) {
                for (int l = 0; l < pos.size(); l++) {
                    if (dp[i][j][k][l] == 0) {
                        continue;
                    }
                    //cout << i << " " << j << " " << k << " " << l << endl;
                    int size = pos[i + 1] - pos[i] - 1;
                    if (size == 0) {
                        if (j == 0) {
                            dp[i + 1][j][k + (j == 1)][l + size % 2] = 1;
                        }
                        continue;
                    }
                    if (size == 1) {
                        if (j == 0) {
                            dp[i + 1][j][k + (j == 1)][l + size % 2] = 1;
                        }
                        dp[i + 1][j ^ 1][k + (j == 0)][l + (size - 1) % 2] = 1;
                        continue;
                    }
                    dp[i + 1][j][k + (j == 1)][l + (size % 2)] = 1;
                    dp[i + 1][j ^ 1][k + (j == 0)][l + (size - 1) % 2] = 1;
                }
            }
        }
    }

    int ans = 0;
    for (int k = 0; k < pos.size(); k++) {
        for (int l = 0; l < pos.size(); l++) {
            if (dp[last][0][k][l] == 0) {
                continue;
            }
            //cout << k << " " << l << endl;
            int t3 = k;
            int t2 = (numdot - 2 * k - l) / 2;
            int t1 = min(l, dot1);
            int rest = dot1 - t1;

            if (2 * g1 > g2) {
                int change = min(rest / 2, t2);
                t1 += change * 2;
                t2 -= change;
                rest -= change * 2;
            }

            if (rest && g1 > g2 && t2) {
                t2--;
                t1++;
            }

            ans = max(ans, t1 * g1 + t2 * g2 + t3 * g3);
        }
    }

    cout << ans << endl;


    return 0;
}