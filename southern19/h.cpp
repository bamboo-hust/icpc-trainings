#include <bits/stdc++.h>

using namespace std;

const int N = 3003;

string a, b;

bool smaller(string a, string b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

string subtract(string a, string b) {
    if (smaller(a, b)) swap(a, b);
    while (b.size() < a.size()) b = '0' + b;
    int carry = 0;
    string c;
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] - b[i] - carry < 0) {
            c = char('0' + 10 + a[i] - b[i] - carry) + c;
            carry = 1;
        } else {
            c = char('0' + a[i] - b[i] - carry) + c;
            carry = 0;
        }
    }
    while (c.size() > 1 && c[0] == '0') {
        c.erase(c.begin());
    }
    return c;
}

int main() {
    cin >> a >> b;
    string max_a = a;
    string max_b = b;
    string min_b = b;
    string min_a = a;

    a = a + a;
    b = b + b;
    string res = "0";

    for (int i = 0; i < a.size() / 2; ++i) if (a[i] != '0') {
        max_a = max(max_a, a.substr(i, a.size() / 2));
        min_a = min(min_a, a.substr(i, a.size() / 2));
    }
    for (int i = 0; i < b.size() / 2; ++i) if (b[i] != '0') {
        min_b = min(min_b, b.substr(i, b.size() / 2));
        max_b = max(max_b, b.substr(i, b.size() / 2));
    }

    string cur = subtract(max_a, min_b);
    if (smaller(res, cur)) {
        res = cur;
    }
    cur = subtract(min_a, max_b);
    if (smaller(res, cur)) {
        res = cur;
    }
    cout << res << endl;
}