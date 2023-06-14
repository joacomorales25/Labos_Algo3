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

    int n, m; 

    while(true){

        cin >> n >> m;

        if(n == 0 && m == 0) break;

        vector<int> preferencias(n+1, 0);

        for(int i = 1; i <= n; i++){
            cin >> preferencias[i]; // les gusta prim o kruskal. Prim = 1, Kruskal = 0
        }

        vector<int> ady[n+1];

        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            ady[u].push_back(v);
            ady[v].push_back(u);
        }
        vector<int> grupoA;
        vector<int> grupoB;

        for(int i = 1; i <= n; i++){
            if(preferencias[i]){
                grupoA.push_back(i);
            }else{
                grupoB.push_back(i);
            }
        }

        int src = 0;
        int dst = n+1;

        vector<vector<int>> red(n+2);

        for(int i = 0; i < grupoA.size(); i++){
            red[src].push_back(grupoA[i]);
        }
        for(int i = 0; i < grupoA.size(); i++){
            for(int j = 0; j < ady[grupoA[i]].size(); j++){
                red[grupoA[i]].push_back(ady[grupoA[i]][j]);
            }
        }

        for(int i = 0; i < grupoB.size(); i++){
            for(int j = 0; j < ady[grupoB[i]].size(); j++){
                red[grupoB[i]].push_back(dst);
            }
        }

        capacity = vector<vector<int>>(n+2, vector<int>(n+2, 0));

        for(int i = 0; i < grupoB.size(); i++){
            capacity[grupoB[i]][dst] = 1;
        }

        for(int i = 0; i < grupoA.size(); i++){
            for(int j = 0; j < ady[grupoA[i]].size(); j++){
                capacity[grupoA[i]][ady[grupoA[i]][j]] = 1;
            }
        }

        for(int i = 0; i < grupoA.size(); i++){
            capacity[src][grupoA[i]] = 1;
        }

        adj = red;
        cout << maxflow(src, dst) << endl;



    }
}