#include <bits/stdc++.h>

using namespace std;

#define FORE(i, a, b) for(int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define X first
#define Y second
#define ll long long
#define mp make_pair
#define pb push_back
#define endl '\n'


const int N = 100;

int dp[N];

bool check(const vector<int> &a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i] != 0) {
            return 1;
        }
    }
    return 0;
}

int get(vector<int> b) {
    vector<int> a;
    for (int i = 0; i < b.size(); i++) {
        a.push_back(b[i]);
    }
    int res = 0;
    if (a[0] == 1) {
        res = 0;
        for (int i = 1; i < a.size(); i++) {
            if (a[i] != 0) {
                res += a[i] + 1;
                if (i + 1 == a.size()) {
                    res--;    
                }
            }        
        }   
    } else {
        int f = 0;
        for (int i = 1; i <= a.size(); i++) {
            if (f == 0 && a[i] == 1) {
                a[i] = 0;
                f = 1;
                break;
            }
        }
        if (f) a[0] ++;
        res = a[0];
        for (int i = 1; i < a.size(); i++) {
            if (a[i] != 0) {
                res += a[i] + 1;
                if (i + 1 == a.size()) {
                    res--;
                }
            }
        }
    }
    return res;
}

#define ll long long

ll gt[50],lt[50];
int a[50];


int sum(int x)
{
    int s = 0;
    int lt = 0;
    while (x)
    {
        s += x%10;
        a[++lt] = x%10;
        x /= 10;
    }
    FORE(i,2,lt)
    if (a[i] == 0) --s;
    return s;
}

int pt(int n)
{
    //cout<< n <<endl;
    if (n <=10) return n - 1;
    int l = 0;
    while (lt[l] <= n) ++l;
    --l;
    int ans = gt[l];

    if(n%lt[l] != 0)
    {
        int x = n;
        //if (x%10 == 1) ++ans;
        x /= 10;
        while (x >= 10)
        {
            if(x%10 == 1)
            {
                --ans;
                break;
            }
            x /= 10;
        }
        if (x == 1) --ans;
        //cout<<n<<' '<<ans<<endl;
        //cout<<n<<' '<<ans+sum(n)<<' '<<l<<endl;
        ans += sum(n) - 1 + l;

    }
    else
    {
        //int q = n/lt[l];
        //if (q == 1) return ans;
        //ans += q;
        //if (q == 2) --ans;
        //cout<<n<<' '<<ans<<' '<<q<<endl;
        ans = pt(n-1) + 1;
    }
    //if (x == 1) --ans;
    return ans;
}

int main() {
    dp[0] = 0;
    for (int i = 1; i <= 10; i++) {
        dp[i] = dp[i - 1] + 10 * i - 1;
    }

    lt[0] = 1;
    FORE(i,1,10) lt[i] = lt[i-1]*10;
    gt[1] = 9;
    FORE(i,2,9) gt[i] = gt[i-1] + 10*i - 1;
  
    int t;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        int n;
        ///cin >> n;
        n = rand() % (int)1e9 + 1;
        int nn = n;
         int res = 0;
        if (n < 10) {
            res = n - 1;
        } else {

            vector<int> a;
            a.clear();
            while (n) {
                a.push_back(n % 10);
                n /= 10;
            }
            reverse(a.begin(), a.end());
            res = dp[a.size() - 1];
            if (check(a)) { 
                res += get(a);
            } else { 
                if (a[0] == 1) {
                } else {
                    a[0]--;
                    for (int i = 1; i < a.size(); i++) {
                        a[i] = 9;
                    }
                    res += 1 + get(a);
                }
            }
        }
        
        int ans = pt(nn);
         //cout << res << endl;
        //cout << ans << endl;
        
        if (ans != res) {
            cout <<  ans << " " << res << " " << nn << endl;
        }
    }
    return 0;
}