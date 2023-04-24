#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;


void countingSort(vector<pair<pair<int,int>,int>>& v, int max_val){
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
        res[count[v[i].first.second]-1] = v[i]; // guardo el elemento en la posicion que le corresponde
        count[v[i].first.second]--; // por si hay mas de un elemento con el mismo tiempo final
    }
    
    // Copio todo al vector original
    for(int i = 0; i < n; i++){
        v[i] = res[i];
    }
}

void ordenar(vector<pair<pair<int,int>,int>>& v, int max){
    countingSort(v, max);
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
    ifstream inputFile("iguales.txt");
    if(!inputFile){
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    // Open output file
    ofstream outputFile("output_iguales.txt");
    if(!outputFile){
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    int numTests;
    inputFile >> numTests;
    for(int i = 1; i <= numTests; i++){
            int numActividades;
            inputFile >> numActividades;
            vector<pair<pair<int,int>,int>> v;
            int max_val = -1;
            for(int j = 0; j < numActividades; j++){
                int inicio, fin;
                inputFile >> inicio >> fin;
                if(fin > max_val)
                    max_val = fin;
                v.push_back(make_pair(make_pair(inicio, fin),j+1));
            }
            auto start = chrono::high_resolution_clock::now();
            ordenar(v, max_val);
            vector<int> res = actividades(v);
            auto end = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


            outputFile << numActividades << " " << duration.count() << endl;
        }

    inputFile.close();
    outputFile.close();

    return 0;
}

