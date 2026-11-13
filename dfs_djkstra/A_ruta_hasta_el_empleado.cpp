#include <bits/stdc++.h>
using namespace std;
const int N = (int) 2e5 + 5;
vector<int> adj[N];
int n,t;

void dfs(int u, int p, vector<int>& padre){
    padre[u] = p;
    for(int& v : adj[u]){
        if(v == p) continue;
        dfs(v,u,padre);
    }
}

int main(){
    cin>>n>>t;
    for(int i = 0 ; i < n-1 ; i++){
        int u,v; cin>>u>>v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> padre(n,-1);
    dfs(0,-1,padre);
    // subo desde t hasta el director usando padre
    vector<int> camino;
    int x = t-1;
    while(x != -1){
        camino.push_back(x);
        x = padre[x];
    }
    reverse(camino.begin(),camino.end());
    cout<<camino.size()<<"\n";
    for(int& c : camino) cout<<(c+1)<<" ";
    cout<<"\n";
    return 0;
}
