#include <bits/stdc++.h>

using namespace std;

const int N = 33;

bool is_prime[N];
vector<int> P;

vector<int> state[N];

int cur[N];

set<int64_t> S;
int d, h;

void backtrack(int i, int last, int rem) {
    if (rem < 0) return;
    if (i > d) {
        if (rem == 0) {
            int64_t more = 1;
            for (int j = 0; j < P.size(); ++j) {
                for (int k = 0; k < cur[j]; ++k) {
                    more *= P[j];
                }
            }
            S.insert(more);
        }
        return;
    }
    for (int x = last; x <= rem; ++x) {
        for (int j = 0; j < P.size(); ++j) cur[j] -= state[x][j];
        backtrack(i + 1, x, rem - x);
        for (int j = 0; j < P.size(); ++j) cur[j] += state[x][j];
    }
}

int main() {
    ios::sync_with_stdio(false);
    memset(is_prime, 1, sizeof is_prime);
    for (int i = 2; i < N; ++i) if (is_prime[i]) {
        for (int j = i + i; j < N; j += i) is_prime[j] = false;
    }
    
    for (int i = 2; i < N; ++i) if (is_prime[i]) {
        P.push_back(i);
    }

    state[0] = vector<int>(P.size());
    for (int i = 1; i < N; ++i) {
        state[i] = state[i - 1];
        int x = i;
        for (int j = 0; j < P.size(); ++j) {
            while (x % P[j] == 0) {
                x /= P[j];
                state[i][j]++;
            }
        }
    }

    cin >> d >> h;
    for (int j = 0; j < P.size(); ++j) {
        cur[j] = state[h - 1][j];
    }
    backtrack(1, 0, h - 1);

    for (auto v : S) {
        cout << v << '\n';
    }

    return 0;
}