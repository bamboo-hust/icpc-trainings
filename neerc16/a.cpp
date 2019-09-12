#include <bits/stdc++.h>

using namespace std;
#define f first
#define s second

int const N = 1e3 + 5;

string spaces(int x) {
    string res = "";
    for (int i = 1; i <= x; i++) {
        res += ' ';
    }
    return res;
}

bool check(string word) {
    if (word.size() == 1) {
        return false;
    }
    if (word[0] < 'A' || word[0] > 'Z') {
        return false;
    }
    for (int i = 1; i < word.size(); i++) {
        if (word[i] < 'a' || word[i] > 'z') {
            return false;
        }
    }
    return true;
}

bool is_char(char p) {
    if (p >= 'a' && p <= 'z') {
        return true;
    }
    if (p >= 'A' && p <= 'Z') {
        return true;
    }
    return false;
}

string abbreviation(string s) {
    vector < pair < string, string > > words;
    for (int i = 0; i < s.size();) {
        int pos = i;
        string curWord = "";
        while (pos < s.size() && is_char(s[pos])) {
            curWord += s[pos];
            pos++;
        }
        string curSign = "";
        while (pos < s.size() && !is_char(s[pos])) {
            curSign += s[pos];
            pos++;
        }
        words.push_back(make_pair(curWord, curSign));
        i = pos;
    }
    string ans = "";
    for (int i = 0; i < words.size();) {
        int pos = i;
        while (pos < words.size() && check(words[pos].f)) {
            if (words[pos].s != " ") {
                pos++;
                break;
            }
            pos++;
        }
        if (pos > i + 1) {
            //cout << "pos : " << i << " " << pos << endl;
            for (int j = i; j < pos; j++) {
                ans += words[j].f[0];
            }

            ans += " (";

            for (int j = i; j < pos; j++) {
                ans += words[j].f;
                if (j != pos - 1) {
                    ans += words[j].s;
                }
            }
            ans += ")";
            ans += words[pos - 1].s;
            i = pos;
        } else {
            //cout << i << " " << pos << endl;
            ans += words[i].f;
            ans += words[i].s;
            i = i + 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    freopen("abbreviation.in", "r", stdin);
    freopen("abbreviation.out", "w", stdout);
    string s;
    while (getline(cin, s)) {
        cout << abbreviation(s) << endl;
    }
}