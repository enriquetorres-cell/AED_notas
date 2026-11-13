#include <bits/stdc++.h>
using namespace std;
 
const int N = (int) 2e5 + 5;
vector<int> adj[N];
int n;
 
 
 
void dfs(int u, vector<int>& topo , vector<bool>& vis){
    vis[u] = true;
    for(auto& v : adj[u]){
        if(!vis[v]) dfs(v,topo,vis);
    }
    topo.push_back(u);
}
 
void slv(){
    cin>>n;
    for(int i = 0 ; i < n-1 ; i++){
        int u,v,x,y; cin>>u>>v>>x>>y;
        u--; v--;
        if(x > y) adj[v].push_back(u); // v a u
        else adj[u].push_back(v); // u a v
    }
    vector<int> topo;
    vector<bool> vis(n,false);
    for(int i = 0 ; i < n ; i++){
        if(!vis[i]) dfs(i,topo,vis);
    }
    reverse(topo.begin(),topo.end());
    vector<int> p(n);
    for(int i = 0 ; i < n ; i++){
        p[topo[i]] = i;
    }
 
    for(int i = 0 ; i < n ; i++) cout<<(p[i] + 1)<<" ";
    cout<<"\n";
}
 
int main() {
    int t = 1; cin>>t;
    while(t--){
        slv();
        for(int i = 0 ; i < n ; i++) adj[i].clear();
    }
    return 0;
}