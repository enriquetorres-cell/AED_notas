#include <bits/stdc++.h>
using namespace std;
const int N = (int) 2e5 + 5;
vector<int> adj[N];
int n,m;

void dfs(int u, vector<bool>& vis, vector<int>& orden){
    vis[u] = true;
    orden.push_back(u);
    for(int& v : adj[u]){
        if(!vis[v]) dfs(v,vis,orden);
    }
}

int main(){
    cin>>n>>m;
    for(int i = 0 ; i < m ; i++){
        int u,v; cin>>u>>v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // ordeno los vecinos para ir siempre a la cueva de menor numero
    for(int i = 0 ; i < n ; i++) sort(adj[i].begin(),adj[i].end());
    vector<bool> vis(n,false);
    vector<int> orden;
    dfs(0,vis,orden);
    cout<<orden.size()<<"\n";
    for(int& x : orden) cout<<(x+1)<<" ";
    cout<<"\n";
    return 0;
}
