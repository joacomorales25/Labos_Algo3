#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;


void bucketSort(vector<pair<pair<int,int>,int>>& v, int max_val){
    int n = v.size();
    vector<int> count(max_val+1, 0);
    
    // Cuento cuantas veces aparece cada tiempo final en el vector
    for(int i = 0; i < n; i++){
        count[v[i].first.second]++;
    }
    
    // me fijo cuantos elementos hay antes de cada tiempo final para saber el orden en el que van a quedar
    for(int j = 1; j <= max_val; j++){
        count[j] += count[j-1];
    }
    
    // Creo un vector auxiliar para guardar los elementos ordenados
    vector<pair<pair<int,int>,int>> res(n);
    for(int i = n-1; i >= 0; i--){
        res[count[v[i].first.second]-1] = v[i];
        count[v[i].first.second]--; // por si hay mas de un elemento con el mismo tiempo final
    }
    
    // Copio todo al vector original
    for(int i = 0; i < n; i++){
        v[i] = res[i];
    }
}

void ordenar(vector<pair<pair<int,int>,int>>& v){
    int max_val = -1;
    for(pair<pair<int,int>,int> p: v){
        max_val = max(max_val, p.first.second);
    }
    bucketSort(v, max_val);
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

    return 0;
}

