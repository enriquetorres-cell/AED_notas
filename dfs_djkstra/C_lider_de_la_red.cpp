#include <bits/stdc++.h>
using namespace std;
const int N = (int) 2e5 + 5;
vector<int> adj[N], radj[N];
int n,m;

int dfs(int u, vector<int> g[], vector<bool>& vis){
    vis[u] = true;
    int cnt = 1;
    for(int& v : g[u]){
        if(!vis[v]) cnt += dfs(v,g,vis);
    }
    return cnt;
}

int main(){
    cin>>n>>m;
    for(int i = 0 ; i < m ; i++){
        int u,v; cin>>u>>v;
        u--; v--;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    // 1) la ultima raiz desde la que se lanza un DFS es el unico candidato a lider
    vector<bool> vis(n,false);
    int cand = 0;
    for(int i = 0 ; i < n ; i++){
        if(!vis[i]){
            cand = i;
            dfs(i,adj,vis);
        }
    }
    // 2) verifico que el candidato llegue a todos
    vis.assign(n,false);
    if(dfs(cand,adj,vis) != n){
        cout<<0<<"\n";
        return 0;
    }
    // 3) lideres = los que llegan al candidato (DFS en el grafo invertido)
    vis.assign(n,false);
    cout<<dfs(cand,radj,vis)<<"\n";
    return 0;
}
