#include <bits/stdc++.h>

using namespace std;


int const N = (1 << 16);
int const MIN = (1 << 15);

int sum[N + 1];


int convert(string s) {
    int sign;
    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1, s.size() - 1);
    } else {
        sign = 1;
    }
    int res = 0;
    for (int i = 0; i < s.size(); i++) {
        res = res * 10 + (s[i] - '0');
    }
    return res * sign;
}

void add_segment(string s) {
    vector < string > words;
    for (int i = 0; i < s.size();) {
        int pos = i;
        while (pos < s.size() && s[pos] != ' ') {
            pos++;
        }
        words.push_back(s.substr(i, pos - i));
        i = pos + 1;
    }

    if (words[1] == "<=") {
        int r = convert(words[2]);
        sum[0]++;
        sum[r + 1 + MIN]--;
        return;
    }
    int l = convert(words[2]);
    int r = MIN - 1;
    if (words.size() >= 7) {
        r = convert(words[6]);
        //cout << "l r" << l << " " << r << endl;
    }
    //cout << convert(words[6]) << endl;
    if (l > r) {
        return;
    }

    sum[l + MIN]++;
    sum[r + MIN + 1]--;

}

int main() {
    freopen("hard.in", "r", stdin);
    //freopen("hard.out", "w", stdout);
    string s;
    while (getline(cin, s)) {
        //cout << s << endl;
        add_segment(s);
    }
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        sum[i] += sum[i - 1];
        cnt += sum[i] != 0;
    }
    if (cnt == 0) {
        cout << "false" << endl;
        return 0;
    }
    if (cnt == N) {
        cout << "true" << endl;
        return 0;
    }
    vector < pair < int, int > > ans;
    for (int i = 0; i < N;) {
        if (sum[i] == 0) {
            i++;
            continue;
        }
        int pos = i;
        while (pos < N && sum[pos]) {
            pos++;
        }
        ans.push_back(make_pair(i, pos - 1));
        i = pos;
    }

    for (int i = 0; i < ans.size(); i++) {
        pair < int, int > p = ans[i];
        if (p.first == 0) {
            cout << "x <= " << p.second - MIN;
            if (i != ans.size() - 1) {
                cout << " ||" << endl;
            }
            continue;
        }
        if (p.second == N - 1) {
            cout << "x >= " << p.first - MIN;
            if (i != ans.size() - 1) {
                cout << " ||" << endl;
            }
            continue;
        }
        cout << "x >= " << p.first - MIN << " && " << "x <= " << p.second - MIN;
        if (i != ans.size() - 1) {
            cout << " ||" << endl;
        }
    }
    cout << endl;
}