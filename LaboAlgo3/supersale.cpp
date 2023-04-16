#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define inf 1000000

vector<pair<int,int>> huevos;
vector<vector<int>> dp;
int superSale(int i, int c){

    if(c < 0){
        return -inf;
    }else if(i < 0){
        return 0;
    }else{
        if(dp[i][c] == -1){
            dp[i][c] = max(superSale(i-1, c-huevos[i].first) + huevos[i].second,
            superSale(i-1, c));
        }
        return dp[i][c];
    }
}



int main(){

    int T; cin >> T;
    while(T--){
        int cant; cin >> cant;
        huevos = vector<pair<int,int>>(cant+1);
        for(int i = 0; i < cant;i++){
            int peso, precio;
            cin >> precio >> peso;
            huevos[i] = make_pair(peso, precio);
        }
        int amigos; cin >> amigos;
        vector<int> capacidades(amigos+1);
        int max = 0;
        for(int i = 0; i < amigos;i++){
            int cap; cin >> cap;
            capacidades[i] = cap;

            if(cap > max){max = cap;}
        }
        dp = vector<vector<int>>(cant+1, vector<int>(max+1, -1));
        int res = 0;
        for(int i = 0; i < amigos;i++){
            
            res += superSale(huevos.size()-1, capacidades[i]);

        }
        cout << res << endl;
    }

}