#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <math.h>
#include <fstream>
#include <chrono>
#include <map>
#include <utility>
#include <set>
#define INF 10000000

using namespace std;

typedef pair<int, int> infoDist;       //el primer elemento corresponde a la distancia computada. El segundo corresponde al nodo.

typedef pair<pair<int,int>, int> edge; //el primer elemento corresponde a la arista. El segundo corresponde al peso.

struct arista{
    int u;
    int v;
    int peso;
};

void Dijkstra(const vector<vector<pair<int,int>>> &ady, int s, vector<int> &dist){
    dist[s] = 0;
    priority_queue<infoDist , vector<infoDist>, greater<infoDist>> Q;

    for (int v = 0; v < ady.size(); v++)
        Q.push(make_pair(dist[v], v));

    while(!Q.empty()){
        infoDist infoU = Q.top();
        Q.pop();
        int u = infoU.second;
        for (auto edge : ady[u]){
            int v = edge.first;
            int peso = edge.second;
            if (dist[u] < INF && dist[v] > dist[u] + peso){
                dist[v] = dist[u] + peso;
                Q.push(make_pair(dist[v], v));
            }
        }
    }
}

int main(){

    ifstream inputFile("test_n2.txt");

    ofstream outputFile("tiempos_log_n_densos.txt");

    map<int,chrono::microseconds> promedios;

    if (!outputFile){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int numCasos; inputFile >> numCasos;

    while(numCasos--){
        int nodos, aristas, k, origen, destino;
        inputFile >> nodos >> aristas >> k >> origen >> destino;

        vector<vector<pair<int,int>>> ady(nodos+1);
        vector<vector<pair<int,int>>> ady_inv(nodos+1);

        for(int i = 0; i < aristas; i++){
            int u, v, peso;
            inputFile >> u >> v >> peso;
            ady[u].push_back(make_pair(v, peso));
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
        auto start = chrono::steady_clock::now();
        Dijkstra(ady, origen, dist_src);
        Dijkstra(ady_inv, destino, dist_dst);
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