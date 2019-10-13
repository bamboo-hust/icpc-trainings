#include <bits/stdc++.h>

using namespace std;

int const NN = 20;


set < string > set_string;

void init(string s) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        string cur = "";
        for (int j = i; j < min(i + NN, n); j++) {
            cur = cur + s[j];
            set_string.insert(cur);
        }
    }
}


string convert(int mask, int len) {
    string cur = "";
    for (int i = 1; i <= len; i++) {
        int val = (mask % 2);
        cur = cur + (char)('0' + val);
        mask /= 2;
    }
    reverse(cur.begin(), cur.end());
    return cur;
}

int main() {
    ios_base::sync_with_stdio(0);
    string s;
    for (int i = 1; i <= 2; i++) {
        cin >> s;
        init(s);
    }

    for (int len = 1; len <= NN; len++) {
        for (int mask = 0; mask < (1 << len); mask++) {
            string cur = convert(mask, len);
            if (set_string.find(cur) == set_string.end()) {
                cout << cur << endl;
                return 0;
            }
        }
    }

}