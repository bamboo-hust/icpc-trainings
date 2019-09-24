#include <bits/stdc++.h>

using namespace std;


int const NN = 60;
long long const MAX = (1ll << 60);

string odd, even;
bool hemi_odd, hemi_even;



bool check_odd(int i, int total_size) {
    if (!hemi_odd) {
        return false;
    }
    if (i % 2 == 1) {
        int curPos = total_size - 1 - odd.size();
        if (curPos < odd.size()) {
            return odd[curPos] == '0';
        }
    }
    return true;
}

bool check_even(int i, int total_size) {
    if (!hemi_even) {
        return false;
    }
    if (i % 2 == 0) {
        int curPos = total_size - 1 - even.size();
        if (curPos < even.size()) {
            return even[curPos] == '0';
        }
    }
    return true;
}

long long pows(int x, int y) {
    if (y == -1) {
        return 0;
    }
    if (y == 0) {
        return 1;
    }
    long long u = pows(x, y / 2);
    u = u * u;
    if (y % 2) {
        u = u * x;
    }
    return u;
}

long long calc(int x, int y, int xt, int yt, int i) {
    if (i % 2) {
        x++;
    } else {
        y++;
    }
    int num_odd = -1;
    int num_even = -1;
    int num_total = -1;
    bool is_odd = check_odd(i, xt);
    bool is_even = check_even(i, yt);
    if (is_odd) {
        num_odd = (max(0, (xt - 2 * x + 1) / 2)) + (yt - y);
    }
    if (is_even) {
        num_even = (max(0, (yt - 2 * y + 1) / 2)) + (xt - x);
    }
    if (is_odd && is_even) {
        num_total = (max(0, (xt - 2 * x + 1) / 2)) + (max(0, (yt - 2 * y + 1) / 2));
    }

    if (num_odd == num_total) {
        num_odd = num_total = -1;
    } else {
        if (num_even == num_total) {
            num_even = num_total = -1;
        }
    }

    if (num_odd > NN || num_even > NN) {
        return MAX;
    }
    long long res = pows(2, num_odd) + pows(2, num_even) - pows(2, num_total);
    //cout << i << " " << x << " " << y << " " << xt << " " << yt << endl;
    //cout << i << " " << num_odd << " " << num_even << " " << num_total << " " << res << endl;
    return res;
}

string solve(int n, long long k) {
    int xt = n / 2, yt = n / 2;
    if (n % 2) {
        xt++;
    }
    int x = 0, y = 0;
    odd = "";
    even = "";
    string ans = "";
    hemi_odd = true;
    hemi_even = true;
    for (int i = 1; i <= n; i++) {
        char cur;
        long long num = calc(x, y, xt, yt, i);
        if (k <= num) {
            cur = '0';
        } else {
            k -= num;
            cur = '1';
        }
        if (i % 2 == 1) {
            x++;
            odd += cur;
            int curPos = xt - 1 - (odd.size() - 1);
            if (curPos < odd.size() && odd[curPos] != odd[(int)odd.size() - 1]) {
                hemi_odd = false;
            }
        } else {
            y++;
            even += cur;
            int curPos = yt - 1 - (even.size() - 1);
            if (curPos < even.size() && even[curPos] != even[(int)even.size() - 1]) {
                hemi_even = false;
            }
        }
        ans += cur;
    }
    if (k == 1) {
        return ans;
    }
    return "NOT FOUND!";
}

int main() {
    ios_base::sync_with_stdio(0);
    int test_case;
    cin >> test_case;
    for (int test = 1; test <= test_case; test++) {
        cout << "Case #" << test << ": ";
        long long n, k;
        cin >> n >> k;
        cout << solve(n, k) << endl;
    }
}