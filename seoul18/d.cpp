#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string u;
        cin >> u;
        if (u.back() == 'a') {
            cout << u.substr(0, u.size() - 1) << "as" << endl;
        } else if (u.back() == 'i' || u.back() == 'y') {
            cout << u.substr(0, u.size() - 1) << "ios" << endl;
        } else if (u.back() == 'l') {
            cout << u.substr(0, u.size() - 1) << "les" << endl;
        } else if (u.back() == 'n') {
            cout << u.substr(0, u.size() - 1) << "anes" << endl;
        } else if (u.back() == 'e' && u[u.size() - 2] == 'n') {
            cout << u.substr(0, u.size() - 2) << "anes" << endl;
        } else if (u.back() == 'o') {
            cout << u.substr(0, u.size() - 1) << "os" << endl;
        } else if (u.back() == 'r') {
            cout << u.substr(0, u.size() - 1) << "res" << endl;
        } else if (u.back() == 't') {
            cout << u.substr(0, u.size() - 1) << "tas" << endl;
        }else if (u.back() == 'u') {
            cout << u.substr(0, u.size() - 1) << "us" << endl;
        } else if (u.back() == 'v') {
            cout << u.substr(0, u.size() - 1) << "ves" << endl;
        } else if (u.back() == 'w') {
            cout << u.substr(0, u.size() - 1) << "was" << endl;
        } else {
            cout << u << "us" << endl;
        }
     }
    return 0;
}