#include <bits/stdc++.h>

using namespace std;

int main() {
    int T; cin >> T;
    vector< pair<int, int> > games;
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            games.push_back(make_pair(i, j));
        }
    }
    map< vector<int>, int > cnt;
    for (int mask = 0; mask < 729; ++mask) {
        vector<int> scores(4);
        int cur = mask;
        for (int match = 0; match < games.size(); ++match) {
            int outcome = cur % 3;
            cur /= 3;
            if (outcome == 0) {
                scores[games[match].first] += 3;
            } else if (outcome == 1) {
                scores[games[match].second] += 3;
            } else {
                scores[games[match].first]++;
                scores[games[match].second]++;
            }
        }
        cnt[scores]++;
    }

    for (int tc = 1; tc <= T; ++tc) {
        cout << "Case #" << tc << ": ";
        vector<int> a(4);
        for (int i = 0; i < 4; ++i) cin >> a[i];
        if (cnt.count(a)) {
            if (cnt[a] == 1) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        } else {
            cout << "Wrong Scoreboard" << endl;
        }
    }
}