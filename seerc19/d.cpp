#include <bits/stdc++.h>

using namespace std;
int const N = 30;
int cnt[N];


bool cmp(char p, char q) {
    if (cnt[p - 'a'] != cnt[q - 'a']) {
        return cnt[p - 'a'] > cnt[q - 'a'];
    }
    return p < q;
}

int main() {
    string s; cin >> s;
    int n = s.size();
    int maxs = 0;
    for (int i = 0; i < s.size(); i++) {
        cnt[s[i] - 'a']++;
        maxs = max(maxs, cnt[s[i] - 'a']);
    }

    sort(s.begin(), s.end(), cmp);
    if (maxs <= n / 2) {
        cout << "YES" << endl;
        cout << s << endl;
        return 0;
    }
    if (n - maxs == 2 && s[n - 1] != s[n - 2]) {
        swap(s[n / 2], s[n - 2]);
        cout << "YES" << endl;
        cout << s << endl;
        return 0;
    }
    if (n - maxs <= 2) {
        cout << "NO" << endl;
        return 0;
    }

    //cout << n / 2 + 1 << " " << n - 2 << endl;
    swap(s[n / 2], s[maxs]);
    cout << "YES" << endl;
    cout << s << endl;

}
