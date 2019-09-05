#include <bits/stdc++.h>

using namespace std;

void Solve(int n, int k){
    if(k == 2){
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

    int first;
    if(k % 2 == 1){
        first = 2;
        k = (k + 1) / 2;
    }
    else{
        first = 2;
        k = k / 2;
    }

    cout << first << " ";
    for(int i=2; i<=n; i++){
        cout << 1 << " ";
    }   cout << endl;

    cout << 1 << " " << k << " ";
    for(int i=3; i<=n; i++)
        cout << 1 << " ";

    for(int i=3; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(j == i){
                cout << 1 << " ";
            }
            else{
                cout << 0 << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    freopen("inp.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--){
            int n, k;
        cin >> n >> k;
        Solve(n, k);
    }
}
