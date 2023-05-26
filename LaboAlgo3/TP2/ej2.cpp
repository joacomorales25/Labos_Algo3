#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define Grafo vector<vector<int>>

enum{NO_VISITADO, VISITADO, EN_PROCESO};

void BFS(Grafo &g, int u, vector<int> &visitado){

    queue<int> q;
    q.push(u);
    visitado[u] = EN_PROCESO;

    while(!q.empty()){
        int v = q.front(); q.pop();
        for(int w : g[v]){
            if(visitado[w] == NO_VISITADO){
                visitado[w] = EN_PROCESO;
                q.push(w);
            }
        }
        visitado[v] = VISITADO;
    }
}

int main(){

    int nodos, aristas; cin >> nodos >> aristas;

    Grafo g(nodos+1);
    vector<int> d_in(nodos+1, 0);
    vector<int> d_out(nodos+1, 0);

    vector<int> visitado(nodos+1, 0);
    for (int i = 0; i < aristas; i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        d_in[v]++;
        d_out[u]++;
    }
    int src = 1;
    for(int i = 1; i <= nodos; i++){
        if(d_in[i] == 0){ // los que si o si van a entrar primero son los que tienen grado de entrada 0, i.e, nadie los tira.
            src = i;
        }
    }
    vector<int> res;
    BFS(g, src, visitado);
    res.push_back(src);
    int componentes = 1;
    for (int i = 1; i <= nodos; i++){
        if(visitado[i] == NO_VISITADO && (d_out[i] > 0 || (d_in[i] == 0 && d_out[i] == 0))){ // me fijo de agarrar los que aun no haya visitado
            // que tengan grado de salida mayor a 0, o sean noditos solos.
            componentes++;
            res.push_back(i);
            BFS(g, i, visitado);
            
        }
    }

    sort(res.begin(), res.end());

    cout << componentes << endl;
    for(int i : res){
        cout << i << " ";
    }
    cout << endl;

    return 0;

}

