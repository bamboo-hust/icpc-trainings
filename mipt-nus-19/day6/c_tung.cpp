#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int const N = 1e3 + 5;
int const MOD = 1e9 + 7;

pair < int, int > a[N];
vector < int > val_x, val_y, point[N];
int x[N], y[N];



int get(int l, int r) {
	//cout << "get : " << l << " " << r << endl;
	int size = (r - l - 1);
	return 1ll * size * (size + 1) / 2 % MOD;
}

int add_mod(int x, int y) {
	return (x + y) % MOD;
}

int mul_mod(int x, int y) {
	//cout << "mul : " << x << " " << y << endl;
	return 1ll * x * y % MOD;
}

void add_point(set < pair < int, int > > &cur_seg, int y, int &hy) {
	auto it = cur_seg.lower_bound(make_pair(y, 0));
	it--;
	pair < int, int > p = *it;
	int l = p.f;
	int r = p.s;
	// cout << "pre hy " << hy << endl;
	// cout << "lr : " << l << " " << r << " " << y << endl;
	cur_seg.erase(cur_seg.find(p));
	hy = add_mod(hy, MOD - get(l, r));
	hy = add_mod(hy, get(l, y));
	hy = add_mod(hy, get(y, r));
	// cout << "updated hy " << hy << endl;
	cur_seg.insert(make_pair(l, y));
	cur_seg.insert(make_pair(y, r));
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	val_x.push_back(0);
	val_x.push_back(n + 1);
	for (int i = 1; i <= k; i++) {
		cin >> x[i] >> y[i];
		val_x.push_back(x[i]);
	}
	sort(val_x.begin(), val_x.end());

	for (int i = 1; i <= k; i++) {
		int pos = lower_bound(val_x.begin(), val_x.end(), x[i]) - val_x.begin();
		point[pos].push_back(y[i]);
	}

	int ans = mul_mod(get(val_x[0], val_x[1]), get(0, m + 1));
	for (int i = 1; i <= k; i++) {
		set < pair < int, int > > cur_seg;
		cur_seg.insert(make_pair(0, m + 1));
		int hy = get(0, m + 1);
		for (int j = i; j <= k; j++) {
			for (int y : point[j]) {
				add_point(cur_seg, y, hy);
			}
			int hx = mul_mod(val_x[i] - val_x[i - 1], val_x[j + 1] - val_x[j]);
			//cout << i << " " << j << " " << hx << " " << hy << endl;
			ans = add_mod(ans, mul_mod(hx, hy));
		}
		ans = add_mod(ans, mul_mod(get(val_x[i], val_x[i + 1]), get(0, m + 1)));
	}
	int total = mul_mod(get(0, n + 1), get(0, m + 1));
	cout << add_mod(total, MOD - ans) << endl;
}