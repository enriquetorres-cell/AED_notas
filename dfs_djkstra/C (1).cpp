#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = (int) 2e5 + 5;
using i2 = pair<int,ll>;
vector<i2> adj[N];
int n; 

void dfs(int u, int p , ll d_u , vector<ll>& d){
    d[u] = d_u;
    for(auto& [v,w] : adj[u]){
        if(v == p) continue;
        dfs(v,u,d_u + w,d);
    }
}

void slv(){
    for(int i = 0 ; i < n-1 ; i++){
        int u,v; cin>>u>>v;
        u--; v--;
        ll w; cin>>w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<ll> d0(n);
    dfs(0, -1 , 0 , d0);
    int s = max_element(d0.begin(),d0.end()) - d0.begin();
    vector<ll> ds(n);
    dfs(s,-1,0,ds);
    cout<<*max_element(ds.begin(),ds.end())<<"\n";
}

int main() {
    while(cin >> n) {
        slv();
        for(int i = 0 ; i < n ; i++) adj[i].clear();
    }
    return 0;
}
