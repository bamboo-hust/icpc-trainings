#include <bits/stdc++.h>
 
#define f first
#define s second
#define left __left
#define right __right
 
using namespace std;
 
int const N = 1e5 + 5;
int const MAX = 1e9 + 7;
 
int n;
 
pair < int, int > b[N], a[N];
 
 
int mul(pair < int, int > p, pair < int, int > q) {
    return p.f * q.s - p.s * q.f;
}
 
bool cmp_left(pair < int, int > p, pair < int, int > q) {
    return mul(p, q) > 0;
}
 
int solve() {
    vector < pair < int, int > > left, right;
    int best = 0;
    int equals = 0;
    for (int i = 1; i <= n; i++) {
        int x = b[i].f - b[1].f;
        int y = b[i].s - b[1].s;
        if (x == 0 && y == 0) {
            equals++;
            continue;
        }
        if (x <= 0 && y <= 0) {
            continue;
        }
 
        if (x > 0 && y > 0) {
            best++;
            continue;
        }
 
        if (x <= 0 && y >= 0) {
            left.push_back(make_pair(x, y));
        }
        if (x >= 0 && y <= 0) {
            right.push_back(make_pair(x, y));
        }
    }
 
    sort(left.begin(), left.end(), cmp_left);
    sort(right.begin(), right.end(), cmp_left);
   /* for (pair < int, int > p : left) {
    	cout << "left : " << p.f << " " << " " << p.s << endl;
    }
    for (pair < int, int > p : right) {
    	cout << "right : " << p.f << " " << p.s << endl;
    }*/
 
 
 
    int j = 0;
    int mins = MAX;
    for (int i = 0; i < left.size();) {
        int pos = i;
        while (pos < left.size() && mul(left[i], left[pos]) == 0) {
            pos++;
        }
        while (j < right.size() && mul(left[i], right[j]) >= 0) {
            j++;
        }
        mins = min(mins, i + (int)right.size() - j);
        //cout << "i j " << " " << i << " " << j << endl;
        //cout << "mins : " << i + (int)right.size() - j<< endl;
        i = pos;
    }
    j = 0;
    for (int i = 0; i < right.size();) {
        int pos = i;
        while (pos < right.size() && mul(right[i], right[pos]) == 0) {
            pos++;
        }
        while (j < left.size() && mul(right[i], left[j]) > 0) {
            j++;
        }
        mins = min(mins, (int)right.size() - pos + j);
        //cout << "i j " << " " << i << " " << j << endl;
        //cout << "mins : " << (int)right.size() - pos + j<< endl;
        i = pos;
    }
    if (mins == MAX) {
    	mins = 0;
    }
   // cout << "best : " << mins << " " << best << endl;
 
    return best + mins + 1;
}
 
 
int cost[N];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i].f >> b[i].s;
    }
    int ans2 = solve();
    cout << ans2;
 
    for (int i = 1; i <= n; i++) {
        b[i].f = -b[i].f;
        b[i].s = -b[i].s;
    }
    int ans1 = solve();
    ans1 = n + 1 - ans1;
    cout << " " << ans1 << endl;
}