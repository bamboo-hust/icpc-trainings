#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;

inline int cmp(double a, double b) {
    return a + EPS < b ? -1 : (a > b + EPS ? 1 : 0);
}

struct Point {
    double x, y;
    Point() { x = y = 0.0; }
    Point(double x, double y): x(x), y(y) {}

    Point operator + (const Point &a) const { return Point(x + a.x, y + a.y); }
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }

    double operator % (const Point &a) const { return x * a.y - y * a.x; }

    bool operator < (const Point &a) const {
        if (cmp(x, a.x)) return cmp(x, a.x) < 0;
        return y < a.y;
    }

    double norm() { return x * x + y * y; }
    double len() { return sqrt(norm()); }
};

double dist(Point A, Point B) {
    return (A - B).len();
}

bool ccw(Point a, Point b, Point c) {
    return (b - a) % (c - a) >= 0;
}

struct Line {
    double a, b, c;
    Point A, B;

    Line(double a, double b, double c): a(a), b(b), c(c) {}
    Line(Point A, Point B): A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    double f(Point A) {
        return a * A.x + b * A.y + c;
    }

    bool contains(Point p) {
        return cmp(dist(A, p) + dist(B, p), dist(A, B)) == 0;
    }
};

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b * l2.c - l2.b * l1.c;
    double dy = l1.c * l2.a - l2.c * l1.a;
    double d = l1.a * l2.b - l2.a * l1.b;
    p = Point(dx / d, dy / d);
    return true;
}

using Polygon = vector<Point>;

Polygon convex_hull(Polygon a) {
    Polygon h;
    sort(begin(a), end(a));
    for (int i = 0; i < a.size(); ++i) {
        while (h.size() > 1 && ccw(h[h.size() - 2], h[h.size() - 1], a[i])) h.pop_back();
        h.push_back(a[i]);
    }
    for (int i = (int)a.size() - 2, t = h.size(); i >= 0; --i) {
        while (h.size() > t && ccw(h[h.size() - 2], h[h.size() - 1], a[i])) h.pop_back();
        h.push_back(a[i]);
    }
    h.pop_back();
    return h;
}

double area(Polygon a) {
    a = convex_hull(a);
//    cerr << "area\n";
//    for (auto it : a) {
//        cerr << it.x << ' ' << it.y << endl;
//    }
//    cerr << endl;

    double res = 0;
    for (int i = 0; i < a.size(); ++i) {
        res += a[i] % a[(i + 1) % a.size()];
    }
    return abs(res) / 2;
}

Polygon square(4);

vector<Point> cuts(Line L) {
    vector<Point> res;
    for (int i = 0; i < 4; ++i) {
        Point p;
        Line cur(square[i], square[(i + 1) % 4]);
        if (areIntersect(L, cur, p)) {
            if (cur.contains(p)) {
                res.push_back(p);
            }
        }
    }
    return res;
}

double calc_south() {
    Polygon a = cuts(Line(0, 1, 0.5));
    for (int i = 0; i < square.size(); ++i) {
        if (square[i].y <= -0.5) a.push_back(square[i]);
    }
    return area(a);
}

double calc_east() {
    Polygon a = cuts(Line(1, 0, -0.5));
    for (int i = 0; i < square.size(); ++i) {
        if (square[i].x >= 0.5) a.push_back(square[i]);
    }
    return area(a);
}

double calc_west() {
    Polygon a = cuts(Line(1, 0, 0.5));
    for (int i = 0; i < square.size(); ++i) {
        if (square[i].x <= -0.5) a.push_back(square[i]);
    }
    return area(a);
}

double calc_north() {
    Polygon a = cuts(Line(0, 1, -0.5));
    for (int i = 0; i < square.size(); ++i) {
        if (square[i].y >= 0.5) a.push_back(square[i]);
    }
    return area(a);
}

int main() {
    for (int i = 0; i < 4; ++i) {
        cin >> square[i].x >> square[i].y;
    }

    double res = 5 * 4 * 5 * 5; // see 5 dots

    res += 1 * 5 * calc_south();
    res += 4 * 5 * calc_west();
    res += 3 * 5 * calc_east();
    res += 6 * 5 * calc_north();

    res /= 5 * 5 * 5 - 1;

    cout << setprecision(10) << fixed << res << endl;
}