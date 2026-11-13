#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = (int) 2e5 + 5;
using i2 = pair<int,ll>;
vector<i2> adj[N];
int n;

void dfs(int u, int p, ll d_u, vector<ll>& d){
    d[u] = d_u;
    for(auto& [v,w] : adj[u]){
        if(v == p) continue;
        dfs(v,u,d_u + w,d);
    }
}

int main(){
    cin>>n;
    for(int i = 0 ; i < n-1 ; i++){
        int u,v; ll w; cin>>u>>v>>w;
        u--; v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    // 1er DFS: el mas lejano desde 0 es un extremo del diametro
    vector<ll> d0(n);
    dfs(0,-1,0,d0);
    int s = max_element(d0.begin(),d0.end()) - d0.begin();
    // 2do DFS desde ese extremo: la mayor distancia es el diametro
    vector<ll> ds(n);
    dfs(s,-1,0,ds);
    cout<<*max_element(ds.begin(),ds.end())<<"\n";
    return 0;
}
