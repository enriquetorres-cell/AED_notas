#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = (int) 2e5 + 5;
int n,m;

using i2 = pair<ll,ll>;

vector<i2> adj[N];

const ll INF = 1e18;


vector<ll> dijkstra(int s){
    vector<ll> dis(n,INF);
    dis[s] = 0;
    priority_queue<i2, vector<i2> , greater<i2>> pq;
    pq.push({0,s});
    while(!pq.empty()){
        auto [d_u, u] = pq.top();
        pq.pop();
        if(d_u != dis[u]) continue;
        for(auto& [v,w] : adj[u]){
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                pq.push({dis[v] , v});
            }
        }
    }
    return dis;
}

void slv(){
    vector<int> A(n);
    for(int i = 0 ; i < n ; i++) cin>>A[i];
    for(int i = 0 ; i < m ; i++){
        int u,v; cin>>u>>v;
        ll w; cin>>w;
        u--; v--;
        adj[u].emplace_back(v,A[u] + w);
        adj[v].emplace_back(u,A[v] + w);
    }
    auto d = dijkstra(0);
    for(int i = 1 ; i < n ; i++) cout<<(d[i] + A[i])<<" ";
    cout<<"\n";
}


int main() {
	while(cin >> n >> m) {
        slv();
        for(int i = 0 ; i < n ; i++) adj[i].clear();
    }
    return 0;
}
