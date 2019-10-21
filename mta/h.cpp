#include <bits/stdc++.h>

using namespace std;

const int N = 1000;
const int INF = 1e9;

int dp[N];

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = "Q" + s;
    dp[0] = 0;

    map<string, int> m;
    m["M"] = 1000;
    m["MM"] = 2000;
    m["MMM"] = 3000;

    m["C"] = 100;
    m["CC"] = 200;
    m["CCC"] = 300;
    m["CD"] = 400;
    m["D"] = 500;
    m["DC"] = 600;
    m["DCC"] = 700;
    m["DCCC"] = 800;
    m["CM"] = 900;


    m["X"] = 10;
    m["XX"] = 20;
    m["XXX"] = 30;
    m["XL"] = 40;
    m["L"] = 50;
    m["LX"] = 60;
    m["LXX"] = 70;
    m["LXXX"] = 80;
    m["XC"] = 90;

    m["I"] = 1;
    m["II"] = 2;
    m["III"] = 3;
    m["IV"] = 4;
    m["V"] = 5;
    m["VI"] = 6;
    m["VII"] = 7;
    m["VIII"] = 8;
    m["IX"] = 9;

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        for (int j = i; j >= max(1, i - 3); j--) {
            string foo = s.substr(j, i - j + 1);
            if (m.count(foo)) {
                dp[i] = min(dp[i], dp[j - 1] + m[foo]);
            }
        }
    }
    cout << dp[n] << endl;
    return 0;
}