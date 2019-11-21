#include <bits/stdc++.h>

using namespace std;

int const N = 1e3 + 5;

int n;
string s[N];



int get_type(char p) {
    if (p >= 'A' && p <= 'Z') {
        return 2;
    }
    if (p >= 'a' && p <= 'z') {
        return 2;
    }
    return 1;
}

vector < pair < int, string > > get_items(string p) {
    vector < pair < int, string > > res;
    for (int i = 0; i < p.size();) {
        if (get_type(p[i]) == 2) {
            string empty = "";
            res.push_back(make_pair(2, empty + p[i]));
            i++;
            continue;
        }
        int pos = i;
        while (pos < p.size() && get_type(p[pos]) == 1) {
            pos++;
        }
        res.push_back(make_pair(1, p.substr(i, pos - i)));
        i = pos;
    }
    return res;
}

int get_int(string p) {
    int res = 0;
    for (int i = 0; i < p.size(); i++) {
        res = res * 10 + (p[i] - '0');
    }
    return res;
}


int smaller(pair < int, string > p, pair < int, string > q) {
    if (p.first != q.first) {
        return p.first < q.first ? -1 : 1;
    }
    if (p.first == 1) {
        if (get_int(p.second) != get_int(q.second)) {
            return get_int(p.second) < get_int(q.second) ? -1 : 1;
        }
        return 0;
    }
    if (p.second != q.second) {
        return p.second < q.second ? -1 : 1;
    }
    return 0;
}

int compare(string p, string q) {
    vector < pair < int, string > > item_p = get_items(p);
    vector < pair < int, string > > item_q = get_items(q);
    for (int i = 0; i < min(item_p.size(), item_q.size()); i++) {
        int cur = smaller(item_p[i], item_q[i]);
        if (cur) {
            return cur;
        }
    }
    return p.size() < q.size() ? -1 : 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n + 1; i++) {
        cin >> s[i];
    }
    for (int i = 2; i <= n + 1; i++) {
        cout << (compare(s[i], s[1]) == -1 ? '-' : '+') << endl;
    }
}