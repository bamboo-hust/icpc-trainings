#include <bits/stdc++.h>

using namespace std;

string s;

bool is_alpha(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*' || c == '%';
}

string remove_space(string s) {
    string res;
    for (char c : s) {
        if (c != ' ') {
            if (is_alpha(c)) {
                res += 'a';
            } else {
                res += c;
            }
        }
    }
    return res;

}

bool wrong() {
    for (int i = 1; i < s.size(); ++i) {
        if (is_alpha(s[i]) && is_alpha(s[i - 1])) return true;
        if (is_operator(s[i] && is_operator(s[i - 1]))) return true;
    }
    return false;
}

void show_error() {
    cout << "error" << endl;
    exit(0);
}

void show_improper() {
    cout << "improper" << endl;
    exit(0);
}

void check_error(int l, int r) {
    if (l > r) show_error();
    if (l == r) {
        if (!is_alpha(s[l])) show_error();
        return;
    }
    int deg = 0;
    int first_zero = -1;
    for (int i = l; i <= r; ++i) {
        if (s[i] == '(') {
            deg++;
        } else if (s[i] == ')') {
            deg--;
        }
        if (deg < 0) {
            show_error();
        }
        if (deg == 0 && is_operator(s[i])) {
            if (first_zero == -1) {
                first_zero = i;
            }
        }
    }
    if (deg != 0) show_error();
    if (first_zero == -1) {
        if (s[l] != '(' || s[r] != ')') show_error();
        check_error(l + 1, r - 1);
        return;
    }
    check_error(l, first_zero - 1);
    check_error(first_zero + 1, r);
}

void check_improper(int l, int r) {
    if (l + 2 == r && s.substr(l, 3) == "(a)") {
        if (l > 0 || r + 1 < s.size()) show_improper();
        return;
    }

    if (l == r) return;

    if (s[l] != '(' || s[r] != ')') show_improper();

    int deg = 0;
    int num_zero = 0;
    int first_zero = -1;
    for (int i = l + 1; i < r; ++i) {
        if (s[i] == '(') {
            deg++;
        } else if (s[i] == ')') {
            deg--;
        }
        if (deg < 0) {
            show_improper();
        }
        //cerr << i << ' ' << deg << endl;
        if (deg == 0 && is_operator(s[i])) {
            num_zero++;
            if (first_zero == -1) {
                first_zero = i;
            }
        }
    }
    if (deg < 0) show_improper();

    if (num_zero > 1) show_improper();
    check_improper(l + 1, first_zero - 1);
    check_improper(first_zero + 1, r - 1);
}

int main() {
    ios::sync_with_stdio(false);
    getline(cin, s);
    s = remove_space(s);

    s = "(" + s + ")";

    check_error(0, s.size() - 1);
    check_improper(0, s.size() - 1);

    cout << "proper" << endl;

    return 0;
}