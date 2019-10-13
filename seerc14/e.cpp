#include <bits/stdc++.h>

using namespace std;

int const N =  1e5 + 5;
int const MAX = 1e9 + 7;

struct Point
{
    int x, y;
    Point(){};
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    };
};

double dis(Point p, Point q) {
    double hx = p.x - q.x;
    double hy = p.y - q.y;
    return sqrt(hx * hx + hy * hy);
}


int main() {
    ios_base::sync_with_stdio(0);
    freopen("e.in", "r", stdin);
    int n;
    cin >> n;
    int max_x, min_x, max_y, min_y, max_plus_xy, min_plus_xy, min_sub_xy, max_sub_xy;
    max_x = max_y = max_plus_xy = max_sub_xy = -MAX;
    min_x = min_y = min_plus_xy = min_sub_xy = MAX;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        max_x = max(max_x, x + 1);
        min_x = min(min_x, x - 1);
        max_y = max(max_y, y + 1);
        min_y = min(min_y, y - 1);
        max_plus_xy = max(max_plus_xy, x + y + 1);
        min_plus_xy = min(min_plus_xy, x + y - 1);
        max_sub_xy = max(max_sub_xy, x - y + 1);
        min_sub_xy = min(min_sub_xy, x - y - 1);
    }


    vector < Point > a;
    a.push_back(Point(max_plus_xy - max_y, max_y));
    a.push_back(Point(min_sub_xy + max_y, max_y));
    a.push_back(Point(min_x, min_x - min_sub_xy));
    a.push_back(Point(min_x, min_plus_xy - min_x));
    a.push_back(Point(min_plus_xy - min_y, min_y));
    a.push_back(Point(max_sub_xy + min_y, min_y));
    a.push_back(Point(max_x, max_x - max_sub_xy));
    a.push_back(Point(max_x, max_plus_xy - max_x));
    a.push_back(a[0]);
    // for (int i = 0; i < 8; i++) {
    //     cout << a[i].x << " " << a[i].y << endl;
    // }
    double ans = 0;
    for (int i = 0; i < 8; i++) {
        ans += dis(a[i], a[i + 1]);
    }
    printf("%.6f\n", ans);
}