#include <bits/stdc++.h>

using namespace std;

struct Job {
    int a, b;
};

int calc(const vector<Job> &a) {
    int t = 0;
    int res = 0;
    for (int i = 0; i < a.size(); ++i) {
        t += a[i].a;
        res += max(0, t - a[i].b);
    }
    return res;
}

int solve(vector<Job> a) {
    vector<Job> L, R;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i].a > a[i].b) {
            L.push_back(a[i]);
        } else {
            R.push_back(a[i]);
        }
    }
    sort(begin(L), end(L), [] (const Job &x, const Job &y) {
        return x.a < y.a;
    });
    sort(begin(R), end(R), [] (const Job &x, const Job &y) {
        return x.b < y.b;
    });
    L.insert(L.end(), begin(R), end(R));
    return calc(L);
}

int solve_naive(vector<Job> a) {
    vector<int> p(a.size());
    for (int i = 0; i < p.size(); ++i) p[i] = i;
    int res = INT_MAX;
    do {
        vector<Job> b = a;
        for (int i = 0; i < p.size(); ++i) {
            b[i] = a[p[i]];
        }
        res = min(res, calc(b));
    } while (next_permutation(begin(p), end(p)));
    return res;
}

void stress() {
    const int LIM = 10;
    for (int tc = 1; tc <= 100; ++tc) {
        cerr << tc << endl;
        vector<Job> a;
        int n = 2;
        for (int i = 0; i < n; ++i) {
            a.push_back(Job{rand() % LIM + 1, rand() % LIM + 1});
        }
        int my = solve(a);
        int correct = solve_naive(a);
        cerr << my << ' ' << correct << endl;
        if (my != correct) {
            cerr << n << endl;
            for (int i = 0; i < n; ++i) {
                cerr << a[i].a << ' ' << a[i].b << endl;
            }
        }
        assert(my == correct);
    }
}

int main() {
    stress();
    return 0;
}