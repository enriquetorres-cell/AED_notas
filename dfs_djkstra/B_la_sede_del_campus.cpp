#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1005;
const ll INF = 1e18;
using i2 = pair<ll,ll>;
vector<i2> adj[N];
int n,m;

vector<ll> dijkstra(int s){
    vector<ll> d(n,INF);
    d[s] = 0;
    priority_queue<i2, vector<i2>, greater<i2>> pq;
    pq.push({0,s});
    while(!pq.empty()){
        auto [d_u,u] = pq.top();
        pq.pop();
        if(d_u != d[u]) continue;
        for(auto& [v,w] : adj[u]){
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
        adj[v].emplace_back(u,w);
    }
    // n es pequeno: corro Dijkstra desde cada edificio
    int mejor = 0;
    ll mejorSuma = INF;
    for(int s = 0 ; s < n ; s++){
        auto d = dijkstra(s);
        ll suma = 0;
        for(int v = 0 ; v < n ; v++) suma += d[v];
        if(suma < mejorSuma){ // estrictamente menor: en empate se queda el de menor numero
            mejorSuma = suma;
            mejor = s;
        }
    }
    cout<<(mejor+1)<<" "<<mejorSuma<<"\n";
    return 0;
}
