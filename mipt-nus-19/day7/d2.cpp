#include <bits/stdc++.h>

using namespace std;

const double INF = 1000;
const double EPS = 1e-6;
const double LIM = 100;

bool maximize(double &a, double b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

double a, b, c, d, e, f;

vector<double> calc_z_know_xy(double x, double y) {
    //ax2 + by2 + cz2 + dyz + exz + fxy = 1
    double alpha = c;
    double beta = (d * y + e * x);
    double gamma = (a * x * x + b * y * y + f * x * y - 1);
    double delta = beta * beta - 4 * alpha * gamma;
    //cerr << "calc_z_know_xy, x y delta= " << x << ' ' << y << ' ' << delta << endl;
    if (delta < 0) return vector<double>();
    double z0 = (-beta + sqrt(delta)) / (2 * alpha);
    double z1 = (-beta - sqrt(delta)) / (2 * alpha);
    vector<double> z;
    z.push_back(z0);
    z.push_back(z1);
    return z;
}

bool check_xy(double x, double y) {
    return calc_z_know_xy(x, y).size();
}

double calc_know_xyz(double x, double y, double z) {
    //cerr << x << ' ' << y << ' ' << z << ' ' << sqrt(x * x + y * y + z * z) << endl;
    //assert((a * x * x + b * y * y + c * z * z + d * y * z + e * x * z + f * x * y - 1) < EPS);
    return x * x + y * y + z * z;
}

double find_y_low(double x, double yl, double yr) {
    double res = yr;
    for (int it = 0; it < LIM; ++it) {
        double y_mid = (yl + yr) / 2;
        if (check_xy(x, y_mid)) {
            res = y_mid;
            yr = y_mid;
        } else {
            yl = y_mid;
        }
    }
    return res;
}

double find_y_high(double x, double yl, double yr) {
    double res = yl;
    for (int it = 0; it < LIM; ++it) {
        double y_mid = (yl + yr) / 2;
        if (check_xy(x, y_mid)) {
            res = y_mid;
            yl = y_mid;
        } else {
            yr = y_mid;
        }
    }
    return res;
}

double calc_know_xy(double x, double y) {
    vector<double> z = calc_z_know_xy(x, y);
    //assert(z.size());
    double res = INF;
    for (double z0 : z) {
        res = min(res, calc_know_xyz(x, y, z0));
    }
    return res;
}

double calc_know_x(double x) {
    double y_low = find_y_low(x, -INF, 0);
    double y_high = find_y_high(x, 0, +INF);
    //cerr << "calc_know_x, y_low y_high =  " << y_low << ' ' << y_high << endl;
    for (int it = 0; it < LIM; ++it) {
        double y_l = y_low + (y_high - y_low) / 3;
        double y_r = y_high - (y_high - y_low) / 3;
        double vl = calc_know_xy(x, y_l);
        double vr = calc_know_xy(x, y_r);
        if (vl < vr) {
            y_high = y_r;
        } else {
            y_low = y_l;
        }
    }
    double y_opt = (y_low + y_high) / 2;
    double f = calc_know_xy(x, y_opt);
    //cerr << "calc_know_x " << x << ' ' << f << endl;
    return f;
}

double solve() {
    double x_low = -1/ sqrt(a);
    double x_high = 1 / sqrt(a);
    //cerr << "x_low = " << x_low << endl;
    //cerr << "x_high = " << x_high << endl;
    //assert(x_low <= x_high);
    for (int it = 0; it < LIM; ++it) {
        double x_l = x_low + (x_high - x_low) / 3;
        double x_r = x_high - (x_high - x_low) / 3;
        double vl = calc_know_x(x_l);
        double vr = calc_know_x(x_r);
        if (vl < vr) {
            x_high = x_r;
        } else {
            x_low = x_l;
        }
    }
    double x_opt = (x_low + x_high) / 2;
    return calc_know_x(x_opt);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    while (cin >> a >> b >> c >> d >> e >> f) {
        double res = solve();
        res = sqrt(res);
        cout << setprecision(6) << fixed << res << '\n';
    }
}