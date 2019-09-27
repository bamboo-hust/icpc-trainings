#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

struct Node {
    int x;
    int sum;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    list<Node> L;
    vector<int> S;
    auto it = L.begin();
    while (q--) {
        char c; cin >> c;
        if (c == 'I') {
            int x; cin >> x;
            Node cur {x, x};
            if (it != L.begin()) {
                auto pre = it; --pre;
                cur.sum += pre->sum;
            }
            it = L.insert(it, cur);
            it++;
            S.push_back(max(cur.sum, S.empty() ? -INF : S.back()));
        } else if (c == 'D') {
            --it;
            it = L.erase(it);
            S.pop_back();
        } else if (c == 'L') {
            if (it != L.begin()) {
                --it;
                S.pop_back();
            }
        } else if (c == 'R') {
            if (it != L.end()) {
                if (it != L.begin()) {
                    auto pre = it;
                    --pre;
                    it->sum = pre->sum + it->x;
                } else {
                    it->sum = it->x;
                }
                S.push_back(max(it->sum, S.empty() ? -INF : S.back()));
                ++it;
            }
        } else {
            int k; cin >> k;
            cout << S[k - 1] << '\n';
        }

        // cerr << "begin list\n";
        // for (auto e : L) {
        //     cerr << e.x << ' ' << e.sum << endl;
        // }
        // cerr << "end list " << endl;
        // for (int v : S) {
        //     cerr << v << ' ';
        // }
        // cerr << endl << endl;
    }
}