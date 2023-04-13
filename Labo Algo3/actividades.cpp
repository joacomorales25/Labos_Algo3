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

vector<int> actividades(vector<pair<pair<int,int>,int>> v){
    vector<int> res;
    res.push_back(v[0].second);
    pair<int,int> ultAct = v[0].first;
    for(int i = 1; i < v.size();i++){
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
        
        for(int i = 0; i < res.size(); i++){

            cout << res[i] << " ";
        }
    }
    return 0;

}

