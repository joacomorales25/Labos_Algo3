#include <iostream>
#include <vector>

using namespace std;

#define Grafo vector<vector<int>>

enum{NO_VISITADO, VISITADO, EN_PROCESO};

void dfs(Grafo &g, int u, vector<int> &visitado){

    visitado[u] = EN_PROCESO;

    for(int v : g[u]){
        if(visitado[v] == NO_VISITADO){
            dfs(g, v, visitado);
        }
    }
    visitado[u] = VISITADO;
}

int main(){

    int nodos, aristas; cin >> nodos >> aristas;

    Grafo g(nodos+1);
    vector<int> visitado(nodos+1, 0);
    for (int i = 0; i < aristas; i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }
    int componentes = 0;
    vector<int> menores;
    for(int i = 1; i <= nodos; i++){

        if(visitado[i] == NO_VISITADO){
            menores.push_back(i);
            componentes++;
            dfs(g, i, visitado);
        }
    }
    cout << componentes << endl;

    for(int i = 0; i < menores.size(); i++){
        cout << menores[i];
        if(i != menores.size()-1)
            cout << " ";
    }
    cout << endl;


}