#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = (int) 2e5 + 5;
const ll INF = 1e18;
using i2 = pair<ll,ll>;
vector<i2> adj[N], radj[N]; // grafo normal y grafo invertido
int n,m;

vector<ll> dijkstra(int s, vector<i2> g[]){
    vector<ll> d(n,INF);
    d[s] = 0;
    priority_queue<i2, vector<i2>, greater<i2>> pq;
    pq.push({0,s});
    while(!pq.empty()){
        auto [d_u,u] = pq.top();
        pq.pop();
        if(d_u != d[u]) continue;
        for(auto& [v,w] : g[u]){
            if(d[v] > d[u] + w){
                d[v] = d[u] + w;
                pq.push({d[v],v});
            }
        }
    }
    return d;
}

int main(){
    cin>>n>>m;
    for(int i = 0 ; i < m ; i++){
        int u,v; ll w; cin>>u>>v>>w;
        u--; v--;
        adj[u].emplace_back(v,w);
        radj[v].emplace_back(u,w); // invertida: sirve para el regreso v -> 1
    }
    auto ida = dijkstra(0,adj);
    auto vuelta = dijkstra(0,radj);
    int cnt = 0;
    ll total = 0;
    for(int v = 0 ; v < n ; v++){
        if(ida[v] < INF && vuelta[v] < INF){
            cnt++;
            total += ida[v] + vuelta[v];
        }
    }
    cout<<cnt<<" "<<total<<"\n";
    return 0;
}
