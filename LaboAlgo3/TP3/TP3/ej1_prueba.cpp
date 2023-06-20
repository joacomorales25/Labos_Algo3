
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <math.h>
#include <utility>
#include <set>
#include <chrono>
#include <map>
#include <fstream>

using namespace std;

typedef pair<int, int> infoDist;       //el primer elemento corresponde a la distancia computada. El segundo corresponde al nodo.

typedef pair<pair<int,int>, int> edge; //el primer elemento corresponde a la arista. El segundo corresponde al peso.

struct arista{
    int u;
    int v;
    int peso;
};

const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vector<bool> u(n, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}

int main(){
    ifstream inputFile("test_n2.txt");

    ofstream outputFile("tiempos_n_2_densos.txt");

    int numCasos; inputFile >> numCasos;

    map<int,chrono::microseconds> promedios;

    while(numCasos--){
        int nodos, aristas, k, origen, destino;
        inputFile >> nodos >> aristas >> k >> origen >> destino;

        vector<vector<pair<int,int>>> ady(nodos+1);
        vector<vector<pair<int,int>>> ady_inv(nodos+1);

        adj = vector<vector<pair<int, int>>>(nodos+1);

        for(int i = 0; i < aristas; i++){
            int u, v, peso;
            inputFile >> u >> v >> peso;
            adj[u].push_back(make_pair(v, peso));
            ady_inv[v].push_back(make_pair(u, peso));

        }

        vector<edge> aristas_especiales;

        for(int i = 0; i < k; i++){
            int u, v, peso;
            inputFile >> u >> v >> peso;
            aristas_especiales.push_back(make_pair(make_pair(u,v), peso));
        }

        for(int i = 0; i < 40;i++){
        vector<int> dist_src(nodos+1, INF);
        vector<int> dist_dst(nodos+1, INF);

        vector<int> predecesor(nodos+1, -1);

        
        auto start = chrono::steady_clock::now();
        dijkstra(origen, dist_src, predecesor);
        adj = ady_inv;
        dijkstra(destino, dist_dst, predecesor);
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        if(promedios.count(nodos)){
            chrono::microseconds tiempo = promedios[nodos];
            tiempo += duration;
        }else{
            promedios.insert(make_pair(nodos,duration));
        }

        int minimo = INF;

        for(auto& edge: aristas_especiales){
            int u = edge.first.first;
            int v = edge.first.second;
            int peso = edge.second;

            int dist_normal = dist_src[u] + peso + dist_dst[v];
            int dist_inversa = dist_src[v] + peso + dist_dst[u];

            minimo = min(minimo, min(dist_src[destino], min(dist_normal, dist_inversa)));
            // me quedo con el valor anterior, o considero el camino normal, o el camino con una arista especial normal o invertida. 
        }

        minimo == INF ? cout << -1 << endl : cout << minimo << endl;
        }
        
    }

    for(auto& keys : promedios){

        chrono::microseconds res = keys.second/40;

        outputFile << keys.first << " " << res.count() << endl;

    }
}