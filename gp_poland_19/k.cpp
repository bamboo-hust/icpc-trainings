#include <bits/stdc++.h>

using namespace std;

const int LIM = 100;
const double INF = 1e7;

struct Line {
    double a, b; // y = ax + b

    double eval(double x) const {
        return a * x + b;
    }

    bool operator < (const Line &o) const {
        if (a != o.a) return a < o.a;
        return b < o.b;
    }
};

struct ConvexHull {
    vector<Line> H;
    vector<Line> L;
    vector<double> X;

    double last_x;
    int last_pos;

    ConvexHull() {
        last_x = -INF;
        last_pos = -1;
    }

    bool bad(Line l1, Line l2, Line l3) {
        return (l3.b - l1.b) * (l1.a - l2.a) <= (l2.b - l1.b) * (l1.a - l3.a);
    }

    void add_line(double a, double b) {
        L.push_back(Line{a, b});
    }

    void init() {
        sort(L.rbegin(), L.rend());
        // decreasing slope
        for (const Line l : L) {
            while (H.size() >= 1 && H.back().a == l.a && H.back().b >= l.b) H.pop_back();
            while (H.size() >= 2 && bad(H[H.size() - 2], H[H.size() - 1], l)) H.pop_back();
            H.push_back(l);
        }
        X.push_back(-INF);
        for (int i = 1; i < H.size(); ++i) {
            X.push_back((H[i - 1].b - H[i].b) / (H[i].a - H[i - 1].a));
        }
        X.push_back(INF);
    }

    double eval(double x) { // min_y given x
        return H[upper_bound(X.begin(), X.end(), x) - X.begin() - 1].eval(x);
        if (abs(last_x - x) > 0) {
            last_x = x;
            last_pos = upper_bound(X.begin(), X.end(), x) - X.begin() - 1;
            return H[last_pos].eval(x);
        } else {
            last_x = x;
            double best = H[last_pos].eval(x);
            while (last_pos + 1 < H.size() && H[last_pos + 1].eval(x) < best) {
                best = H[++last_pos].eval(x);
            }
            while (last_pos > 0 && H[last_pos - 1].eval(x) < best) {
                best = H[--last_pos].eval(x);
            }
            return best;
        }
    }
};

double find_max_diff(ConvexHull &P, ConvexHull &Q) {
    double l = 0, r = INF;
    for (int it = 0; it < LIM; ++it) {
        double ll = l + (r - l) / 3;
        double rr = r - (r - l) / 3;
        double vl = P.eval(ll) + Q.eval(ll);
        double vr = P.eval(rr) + Q.eval(rr);
        if (vl < vr) {
            l = ll;
        } else {
            r = rr;
        }
    }
    return l;
}

void find_feasible_range(ConvexHull &P, ConvexHull &Q, double &L, double &R) {
    double middle = find_max_diff(P, Q);
    if (P.eval(middle) + Q.eval(middle) <= 0) {
        L = 0; R = -1;
        return;
    }
    {
        double l = 0, r = middle;
        for (int it = 0; it < 40; ++it) {
            double mid = (l + r) / 2;
            if (P.eval(mid) + Q.eval(mid) >= 0) {
                L = mid;
                r = mid;
            } else {
                l = mid;
            }
        }
    }
    {
        double l = middle, r = 1e7;
        for (int it = 0; it < 40; ++it) {
            double mid = (l + r) / 2;
            if (P.eval(mid) + Q.eval(mid) >= 0) {
                R = mid;
                l = mid;
            } else {
                r = mid;
            }
        }
    }
}

int n, q;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << setprecision(9) << fixed;

    int T; cin >> T;
    while (T--) {
        ConvexHull X, Y, U, V;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            int x, y, u, v, vx, vy;
            cin >> x >> y >> u >> v >> vx >> vy;
            X.add_line(-vx, -x);
            Y.add_line(-vy, -y);
            U.add_line(vx, u);
            V.add_line(vy, v);
        }

        X.init(); Y.init();
        U.init(); V.init();

        double lx, rx, ly, ry;
        find_feasible_range(X, U, lx, rx);
        find_feasible_range(Y, V, ly, ry);

        double L = max(lx, ly);
        double R = min(rx, ry);
        double l = L, r = R;

        double res = 0;
        if (L <= R) {
            for (int it = 0; it < LIM; ++it) {
                double ll = l + (r - l) / 3;
                double rr = r - (r - l) / 3;
                double vl = (X.eval(ll) + U.eval(ll)) * (Y.eval(ll) + V.eval(ll));
                double vr = (X.eval(rr) + U.eval(rr)) * (Y.eval(rr) + V.eval(rr));
                res = max(res, max(vl, vr));
                if (vl < vr) {
                    l = ll;
                } else {
                    r = rr;
                }
            }
        }
        double best = (l + r) / 2;
        cin >> q;
        while (q--) {
            double l, r;
            cin >> l >> r;
            l = max(l, L);
            r = min(r, R);
            if (l > r) {
                cout << "0\n";
            } else if (l <= best && best <= r) {
                cout << res << '\n';
            } else {
                double vl = (X.eval(l) + U.eval(l)) * (Y.eval(l) + V.eval(l));
                double vr = (X.eval(r) + U.eval(r)) * (Y.eval(r) + V.eval(r));
                cout << max(0.0, max(vl, vr)) << '\n';
            }
        }

    }
}
