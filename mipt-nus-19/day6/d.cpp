#include <bits/stdc++.h>
#define EPS 1e-9
#define double long double

using namespace std;

const double PI = acos(-1);

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    Point() { x = y = 0; }
    Point(double x, double y): x(x), y(y) {}

    Point operator + (const Point &a) const { return Point(x + a.x, y + a.y); }
    Point operator - (const Point &a) const { return Point(x - a.x, y - a.y); }
    Point operator * (const double k) const { return Point(x * k, y * k); }
    Point operator / (const double k) const { return Point(x / k, y / k); }

    double norm() { return x * x + y * y; }
    double len() { return sqrt(norm()); }
    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

struct Circle : Point {
    double r;
    Circle(Point p, double r): Point(p), r(r) {}

    bool contains(const Circle &o) {
        return (o - *this).len() < r - o.r;
    }
};

bool has_common_point(Circle u, Circle v) {
    return (cmp((u - v).len(), u.r + v.r) <= 0);
}

pair<double, double> intersection_angle_range(Circle u, Circle v) {
    assert(has_common_point(u, v));
    double d = (u - v).len();
    double alpha = acos((u.r * u.r + d * d - v.r * v.r) / 2.0 / u.r / d);
    double base = atan2(v.y - u.y, v.x - u.x);
    return make_pair(base - alpha, base + alpha);
}

void normalize_angle(double &a) {
    while (a > 2 * PI) a -= 2 * PI;
    while (a < 0) a += 2 * PI;
}

vector< pair<double, double> > get_ranges(pair<double, double> range) {
    normalize_angle(range.first);
    normalize_angle(range.second);
    vector< pair<double, double> > res;
    if (range.first > range.second) {
        res.emplace_back(range.first, 2 * PI);
        res.emplace_back(0, range.second);
    } else {
        res.push_back(range);
    }
    return res;
}

bool ranges_intersect(pair<double, double> a, pair<double, double> b) {
    return !(a.second < b.first || b.second < a.first);
}

bool has_common_point(vector<Circle> C) {
    for (int i = 0; i < C.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (!has_common_point(C[i], C[j])) {
                return false;
            }
        }
    }

    sort(begin(C), end(C), [](const Circle &a, const Circle &b) {
        return a.r < b.r;
    });
    if (C.back().contains(C[0]) || C.back().contains(C[1])) return true;

    pair<double, double> a = intersection_angle_range(C[0], C[1]);
    pair<double, double> b = intersection_angle_range(C[0], C[2]);
    vector< pair<double, double> > aa = get_ranges(a);
    vector< pair<double, double> > bb = get_ranges(b);
    for (auto p : aa) for (auto q : bb) {
        if (ranges_intersect(p, q)) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<Point> p(3);
    for (int i = 0; i < 3; ++i) cin >> p[i].x >> p[i].y;
    int n;
    cin >> n;
    vector<double> r(n);
    for (int i = 0; i < n; ++i) cin >> r[i];
    int num_mask = 1;
    for (int i = 1; i < n; ++i) num_mask *= 3;
    //cerr << "num_mask " << num_mask << endl;
    for (int i = 0; i < n; ++i) {
        vector<int> role(n, -1);
        for (int mask = 0; mask < num_mask; ++mask) {
            //cerr << "mask " << mask << endl;
            int cur = mask;
            for (int j = 0; j < n; ++j) if (i != j) {
                role[j] = cur % 3;
                cur /= 3;
            }
            vector<Circle> C;
            for (int j = 0; j < 3; ++j) {
                C.push_back(Circle(p[j], r[i]));
            }
            for (int j = 0; j < n; ++j) {
                if (role[j] >= 0) {
                    C[role[j]].r += r[j] * 2;
                }
            }
            if (has_common_point(C)) {
                cout << "possible" << endl;
                return 0;
            }
        }
    }
    cout << "impossible" << endl;
}