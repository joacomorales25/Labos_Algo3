#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(true){

        int nodos, m; cin >> nodos >> m;

        if(nodos == 0 && m == 0) break;

        n = nodos;

        vector<int> preferencias(nodos+1, 0);

        for(int i = 1; i <= nodos; i++){
            cin >> preferencias[i]; // les gusta prim o kruskal. Prim = 1, Kruskal = 0
        }

        adj = vector<vector<int>>(nodos+2);
        capacity = vector<vector<int>>(nodos+2, vector<int>(nodos+2,0));

        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> grupoA;
        vector<int> grupoB;

        for(int i = 1; i <= nodos; i++){
            if(preferencias[i]){
                grupoA.push_back(i);
            }else{
                grupoB.push_back(i);
            }
        }

        int src = 0;
        int dst = nodos+1;

        for(auto& elem : grupoA){

            adj[src].push_back(elem);
            capacity[src][elem] = 1;

        }

        for(auto& elem : grupoB){

            adj[elem].push_back(dst);
            capacity[elem][dst] = 1;
        }
        
        for(int i = 1; i <= nodos;i++){
            for(auto& vecinos: adj[i]){

                capacity[i][vecinos] = 1;
                capacity[vecinos][i] = 1;
            }
        }

        cout << maxflow(src, dst) << endl;

        adj.clear();
        capacity.clear();
        grupoA.clear();
        grupoB.clear();
        preferencias.clear();
    }
}