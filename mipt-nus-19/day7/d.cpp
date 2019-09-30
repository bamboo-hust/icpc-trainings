#include <bits/stdc++.h>

using namespace std;

const double INF = 1000;
const double EPS = 1e-6;
const double LIM = 50;

bool maximize(double &a, double b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

double a, b, c, d, e, f;

double eval_quadratic(double alpha, double beta, double gamma, double x) {
    return alpha * x * x + beta * x + gamma * x;
}

double find_max_quadratic(double alpha, double beta, double gamma, double &x) {
    double res = -INF;
    if (maximize(res, eval_quadratic(alpha, beta, gamma, -INF))) x = -INF;
    if (maximize(res, eval_quadratic(alpha, beta, gamma, +INF))) x = +INF;
    if (abs(alpha) > EPS) {
        if (maximize(res, eval_quadratic(alpha, beta, gamma, -beta / (2 * alpha)))) x = -beta / (2 * alpha);
    }
    return res;
}

bool find_any_z(double x, double &z, double &max_v) {
    double alpha = d * d - 4 * b * c;
    double beta = 2 * d * f * x - 4 * b * e * x;
    double gamma = f * f * x * x - 4 * a * b * x * x + 4 * b;
    double z0 = INF;
    max_v = find_max_quadratic(alpha, beta, gamma, z0);
    if (max_v < 0) return false;
    z = z0;
    return true;
}

double get_y_know_xz(double x, double z) {
    double alpha = b;
    double beta = (d * z + f * x);
    double gamma = a * x * x + c * z * z + e * x * z - 1;
    double delta = beta * beta - 4 * alpha * gamma;
    return (-beta + sqrt(delta)) / (2 * alpha);
}

bool check_x(double x) {
    double z, max_v;
    return find_any_z(x, z, max_v);
}

vector<double> calc_z_know_xy(double x, double y) {
    //ax2 + by2 + cz2 + dyz + exz + fxy = 1
    double alpha = c;
    double beta = (d * y + e * x);
    double gamma = (a * x * x + b * y * y + f * x * y - 1);
    double delta = beta * beta - 4 * alpha * gamma;
    cerr << "calc_z_know_xy, x y delta= " << x << ' ' << y << ' ' << delta << endl;
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
    cerr << x << ' ' << y << ' ' << z << endl;
    assert((a * x * x + b * y * y + c * z * z + d * y * z + e * x * z + f * x * y - 1) < EPS);
    return x * x + y * y + z * z;
}

double find_any_y(double x) {
    double z0, max_v;
    assert(find_any_z(x, z0, max_v));
    return get_y_know_xz(x, z0);
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
    assert(z.size());
    cerr << "calc_z_know_xy, x y z = " << x << ' ' << y << ' ' << z[0] << endl;
    double res = INF;
    for (double z0 : z) {
        if (z0 > 0) {
            res = min(res, calc_know_xyz(x, y, z0));
        }
    }
    return res;
}

double calc_know_x(double x) {
    //double y0 = find_any_y(x);
    //double y_low = find_y_low(x, -INF, y0);
    //double y_high = find_y_high(x, y0, +INF);
    double y_low = 0;
    double y_high = find_y_high(x, 0, +INF);
    cerr << "calc_know_x, y_low y_high =  " << y_low << ' ' << y_high << endl;
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
    cerr << "calc_know_x " << x << ' ' << f << endl;
    return f;
}

double find_x_low(double xl, double xr) {
    double res = xr;
    for (int it = 0; it < LIM; ++it) {
        double x_mid = (xl + xr) / 2;
        if (check_x(x_mid)) {
            res = x_mid;
            xr = x_mid;
        } else {
            xl = x_mid;
        }
    }
    return res;
}

double find_x_high(double xl, double xr) {
    double res = xl;
    for (int it = 0; it < LIM; ++it) {
        double x_mid = (xl + xr) / 2;
        if (check_x(x_mid)) {
            res = x_mid;
            xl = x_mid;
        } else {
            xr = x_mid;
        }
    }
    return res;
}

double solve() {
    //double x_low = find_x_low(-INF, 1 / a / a);
    //double x_high = find_x_high(1 / a / a, +INF);
    double x_low = 0;
    double x_high = 1 / sqrt(a);
    cerr << "x_low = " << x_low << endl;
    cerr << "x_high = " << x_high << endl;
    assert(x_low <= x_high);
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

double stupid() {
    return sqrt(min(calc_know_xyz(1 / sqrt(a), 0, 0), min(calc_know_xyz(0, 1 / sqrt(b), 0), calc_know_xyz(0, 0, 1 / sqrt(c)))));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    while (cin >> a >> b >> c >> d >> e >> f) {
        double res = solve();
        res = sqrt(res);
        //double res = stupid();
        cout << setprecision(6) << fixed << res << '\n';
    }
}