#include <bits/stdc++.h>

using namespace std;
#define int long long

int const N = 4e5 + 5;

int const MOD = 1e9 + 7;

int mul_mod(int x, int y) {
	return 1ll * x * y % MOD;
}

int add_mod(int x, int y) {
	int res = (x + y) % MOD;
	return res;
}

struct Rec
{
	int x1, y1, x2, y2, id;
	Rec(){};
	Rec(int _x1, int _y1, int _x2, int _y2, int _id) {
		x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2; id = _id;
	}
};


struct BIT
{
	int tree[N];
	void update(int x, int val) {
		x++;
		while (x < N) {
			tree[x] = add_mod(tree[x], val);
			x += x & (-x);
		}
	}

	int get(int x) {
		x++;
		int res = 0;
		while (x) {
			res = add_mod(res, tree[x]);
			x -= x & (-x);
		}
		return res;
	}
};

vector < int > real_val_y, real_val_x;

struct BIT_SEGMENT
{
	BIT t1, t2;
	void update(int x, int y, int val) {
		assert(x < real_val_y.size());
		// cout << "update : " << x << " " << y << " " << val << endl;
		t1.update(x, MOD - mul_mod(val, real_val_y[x]));
		t1.update(y + 1, mul_mod(val, real_val_y[x]));

		t2.update(x, val);
		t2.update(y + 1, MOD - val);

		t1.update(y + 1, mul_mod(val, add_mod(real_val_y[y] + 1, MOD - real_val_y[x])));
	}	

	int get_val(int x) {
		if (x < 0) {
			return 0;
		}
		assert(x < real_val_y.size());
		return add_mod(t1.get(x), mul_mod(t2.get(x), (real_val_y[x] + 1)));
	}

	int get_segment(int x, int y) {
		int res = add_mod(get_val(y), MOD - get_val(x - 1));
		return res;
	}
};

struct BIT_2D
{
	BIT_SEGMENT t1, t2;
	void update(int time, int x, int y, int val) {
		assert(time < real_val_x.size());
		t1.update(x, y, mul_mod(real_val_x[time], val));
		t2.update(x, y, val);
	}

	int get_rec(int time, int x, int y) {
		assert(time < real_val_x.size());
		int res = add_mod(mul_mod(t2.get_segment(x, y), real_val_x[time] + 1), MOD - t1.get_segment(x, y));
		return res;
	} 
};

BIT_2D tree_2d;


struct Query
{
	int time, l, r, type, val, id; // type = 1 -> update, 2 -> get
	Query(){};
	Query(int _time, int _l, int _r, int _type, int _val, int _id) {
		time = _time; l = _l; r = _r; type = _type; val = _val; id = _id;
	}
};


Rec a[N];

int add[N], n;




vector < Query > que;

bool cmp(Query p, Query q) {
	if (p.time != q.time) {
		return p.time < q.time;
	}
	return p.type < q.type;
}

void solve(int start, int end) {
	if (start == end) {
		int i = start;
		int hx = add_mod(real_val_x[a[i].x2] + 1, MOD - real_val_x[a[i].x1]);
		int hy = add_mod(real_val_y[a[i].y2] + 1, MOD - real_val_y[a[i].y1]);
		add[a[i].id] = add_mod(add[a[i].id], mul_mod(hx, hy));
		return;
	}

	int mid = (start + end) >> 1;
	solve(start, mid);
	que.clear();
	for (int i = start; i <= mid; i++) {
		que.push_back(Query(a[i].x1, a[i].y1, a[i].y2, 1, add[a[i].id], a[i].id));
		if (a[i].x2 + 1 < real_val_x.size()) {
			que.push_back(Query(a[i].x2 + 1, a[i].y1, a[i].y2, 1, MOD - add[a[i].id], a[i].id));
		}
	}

	for (int i = mid + 1; i <= end; i++) {
		if (a[i].x1 > 0) {
			que.push_back(Query(a[i].x1 - 1, a[i].y1, a[i].y2, 2, -1, a[i].id));
		}
		que.push_back(Query(a[i].x2, a[i].y1, a[i].y2, 2, 1, a[i].id));
		// cout << "query_get : " << a[i].x1 << " " << a[i].y1 << " " << a[i].x2 << " " << a[i].y2 << endl;
	}

	sort(que.begin(), que.end(), cmp);

	for (Query p : que) {
		if (p.type == 1) {
			tree_2d.update(p.time, p.l, p.r, p.val);
		} else {
			int val = tree_2d.get_rec(p.time, p.l, p.r);
			add[p.id] = add_mod(add[p.id], mul_mod(val, p.val));
		}
	}


	for (Query p : que) {
		if (p.type == 1) {
			tree_2d.update(p.time, p.l, p.r, MOD - p.val);
		}
	}
	solve(mid + 1, end);

}

int get_pos_x(int x) {
	return lower_bound(real_val_x.begin(), real_val_x.end(), x) - real_val_x.begin();
}

int get_pos_y(int y) {
	return lower_bound(real_val_y.begin(), real_val_y.end(), y) - real_val_y.begin();
}


 main() {
	ios_base::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
		assert(a[i].x1 <= a[i].x2);
		assert(a[i].y1 <= a[i].y2);
		a[i].id = i;
		real_val_x.push_back(a[i].x1);
		real_val_x.push_back(a[i].x1 - 1);
		real_val_x.push_back(a[i].x1 + 1);
		real_val_x.push_back(a[i].x2);
		real_val_x.push_back(a[i].x2 - 1);
		real_val_x.push_back(a[i].x2 + 1);
		real_val_y.push_back(a[i].y1);
		real_val_y.push_back(a[i].y1 - 1);
		real_val_y.push_back(a[i].y1 + 1);
		real_val_y.push_back(a[i].y2);
		real_val_y.push_back(a[i].y2 - 1);
		real_val_y.push_back(a[i].y2 + 1);
	}
	sort(real_val_x.begin(), real_val_x.end());
	real_val_x.resize(unique(real_val_x.begin(), real_val_x.end()) - real_val_x.begin());
	sort(real_val_y.begin(), real_val_y.end());
	real_val_y.resize(unique(real_val_y.begin(), real_val_y.end()) - real_val_y.begin());
	for (int i = 1; i <= n; i++) {
		a[i].x1 = get_pos_x(a[i].x1);
		a[i].x2 = get_pos_x(a[i].x2);
		a[i].y1 = get_pos_y(a[i].y1);
		a[i].y2 = get_pos_y(a[i].y2);
	}
	solve(1, n);
	int res = 0;
	for (int i = 1; i <= n; i++) {
		int hx = add_mod(real_val_x[a[i].x2] + 1, MOD - real_val_x[a[i].x1]);
		int hy = add_mod(real_val_y[a[i].y2] + 1, MOD - real_val_y[a[i].y1]);
		res = add_mod(res, mul_mod(add[a[i].id], mul_mod(hx, hy)));
	}
	res = add_mod(res, MOD);
	cout << res << endl;
}