#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e18;

template<class T> struct LiChaoTree {
    struct Line {
        T a, b; // y = ax + b
        Line(T a, T b): a(a), b(b) {}
        T eval(int x) { return a * x + b; }
    };

    struct Node {
        int l, r;
        Line line;
        Node *left, *right;

        Node(int l, int r): l(l), r(r), line(0, -INF), left(0), right(0) {}

        void create_left() { if (!left) left = new Node(l, l + r >> 1); }
        void create_right() { if (!right) right = new Node((l + r >> 1) + 1, r); }

        void update(int i, int j, Line AB) {
            if (i <= l && r <= j) {
                Line CD = line;
                if (AB.eval(l) < CD.eval(l)) swap(AB, CD);
                if (AB.eval(r) >= CD.eval(r)) {
                    line = AB;
                } else {
                    int mid = l + r >> 1;
                    if (AB.eval(mid) > CD.eval(mid)) {
                        line = AB;
                        create_right();
                        right->update(i, j, CD);
                    } else {
                        line = CD;
                        create_left();
                        left->update(i, j, AB);
                    }
                }
                return;
            }
            int mid = l + r >> 1;
            if (i <= mid && j >= l) create_left(), left->update(i, j, AB);
            if (i <= r && j > mid) create_right(), right->update(i, j, AB);
        }

        T get(int x) {
            return max(line.eval(x), max(left ? left->get(x) : -INF, right ? right->get(x) : -INF));
        }

        ~Node() {
            //if (left) delete left;
            //if (right) delete right;
        }
    };

    Node *root;

    LiChaoTree() { root = 0; }
    LiChaoTree(int n) {
        root = new Node(1, n);
    }
    ~LiChaoTree() {
        //if (root) delete root;
    }

    void update(int i, int j, T a, T b) { root->update(i, j, Line(a, b)); }
    void update(T a, T b) { root->update(root->l, root->r, Line(a, b)); }
    T get(int x) { return root->get(x); }
};

const int N = 150005;
const int LIMIT = 300003;

LiChaoTree<int64_t> T[N * 4];

void update(int k, int l, int r, int i, int64_t a, int64_t b) {
    if (r < i || i < l) return;
    T[k].update(a, b);
    if (l < r) {
        update(k * 2, l, l + r >> 1, i, a, b);
        update(k * 2 + 1, (l + r >> 1) + 1, r, i, a, b);
    }
}

int get(int k, int l, int r, int64_t x, int64_t low) {
    if (T[k].get(x) < low) return 0;
    if (l == r) return l;
    if (T[k * 2 + 1].get(x) >= low) return get(k * 2 + 1, (l + r >> 1) + 1, r, x, low);
    return get(k * 2, l, l + r >> 1, x, low);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        for (int i = 1; i <= 4 * n; ++i) T[i] = LiChaoTree<int64_t>(LIMIT);

        int res = 0;
        for (int i = 1; i <= n; ++i) {
            int64_t a, b, x, y;
            cin >> a >> b >> x >> y;
            int cur = get(1, 1, n, x, y) + 1;
            update(1, 1, n, cur, a, b);
            res = max(res, cur);
        }
        cout << res << '\n';
    }
    return 0;
}