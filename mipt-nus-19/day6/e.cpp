#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class Treap {
    struct Node {
        int key;
        uint32_t prior;
        int add_lazy;
        int maxV;
        int size;
        Node *l, *r;
        Node(int key): key(key), maxV(key), prior(rng()), add_lazy(0), size(1), l(nullptr), r(nullptr) {}
        ~Node() { delete l; delete r; }
    };

    inline int size(Node *x) { return x ? x->size : 0; }

    void push(Node *x) {
        if (x && x->add_lazy) {
            x->maxV += x->add_lazy;
            x->key += x->add_lazy;
            if (x->l) x->l->add_lazy += x->add_lazy;
            if (x->r) x->r->add_lazy += x->add_lazy;
            x->add_lazy = 0;
        }
    }

    inline void update(Node *x) {
        if (x) {
            x->size = size(x->l) + size(x->r) + 1;
            x->maxV = x->key;
            if (x->l) x->maxV = max(x->maxV, x->l->maxV);
            if (x->r) x->maxV = max(x->maxV, x->r->maxV);
        }
    }

    void join(Node *&t, Node *l, Node *r) {
        push(l); push(r);
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior < r->prior)
            join(l->r, l->r, r), t = l;
        else
            join(r->l, l, r->l), t = r;
        update(t);
    }

    void splitByIndex(Node *v, int x, Node* &l, Node* &r) {
        if (!v) return void(l = r = nullptr);
        push(v);
        int index = size(v->l) + 1;
        if (index < x)
            splitByIndex(v->r, x - index, v->r, r), l = v;
        else
            splitByIndex(v->l, x, l, v->l), r = v;
        update(v);
    }

    void show(Node *x) {
        if (!x) return;
        push(x);
        show(x->l);
        cerr << x->key << ' ';
        show(x->r);
    }

    Node *root;
    Node *l, *m, *r;

public:
    Treap() { root = NULL; }
    ~Treap() { delete root; }
    int size() { return size(root); }

    void insertAt(int pos, int x) {
        splitByIndex(root, pos, l, r);
        join(l, l, new Node(x));
        join(root, l, r);
    }

    void eraseAt(int x) {
        splitByIndex(root, x, l, m);
        splitByIndex(m, 2, m, r);
        delete m;
        join(root, l, r);
    }

    int valueAt(int pos) {
        splitByIndex(root, pos, l, m);
        splitByIndex(m, 2, m, r);
        int res = m->key;
        join(l, l, m);
        join(root, l, r);
        return res;
    }

    void addSuffix(int from, int v) {
        splitByIndex(root, from, l, r);
        r->add_lazy += v;
        join(root, l, r);
    }

    int getMaxPrefix(int k) {
        splitByIndex(root, k + 1, l, r);
        int res = l->maxV;
        join(root, l, r);
        return res;
    }

    void show() {
        cerr << "Size = " << size() << " ";
        cerr << "[";
        show(root);
        cerr << "]\n";
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int Q; cin >> Q;
    Treap T;
    int cursor = 1;
    while (Q--) {
        char c; cin >> c;
        if (c == 'I') {
            int x; cin >> x;
            int current = cursor > 1 ? T.valueAt(cursor - 1) : 0;
            //cerr << "current=" << current << endl;
            T.insertAt(cursor, current);
            //T.show();
            T.addSuffix(cursor, x);
            //T.show();
            ++cursor;
        } else if (c == 'D') {
            if (cursor == 1) continue;
            int x = T.valueAt(cursor - 1);
            //cerr << "del " << cursor << ' ' << x << endl;
            if (cursor > 2) x -= T.valueAt(cursor - 2);
            //cerr << "del " << cursor << ' ' << x << endl;
            T.addSuffix(cursor - 1, -x);
            T.eraseAt(cursor - 1);
            --cursor;
        } else if (c == 'L') {
            if (cursor > 1) {
                --cursor;
            }
        } else if (c == 'R') {
            if (cursor <= T.size()) {
                ++cursor;
            }
        } else {
            int k; cin >> k;
            k = min(k, cursor - 1);
            cout << T.getMaxPrefix(k) << '\n';
        }
        //cerr << "After " << c << ' ' << cursor << endl;
        //T.show();
    }
}