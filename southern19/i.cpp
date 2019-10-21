#include <bits/stdc++.h>

using namespace std;

struct Color
{
    long long r, g, b;
    Color(){};
    Color(int _r, int _g, int _b) {
        r = _r; g = _g; b = _b;
    }
};

long long r, g, b;

Color calc(long long n) {
    if (n == 1) {
        return Color(r, g, b);
    }

    Color u = calc((n + 1) / 3);
    if (n % 3 == 2) {
        return Color(u.r + u.g, u.b, u.g);
    }

    if (n % 3 == 0) {
        return Color(u.b, u.g + u.b, u.r);
    }
    return Color(u.g, u.r, u.b + u.r);

}


int main() {
    long long n;
    cin >> r >> g >> b >> n;
    Color ans = calc(n);
    cout << ans.r << " " << ans.g << " " << ans.b << endl;
}