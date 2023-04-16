
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void ordenar(vector<int>& v){

    sort(v.begin(), v.end());
}

int descuento(vector<int> &v){

    int desc = 0;

    for(int i = v.size()-1; i-2>= 0; i=i-3){

        desc += v[i-2];
    }
    return desc;
}



int main(){
    int tests, n;
    cin >> tests;

    while(tests--){
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n;i++){
        cin >> v[i];
    }

    ordenar(v);

    cout << descuento(v) << endl;
    }

}