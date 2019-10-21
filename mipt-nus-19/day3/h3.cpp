#include <bits/stdc++.h>

using namespace std;

int const N = 2e5 + 5;
int const NN = 110;

bitset < NN > dp[NN];
string s[N];

int a[NN], b[NN], n, m;



bitset < NN > convert(string p) {
	bitset < NN > c;
	p = " " + p;
	for (int i = 1; i <= m; i++) {
		if (p[i] == '0') {
			continue;
		}
		if (a[i] == 1) {
			c[b[i] * 3] = 1;
		} else {
			c[b[i] * 3 + 1] = 1;
		}
	}

	for (int i = 2; i < NN; i += 3) {
		c[i] = (c[i - 1] ^ c[i - 2]);
	}
	return c;
}

void push(bitset < NN > q) {
	//cout << p << " " << q << endl;

	for (int j = NN - 1; j >= 0; j--) {
		if (q[j] == 0) {
			continue;
		}

		if (dp[j][j] == 0) {
			dp[j] = q;
			return;
		}

		q ^= dp[j];
	}
}

bool check(int k, bitset < NN > &ans) {
	bitset < NN > ans_copy = ans;
	if (ans[3 * k + 2] == 0) {
		if (dp[3 * k + 2][3 * k + 2]) {
			ans = ans ^ dp[3 * k + 2];
		} else {
			return false;
		}
	}
	if (ans[3 * k + 1] == 1) {
		if (dp[3 * k + 1][3 * k + 1]) {
			ans = ans ^ dp[3 * k + 1];
			if (ans[3 * k] == 0) {
				if (dp[3 * k][3 * k]) {
					ans = ans ^ dp[3 * k];
					return true;
				}
				ans = ans_copy;
				return false;
			}
			return true;
		}
		ans = ans_copy;
		return false;
	}
	

	if (ans[3 * k] == 0) {
		if (dp[3 * k][3 * k]) {
			ans = ans ^ dp[3 * k];
			return true;
		}
		ans = ans_copy;
		return false;
	}
	return true;
}

long long pows[NN];

string gen(int m) {
	string p = "";
	for (int i = 1; i <= m; i++) {
		p += (char)('0' + rand() % 2);
	}
	return p;
}

int main() {
	ios_base::sync_with_stdio(0);	cin.tie(0);
	pows[0] = 1;
	for (int i = 1; i < NN; i++) {
		pows[i] = pows[i - 1] * 3;
	}
	cin >> n >> m;
	// n = 20; m = 70;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}

	for (int j = 1; j <= m; j++) {
		cin >> a[j] >> b[j];
		// b[j] = (j - 1) / 2 + 1; a[j] = j % 2 ? 1 : -1;
		// cout << a[j] << " " << b[j] << endl;
	}

	// for (int j = 0; j < NN; j++) {
	// 	if (dp[j][j]) {
	// 		cout << dp[j] << endl;
	// 	}
	// }

	for (int i = 1; i <= n; i++) {
		push(convert(s[i]));
	}

	bitset < NN > ans;
	long long res = 0;
	for (int k = 35; k >= 0; k--) {
		bool is_positive = check(k, ans);
		if (is_positive) {
			res += pows[k];
		} else {
			if (ans[3 * k + 2] == 1) {
				if (dp[3 * k + 2][3 * k + 2] == 1) {
					ans = ans ^ dp[3 * k + 2];
				} else {
					res -= pows[k];
				}
			}
			if (ans[3 * k + 2] == 0) {
				if (dp[3 * k + 1][3 * k + 1] == 1) {
					for (int i = 3 * k; i < NN; i++) {
						dp[3 * k + 1][i] = 0;
					}
					push(dp[3 * k + 1]);
				}
			}
		}
	}
	// cout << ans << endl;

	long long tot = 0;
	for (int k = 0; k <= 35; k++) {
		if (ans[3 * k] == 1) {
			tot += pows[k];
		}
		if (ans[3 * k + 1] == 1) {
			tot -= pows[k];
		}
		assert(ans[3 * k + 2] == (ans[3 * k] ^ ans[3 * k + 1]));
	}
	assert(tot <= res);

	cout << res << endl;


}