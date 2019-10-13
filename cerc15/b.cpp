#include <bits/stdc++.h>

using namespace std;

int const N = 1e6 + 5;

int pre[N], len[N];
string s;

int solve(int max_len) {
    int pos = 0, ans = 0;
    while (pos < s.size()) {
        ans += len[pos];
        if (pos) {
            ans++;
        }
        if (pos + max_len >= s.size()) {
            break;
        }
        char nxt = s[pos + max_len];
        if (nxt == ' ') {
            pos = pos + max_len + 1;
        } else {
            pos = pre[pos + max_len];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    getline(cin, s);
    for (int i = 0; i < N; i++) {
        pre[i] = i;
    }
    for (int i = 0; i < s.size();) {
        int pos = i;
        while (pos < s.size() && s[pos] != ' ') {
            pos++;
        }

        for (int j = i; j < pos; j++) {
            pre[j] = i;
        }
        len[i] = pos - i;
        i = pos + 1;
    }

    int a, b;
    cin >> a >> b;
    for (int max_len = a; max_len <= b; max_len++) {
        cout << solve(max_len) << '\n';
    }
}