//
// Created by lad on 9/23/19.
//
#include <bits/stdc++.h>

using namespace std;

int get_int() {
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    int ret = 0;
    while (isdigit(ch)) {
        ret = ret * 10 + ch - '0';
        ch = getchar();
    }
    return ret;
}

const int N = 1000010;

int n;
vector<int> a[N];
int id[N];

int main() {
    int n = get_int();
    for (int i = 0; i < n; i++) {
        int sz;
        cin >> sz;
        a[i].resize(sz);
        for (int &u : a[i]) u = get_int();
        id[i] = i;
    }
    sort(id, id + n, [](int u, int v) {
        return a[u] < a[v] || (a[u] == a[v] && u < v);
    });
    for (int i = 0; i < n; i++) cout << id[i] + 1 << '\n';
    return 0;
}