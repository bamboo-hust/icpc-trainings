#include <bits/stdc++.h>

using namespace std;

string digit[] = {"xxxxx"
                  "x...x"
                  "x...x"
                  "x...x"
                  "x...x"
                  "x...x"
                  "xxxxx",

                  "....x"
                  "....x"
                  "....x"
                  "....x"
                  "....x"
                  "....x"
                  "....x",

                  "xxxxx"
                  "....x"
                  "....x"
                  "xxxxx"
                  "x...."
                  "x...."
                  "xxxxx",

                  "xxxxx"
                  "....x"
                  "....x"
                  "xxxxx"
                  "....x"
                  "....x"
                  "xxxxx",

                  "x...x"
                  "x...x"
                  "x...x"
                  "xxxxx"
                  "....x"
                  "....x"
                  "....x",

                  "xxxxx"
                  "x...."
                  "x...."
                  "xxxxx"
                  "....x"
                  "....x"
                  "xxxxx",

                  "xxxxx"
                  "x...."
                  "x...."
                  "xxxxx"
                  "x...x"
                  "x...x"
                  "xxxxx",

                  "xxxxx"
                  "....x"
                  "....x"
                  "....x"
                  "....x"
                  "....x"
                  "....x",

                  "xxxxx"
                  "x...x"
                  "x...x"
                  "xxxxx"
                  "x...x"
                  "x...x"
                  "xxxxx",

                  "xxxxx"
                  "x...x"
                  "x...x"
                  "xxxxx"
                  "....x"
                  "....x"
                  "xxxxx",

                  "....."
                  "..x.."
                  "..x.."
                  "xxxxx"
                  "..x.."
                  "..x.."
                  "....."};


map < string, int > id;
vector < string > a;

void print(char p) {
    int x = p - '0';
    string d = digit[x];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            int pos = i * 5 + j;
            a[i] = a[i] + d[pos];
        }
    }
}

int main() {
    for (int i = 0; i <= 10; i++) {
        id[digit[i]] = i;
    }
    string s;
    while (cin >> s) {
        a.push_back(s);
    }

    int n = a.size();
    int m = a[0].size();

    int ans = 0;
    int number = 0;
    for (int p = 0; p < m; p += 6) {
        string cur = "";
        for (int i = 0; i < n; i++) {
            for (int j = p; j < p + 5; j++) {
                cur += a[i][j];
            }
        }
        int x = id[cur];
        if (x == 10) {
            ans += number;
            number = 0;
        } else {
            number = number * 10 + x;
        }
    }
    ans += number;
    string res = "";
    while (ans) {
        res += '0' + (ans % 10);
        ans /= 10;
    }

    reverse(res.begin(), res.end());
    for (int i = 0; i < n; i++) {
        a[i].clear();
    }
    for (int i = 0; i < res.size(); i++) {
        char p = res[i];
        print(p);
        if (i != (int)res.size() - 1) {
            for (int i = 0; i < n; i++) {
                a[i] = a[i] + ".";
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
}