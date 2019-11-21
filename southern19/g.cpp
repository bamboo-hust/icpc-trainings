#include <bits/stdc++.h>

using namespace std;
#define f first
#define s second

int const N = 1e5 + 5;
long long const MAX = 1000000000000000005;

int n;
long long s;
pair < long long, int > l[N];


long long mul(long long x, long long y) {
	if (x > MAX / y) {
		return MAX;
	}
	return x * y;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		cin >> l[i].f; l[i].s = i;
	}

	sort (l + 1, l + n + 1);
	vector < long long > a;
	long long ans = 0;
	pair < long long, long long > ans_val;
	ans_val = make_pair(-1LL, -1LL);
	for (int i = 1; i <= n;) {
		int pos = i;
		while (pos <= n && l[pos].f == l[i].f) {
			pos++;
		}

		if (pos - i >= 4 && mul(l[i].f, l[i].f) < s) {
			if (ans < mul(l[i].f, l[i].f)) {
				ans = max(ans, mul(l[i].f, l[i].f));
				ans_val = make_pair(l[i].f, l[i].f);
			}
		}
		if (pos - i >= 2) {
			a.push_back(l[i].f);
		}
		i = pos;
	}




	for (int i = 0; i < a.size(); i++) {
		long long val = s / a[i] + ((s % a[i]) != 0);
		int pos = lower_bound(a.begin(), a.end(), val) - a.begin() - 1;
		// cout << a[i] << " " << a[pos] << endl;
		if (pos <= i) {
			continue;
		}
		if (ans < a[i] * a[pos]) {
			ans = a[i] * a[pos];
			ans_val = make_pair(a[i], a[pos]);
		}
	}
	if (ans_val == make_pair(-1LL, -1LL)) {
		cout << -1 << endl;
		return 0;
	}

	map < long long, int > cnt;
	cnt[ans_val.f] += 2;
	cnt[ans_val.s] += 2;
	vector < int > index;
	for (int i = 1; i <= n; i++) {
		if (cnt[l[i].f]) {
			index.push_back(l[i].s);
			cnt[l[i].f]--;
		}
	}

	sort(index.begin(), index.end());
	for (int v : index) {
		cout << v << " ";
	}
	cout << endl;

}