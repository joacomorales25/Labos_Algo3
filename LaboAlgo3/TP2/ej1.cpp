#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <map>
using namespace std;

#define Grafo vector<vector<int>>

enum estados{NO_VISITADO, VISITADO, EN_PROCESO};
vector<int> estado;
//DETECCIÓN DE PUENTES
int componente = 0;
vector<int> elems;
vector<bool> visitados;
map<pair<int, int>, bool> puentes;

void dfs_visit(const vector<vector<int>> &ady, int u, vector<int> &parent, vector<int> &discTime, int &time, vector<int> &color, vector<bool> &bridgeParent){
    time = time + 1;
    discTime[u] = time;
    color[u] = 1;
    for (auto v : ady[u]){
        if (color[v] == 0){
            parent[v] = u;
            dfs_visit(ady, v, parent, discTime, time, color, bridgeParent);
        }

    }
    color[u] = 2;
}

void DFS(const vector<vector<int>> &ady, vector<int> &parent, vector<int> &discTime, vector<int> &color, vector<bool> &bridgeParent){
    int time = 0;
    for (int u = 1; u < ady.size(); u++){
        if (color[u] == 0){
            parent[u] = u;
            componente++;
            dfs_visit(ady, u, parent, discTime, time, color, bridgeParent);
        }
    }
}



int detectarPuentes(const std::vector<std::vector<int>> &ady, int u, std::vector<int> &parent, std::vector<int> &discTime, std::vector<bool> &bridgeParent){
    int cantidad = 0;
    for (auto v : ady[u]){
        if (parent[v] == u){    //por cada tree-edge hacia abajo le sumamos la cantidad de back-edges que lo cubren.
            cantidad += detectarPuentes(ady, v, parent, discTime, bridgeParent);
        } else {
            if (discTime[u] > discTime[v] && parent[u] != v){   //sumamos los back-edges que salen de u y van hacia arriba.
                cantidad++;
            }
            if (discTime[u] < discTime[v]){     //restamos los back-edges que llegan a u desde abajo.
                cantidad--;
            }
        }
    }
    if (cantidad == 0 && parent[u] != u)    //si no hay back-edges que cubran la tree-edge entre u y su padre, entonces es puente. Si u es raíz, no vale.
        puentes[make_pair(u, parent[u])] = true;
        puentes[make_pair(parent[u], u)] = true;

    return cantidad;
}

void dfs(int u, Grafo& g){
    estado[u] = EN_PROCESO;
    elems[componente]++;
    for(int v : g[u]){
        if(estado[v] == NO_VISITADO && (!puentes[make_pair(u, v)] || !puentes[make_pair(v, u)])){
            dfs(v, g);
        }
    }
    estado[u] = VISITADO;
}



int main(){

    int nodos, aristas; cin >> nodos >> aristas;

    Grafo g(nodos+1);

    for(int i = 0; i < aristas; i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> parent(nodos+1, -1);
    vector<int> discTime(nodos+1, -1);
    vector<int> color(nodos+1, 0);
    vector<bool> bridgeParent(nodos+1, false);
    elems = vector<int>(nodos+1, 0);
    DFS(g, parent, discTime, color, bridgeParent);      //corremos DFS para obtener la info necesaria para detectar puentes

    for(int i = 1; i <= nodos; i++){
        detectarPuentes(g, i, parent, discTime, bridgeParent);
    }

    
        //corremos DFS para obtener la info necesaria para detectar puentes
    int componentes = 0;
    estado = vector<int>(nodos+1, NO_VISITADO);
    for(int i = 1; i <= nodos; i++){
        if(estado[i] == NO_VISITADO){
            dfs(i, g);
        }
    }
    long long formas_de_ganar = 0;

    for(int i = 0; i < elems.size(); i++){
        
        formas_de_ganar += (elems[i]*(elems[i]-1))/2;
        
    }
    
    long long formas_de_jugar = (nodos*(nodos-1))/2;
    double prob_ganar = (double)formas_de_ganar/(double)formas_de_jugar;
    cout << fixed << setprecision(5) << 1-prob_ganar << endl;
}





