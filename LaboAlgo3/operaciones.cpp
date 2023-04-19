#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

long long mod_bin_exp(long long x, long long y, long long n) {
    if(y == 0){
        return 1;
    } else if(y % 2 == 0){
        long long z = mod_bin_exp(x, y/2, n);
        return (z*z) % n;
    } else {
        long long z = mod_bin_exp(x, y/2, n);
        return ((z*z % n)*x) % n;
    }
}

bool dp_mod_op(vector<int>& v, int m, int r) {
    int n = v.size();
    vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (long long j = 0; j <= m; j++) {
            dp[i][j] = dp[i][j] || dp[i-1][((j % m) * (v[i-1] % m)) % m];
            dp[i][j] = dp[i][j] || dp[i-1][((j - v[i-1]) % m + m) % m];
            dp[i][j] = dp[i][j] || dp[i-1][(j + (v[i-1] % m)) % m];
            dp[i][j] = dp[i][j] || dp[i-1][mod_bin_exp(j, v[i-1], m) % m];
        }
    }

    return dp[n][r];
}



int main(){
    int cantTests; cin >> cantTests;
    while(cantTests--){
    int n, r, m;
    cin >> n >> r >> m;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    bool res = dp_mod_op(v, m, r);
    if(res){
        cout << "Si" << endl;
    }else{
        cout << "No" << endl;
    }
    }
    
}