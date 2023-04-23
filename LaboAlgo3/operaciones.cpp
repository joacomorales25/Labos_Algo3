
#include <iostream>
#include <vector>

using namespace std;

// Variables globales

vector<vector<int>> dp;
// Fin variables globales
long long mod_bin_exp(long long x, long long y, long long n) {
    
    if(y == 0){
        return 1;
    }else{
        long long z = mod_bin_exp(x, y/2, n);
        if(y % 2 == 0){
            return (z*z) % n;
        }else{
            return  ((z*z % n)*x) % n;
        }
    }
}

bool operaciones(vector<long long>& v, long long i, long long w, long long m, long long r){
    if(i >= v.size()){
        return w % m == r;
    }else{
        if(dp[i][w] != -1){
            return dp[i][w];
        }
        bool res = false;
        
        res = res || operaciones(v, i+1, (w*v[i])%m, m, r);
        res = res || operaciones(v, i+1, mod_bin_exp(w,v[i],m), m, r);
        res = res || operaciones(v, i+1, ((w-v[i])%m + m)%m, m, r);
        res = res || operaciones(v, i+1, (w+v[i])%m, m, r);
        
        dp[i][w] = res;
        
        return dp[i][w];
        
    }
}

int main(){
    int cantTests; cin >> cantTests;
    while(cantTests--){
    int n, r, m;
    cin >> n >> r >> m;
    vector<long long> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    dp = vector<vector<int>>(n+1, vector<int>(m+1, -1));
    bool res = operaciones(v, 1,v[0], m, r);

    if(res){
        cout << "Si" << endl;
    }else{
        cout << "No" << endl;
    }
    }
    return 0;
}