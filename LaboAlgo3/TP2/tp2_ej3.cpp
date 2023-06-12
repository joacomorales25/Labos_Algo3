#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include<tuple>
#include <limits>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>


using namespace std;

using ll = long long;
const ll inf = 1e18;

vector<vector<int>> loc;
int nro_test;
int test;
int n,r,w,UTP,FO;
vector<tuple<double,int,int, int>> E;
int componentes;
double Pu, Pv;



struct DSU_Path{

    DSU_Path(int n){
        padre = rank = vector<int>(n); // Inicializo vector de padres y su distancia al padre
        for(int v = 0; v < n; v++) padre[v] = v; // cada nodo es su propio padre
    }

    int find(int v){ // Encuentra el padre de v
        if(v == padre[v]) return v;  
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){ //
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v); // agarro el de mayor ranking
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1); // me aumenta la distancia a del mas chico
    }

    vector<int> padre;
    vector<int> rank;
};

struct DSU{

    DSU(int n){
        padre = vector<int>(n); // Inicializo vector de padres y su distancia al padre
        for(int v = 0; v < n; v++) padre[v] = v; // cada nodo es su propio padre
    }

    int find(int v){ // Encuentra el padre de v
        if(v == padre[v]) return v;  
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){ //
        u = find(u), v = find(v);
        if(u == v) return; // agarro el de mayor ranking
        padre[v] = padre[u];
        // me aumenta la distancia a del mas chico
    }
    vector<int> padre;
};

double distancia_euclidea(double x0, double x1, double y0, double y1) {
    double deltaX = x0 - y0;
    double deltaY = x1 - y1;
    
    return std::sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

vector<tuple<double,int,int, int>> crear_grafo(vector<vector<int>>& nodos){
    vector<tuple<double,int,int, int>> E;
    double c;            // precio del cable
    int tipoDeCable; // 0 si es UTP, 1 si es Fibra Optica                                
    for (int i = 0; i < nodos.size(); i++){
        for (int j = i+1; j < nodos.size(); j++){
            if (i!=j){
                int x1=nodos[i][0];
                int y1=nodos[i][1];

                int x2=nodos[j][0];
                int y2=nodos[j][1];
                double d = distancia_euclidea(x1,y1,x2,y2);
                if (d<=r){
                    c = UTP*d;
                    tipoDeCable = 0;
                }else{
                    c = FO*d;
                    tipoDeCable = 1;
                }
                E.push_back({c,i,j, tipoDeCable});
            }
        }
        
    }
    return E;
    
}


void kruskal(){
    
    sort(E.begin(),E.end());
    double res = 0;
    int aristas = 0;
    DSU_Path dsu(n);
    for(auto e: E){
        double c;
        int tc;
        int x_1, x_2;
        tie(c,x_1,x_2,tc) = e;
        //si (u,v) es arista segura
        if(dsu.find(x_1) != dsu.find(x_2)){
            // agregar
            dsu.unite(x_1,x_2);
            if (tc == 0){
                Pu += c;
            }else{
                Pv += c;
            }
            aristas++;
            componentes--;     // me disminuye la cantidad de componentes
            if (componentes==w){ // salgo del for
                break;
                }
        }
    }

    
}
               

int main() {
    ifstream inputFile("input.txt");
    if(!inputFile){
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    // Open output file
    ofstream outputFile("output_DSU_Path.txt");
    if(!outputFile){
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }
    
    int nro_test; inputFile >> nro_test;

    for (int i = 0; i < nro_test; i++)
    {
        Pu=0;
        Pv=0;
        inputFile >>n>>r>>w>>UTP>>FO;
        componentes = n;
        for(int j = 0; j < n; j++){
        int x,y;
        inputFile>>x>>y;
        loc.push_back({x, y});
        
        }
    auto start = chrono::high_resolution_clock::now();
    E = crear_grafo(loc);
    kruskal();
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputFile << duration.count() << endl;
    cout<<std::fixed << std::setprecision(3) << "Caso #"<< (i+1) << ": " << Pu << " " << Pv  << endl;
    loc.clear();
    }
    return 0;
}
