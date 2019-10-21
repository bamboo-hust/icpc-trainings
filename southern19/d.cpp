#include <bits/stdc++.h>
#define int long long
#define double long double

using namespace std;

#define EPS 1e-6

const double PI = acos(-1);

inline int cmp(double a, double b) { return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0); }
struct Point {
    double x, y;
    Point() { x = y = 0.0; }
    Point(double x, double y) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (double k) const { return Point(x*k, y*k); }
    Point operator / (double k) const { return Point(x/k, y/k); }

    double operator * (const Point& a) const { return x*a.x + y*a.y; } // dot product
    double operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product
    double norm() { return x*x + y*y; }
    double len() { return sqrt(norm()); } // hypot(x, y);
    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};
double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}
double directed_angle(Point a, Point o, Point b) { // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
}
// Distance from p to Line ab (closest Point --> c)
double distToLine(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p-c).len();
}
// Distance from p to segment ab (closest Point --> c)
double distToLineSegment(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    if (u < 0.0) {
        c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (u > 1.0) {
        c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b, c);
}
// NOTE: WILL NOT WORK WHEN a = b = 0.
struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double a, double b, double c) : a(a), b(b), c(c) {} 

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
    Line(Point P, double m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point A) {
        return a*A.x + b*A.y + c;
    }
};

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1 ,l2) && cmp(l1.c*l2.a, l2.c*l1.a) == 0
                && cmp(l1.c*l2.b, l1.b*l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}
void closestPoint(Line l, Point p, Point &ans) {
    if (fabs(l.b) < EPS) {
        ans.x = -(l.c) / l.a; ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS) {
        ans.x = p.x; ans.y = -(l.c) / l.b;
        return;
    }
    Line perp(l.b, -l.a, - (l.b*p.x - l.a*p.y));
    areIntersect(l, perp, ans);
}

const int N = 1024;
const int INF = 1e18;

Point start, finish;
vector<Point> a;

vector< pair<int, double> > to[N * 4];
double d[N * 4];
int n, sid, fid;

double dijkstra() {
    set< pair<double, int> > Q;
    for (int i = 0; i < a.size(); ++i) d[i] = INF;
    Q.insert(make_pair(0, sid));
    d[sid] = 0;
    while (!Q.empty()) {
        int u = Q.begin()->second;
        double du = Q.begin()->first;
        Q.erase(Q.begin());
        //cerr << u << ' ' << d[u] << endl;
        for (auto e : to[u]) {
            int v = e.first;
            double c = e.second;
            if (u == v) continue;
            //cerr << "edge " << u << ' ' << v << ' ' << c << endl;
            if (d[v] > d[u] + c) {
                if (d[v] < INF) {
                    Q.erase(Q.find(make_pair(d[v], v)));
                }
                d[v] = d[u] + c;
                Q.insert(make_pair(d[v], v));
            }
        }
    }
    //cerr << "fid = " << fid << endl;
    return d[fid];
}

bool do_not_cut(Point p, Point q) {
    Line curLine(p, q);
    for (int i = 0; i < n; ++i){
        vector<Point> cur;
        for (int j = 0; j < 4; ++j) {
            Line edge(a[i * 4 + j], a[i * 4 + (j + 1) % 4]);
            Point cutPoint;
            if (areIntersect(curLine, edge, cutPoint)) {
                Point foo;
                if (distToLineSegment(cutPoint, curLine.A, curLine.B, foo) < EPS && distToLineSegment(cutPoint, edge.A, edge.B, foo) < EPS) {
                    //cerr << p.x << ' ' << p.y << ' ' << i << ' ' << cutPoint.x << ' ' << cutPoint.y << endl;
                    cur.push_back(cutPoint);
                }
            }
        }
        for (int j = 0; j < cur.size(); ++j) {
            for (int k = 0; k < j; ++k) {
                if ((cur[j] - cur[k]).len() > EPS) return false;
            }
        }
    }
    return true;
}

int32_t main() {
    ios::sync_with_stdio(false);
    
    cin >> start.x >> start.y >> finish.x >> finish.y;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        a.push_back(Point(x, y));
        a.push_back(Point(u, y));
        a.push_back(Point(u, v));
        a.push_back(Point(x, v));
    }

    sid = a.size();
    fid = a.size() + 1;
    a.push_back(start);
    a.push_back(finish);

    for (int i = 0; i < 4 * n; ++i) {
        if (do_not_cut(start, a[i])) {
            to[sid].push_back(make_pair(i, (start - a[i]).len()));
        }
        if (do_not_cut(finish, a[i])) {
            to[i].push_back(make_pair(fid, (finish - a[i]).len()));
        }
    }
    if (do_not_cut(start, finish)) {
        to[sid].push_back(make_pair(fid, (finish - start).len()));
    }

    for (int i = 0; i < 4 * n; ++i) {
        for (int square = 0; square < n; ++square) {
            for (int j = 0; j < 4; ++j) {
                Point foo;
                if (distToLineSegment(a[i], a[square * 4 + j], a[square * 4 + (j + 1) % 4], foo) < EPS) {
                    to[i].push_back(make_pair(square * 4 + j, (a[i] - a[square * 4 + j]).len()));
                    to[i].push_back(make_pair(square * 4 + (j + 1) % 4, (a[i] - a[square * 4 + (j + 1) % 4]).len()));
                }
            }
        }
    }

    cout << setprecision(6) << fixed << dijkstra() << endl;
}