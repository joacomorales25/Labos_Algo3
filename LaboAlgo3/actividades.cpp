#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;


void ordenar(vector<pair<pair<int,int>,int>>& v){

    sort(v.begin(), v.end(), [](pair<pair<int,int>,int> a, pair<pair<int,int>,int> b){
        return a.first.second < b.first.second;
    });
}

vector<int> actividades(vector<pair<pair<int,int>,int>>& v){
    vector<int> res;
    pair<int,int> ultAct = {-1,-1};
    for(int i = 0; i < v.size();i++){
        if(v[i].first.first >= ultAct.second){
            res.push_back(v[i].second);
            ultAct = v[i].first;
        }
    }
    return res;
}

int main(){
    // Open input file

    int numTests;
    cin >> numTests;
    for(int i = 1; i <= numTests; i++){
        int numActividades;
        cin >> numActividades;
        vector<pair<pair<int,int>,int>> v;
        for(int j = 1; j <= numActividades; j++){
            int inicio, fin;
            cin >> inicio >> fin;
            v.push_back(make_pair(make_pair(inicio, fin),j));
        }

        ordenar(v);
        vector<int> res = actividades(v);

        cout << res.size() << endl;
        
        for(int k = 0; k < res.size(); k++){
            if(k == res.size()-1){
                cout << res[k] << endl;
                continue;
            }
            cout << res[k] << " ";
        }
    }
    return 0;

}

