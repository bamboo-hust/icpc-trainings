#include <bits/stdc++.h>

using namespace std;

const int N = 260;

int n;
int b[N];

multiset<int> ask(const vector<int> &query) {
    int k = query.size();
    if (k < 2) return multiset<int>();
    cout << 2 << ' ' << k;
    for (int u : query) cout << ' ' << u;
    cout << endl;
    multiset<int> s;
    for (int i = 1; i <= k * (k - 1) / 2; i++) {
        int u; cin >> u;
        s.insert(u);
    }
    return s;
}

multiset<int> subtract(multiset<int> s1, multiset<int> s2) {
    vector<int> ls;
    for (int u : s1) {
        if (s2.count(u)) {
            ls.push_back(u);
            s2.erase(s2.find(u));
        }
    }
    for (int u : ls) s1.erase(s1.find(u));
        return s1;
}

multiset<int> intersect(multiset<int> s1, multiset<int> s2) {
    multiset<int> res;
    for (int u : s2) {
        if (s1.count(u)) {
            res.insert(u);
            s1.erase(s1.find(u));
        }
    }
    return res;
}

int askOne(int u) {
    cout << 1 << ' ' << u << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    cin >> n;
    if (n == 1) {
        cout << "1 1" << endl;
        int u;
        cin >> u;
        cout << "3 " << u << endl;
        return 0;
    }
    vector<int> query;
    for (int i = 1; i <= n; i++) query.push_back(i);
    multiset<int> wholeArray = ask(query);
    int maxVal = *wholeArray.rbegin();
    int low = 1, high = n;
    while (high - low > 1) {
        int mid = low + high >> 1;
        query.clear();
        for (int i = 1; i <= mid; i++) query.push_back(i);
        multiset<int> cur = ask(query);
        int curMaxVal = *cur.rbegin();
        if (curMaxVal == maxVal) high = mid;
        else low = mid;
    }
    
    int center = high;
    query.clear();
    for (int i = 1; i <= n; i++) {
        if (i != center) query.push_back(i);
    }
    multiset<int> wholeArrayWithoutCenter = ask(query);
    multiset<int> wholeArrayB = subtract(wholeArray, wholeArrayWithoutCenter);

    multiset<int> withBit[8];
    for (int it = 0; it < 8; it++) {
        query.clear();
        for (int i = 1; i <= n; i++) {
            if (i != center && (i >> it & 1)) query.push_back(i);
        }
        multiset<int> curWithoutCenter = ask(query);
        query.push_back(center);
        multiset<int> cur = ask(query);
        withBit[it] = subtract(cur, curWithoutCenter);
    }

    for (int i = 1; i <= n; i++) {
        if (i == center) b[i] = 0;
        else {
            multiset<int> cur = wholeArrayB;
            for (int it = 0; it < 8; it++) {
                if (i >> it & 1) {
                    cur = intersect(cur, withBit[it]);
                } else {
                    cur = subtract(cur, withBit[it]);
                }
            }
            assert(cur.size() == 1);
            b[i] = *cur.begin();
        }
    }
    int valCenter = askOne(center);
    int valFoo = center == 1 ? askOne(2) : askOne(1);
    if (valCenter > valFoo) {
        cout << 3;
        for (int i = 1; i <= n; i++) cout << ' ' << valCenter - b[i];
            cout << endl;
    } else {
        cout << 3;
        for (int i = 1; i <= n; i++) cout << ' ' << valCenter + b[i];
            cout << endl;
    }
    return 0;
}