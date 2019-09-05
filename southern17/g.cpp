#include <bits/stdc++.h>

using namespace std;

int const N = 105;

int c[N];

int Convert(int cnt){
    int r = 0;
    for(int i=1; i<=cnt; i++)
        r = r * 10 + c[i];
    return r;
}

int CALC(int n){
    if(n < 10){
        return n - 1;
    }


    
    int x = n, cnt = 0;
    while(x){
        c[++cnt] = x % 10;
        x /= 10;
    }

    reverse(c+1, c+cnt+1);
    if(c[1] == 1){
        int ans = 0;
        for(int i=2; i<=cnt; i++){
            if(c[i] == 0)   continue;
            ans += c[i] + (i != cnt);
            c[i] = 0;
        }
        return ans + 1 + CALC(Convert(cnt)-1);
        
    }

    for(int i=2; i<=cnt; i++){
        if(c[i] == 1){
            c[i]--;
            c[1]++;
            break;
        }
    }


    int ans = c[1];
    c[1] = 1;
    for(int i=2; i<=cnt; i++){
        ans += c[i] + (i != cnt);
        c[i] = 0;
    }
    return ans + 1 + CALC(Convert(cnt) - 1);
}

int main() {
    //freopen("inp.txt", "r", stdin);    
    int T, n;
    cin >> T;
    while(T--){
        cin >> n;
        cout << CALC(n) << endl;
    }
}