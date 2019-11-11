#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int N = 2019;

struct Point {
    LL x, y;

    Point() { x = y = 0; }
    Point(LL x, LL y) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x + a.x, y + a.y); }
    Point operator - (const Point& a) const { return Point(x - a.x, y - a.y); }
    Point operator * (LL k) const { return Point(x * k, y * k); }
    Point operator / (LL k) const { return Point(x / k, y / k); }
    Point& operator += (const Point &a) { return *this = *this + a; }
    Point& operator -= (const Point &a) { return *this = *this - a; }

    LL operator * (const Point& a) const { return x * a.x + y * a.y; } // dot product
    LL operator % (const Point& a) const { return x * a.y - y * a.x; } // cross product
    LL norm() { return x * x + y * y; }
    double len() { return sqrt(norm()); } // hypot(x, y);
};

struct Event {
    Point normal;
    int id1, id2; // if (id2 == -1) then id1 changes sign

    Event(Point normal, int id1, int id2) {
        if (normal.x < 0) {
            normal.x = -normal.x;
            normal.y = -normal.y;
        }
        this->normal = normal;
        this->id1 = id1;
        this->id2 = id2;
    }

    bool operator < (const Event &e) const {
        return normal % e.normal > 0;
    }
};

Point a[N];

vector<Event> E;
int pos[N];
int sign[N];
int n, k;

double res;
double best_x, best_y;

Point cur_sum;

void update_event(Event e) {
    cerr << "Event " << e.normal.x << ' ' << e.normal.y << ' ' << e.id1 << ' ' << e.id2 << endl;
    if (e.id2 == -1) {
        if (e.id1 == -1) return;
        int i = e.id1;
        cerr << i << endl;
        cur_sum -= a[i] * sign[i];
        sign[i] = -sign[i];
        cur_sum += a[i] * sign[i];
        return;
    }
    if (pos[e.id1] < k) cur_sum -= a[e.id1] * sign[e.id1];
    if (pos[e.id2] < k) cur_sum -= a[e.id2] * sign[e.id2];
    swap(pos[e.id1], pos[e.id2]);
    if (pos[e.id1] < k) cur_sum += a[e.id1] * sign[e.id1];
    if (pos[e.id2] < k) cur_sum += a[e.id2] * sign[e.id2];
}

void update_res(double cur, Point normal) {
    if (res > cur) return;
    res = cur;
    double x = -normal.y;
    double y = normal.x;
    //x /= normal.len();
    //y /= normal.len();
    while (max(x, y) > 1e9) {
        x /= 2;
        y /= 2;
    }
    best_x = x;
    best_y = y;
}

void update_max_dot(Point L, Point R, Point p) {
    double res = 0;
    update_res(abs(L * p / L.len()), L);
    update_res(abs(R * p / R.len()), R);
    if (L % p > 0 && p % R > 0) update_res(p * p / p.len(), p);
    p = Point(0, 0) - p;
    if (L % p > 0 && p % R > 0) update_res(p * p / p.len(), p);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
        a[i] = a[i] * 2;
    }

    for (int i = 0; i < n; ++i) {
        E.push_back(Event(Point(-a[i].y, a[i].x), i, -1));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            // through mid-point
            Point middle = (a[i] + a[j]) / 2;
            cerr << "middle point " << -middle.y << ' ' << middle.x << ' ' << i << ' ' << j << endl;
            E.push_back(Event(Point(-middle.y, middle.x), i, j));
            // parallel
            Point dir = a[i] - a[j];
            cerr << "dir " << -dir.y << ' ' << dir.x << ' ' << i << ' ' << j << endl;
            E.push_back(Event(Point(-dir.y, dir.x), i, j));
        }
    }

    E.push_back(Event(Point(1, 0), -1, -1));
    sort(begin(E), end(E));
    E.push_back(Event(Point(-1, 0), -1, -1));

    vector< pair<LL, int> > initial_order;
    for (int i = 0; i < n; ++i) {
        initial_order.push_back(make_pair(abs(a[i].x), i));
    }
    sort(begin(initial_order), end(initial_order));
    for (int it = 0; it < n; ++it) {
        int i = initial_order[it].second;
        pos[i] = it;
        sign[i] = (a[i].x > 0 || (a[i].x == 0 && a[i].y > 0)) ? 1 : -1;
        if (it < k) {
            cur_sum += a[i] * sign[i];
        }
    }
    cerr << "here " << cur_sum.x << ' ' << cur_sum.y << endl;

    for (int i = 0; i + 1 < E.size(); ++i) {
        int j = i;
        while (j + 1 < E.size() && !(E[i] < E[j + 1])) ++j;
        cerr << i << ' ' << j << endl;
        for (int k = i; k <= j; ++k) {
            cerr << "try update " << k << endl;
            update_event(E[k]);

            cerr << "after event\n";
            for (int p = 0; p < n; ++p) {
                cerr << p << ' ' << pos[p] << ' ' << sign[p] << endl;
            }
            cerr << "end debug\n";
        }
        cerr << "done update\n";
        update_max_dot(E[i].normal, E[i + 1].normal, cur_sum);
        i = j;
    }

    cout << setprecision(9) << fixed << res / 2.0 << endl;
    cout << best_x << ' ' << best_y << endl;
}