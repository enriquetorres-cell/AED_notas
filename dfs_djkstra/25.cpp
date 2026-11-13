#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    using ll = long long;
    ll INF = 1e18;
    ll mod = 1e9 + 7;
    using i2 = pair<int,ll>;
    int countPaths(int n, vector<vector<int>>& edges) {
        vector<vector<i2>> adj(n,vector<i2>());
        for(auto& e : edges){
            int u = e[0] , v = e[1] , w = e[2];
            adj[u].emplace_back(v,w);
            adj[v].emplace_back(u,w);
        }
        vector<ll> d(n,INF);
        vector<ll> cnt(n,0);
        vector<bool> vis(n,false);
        d[0] = 0;
        cnt[0] = 1;
        for(int i = 0 ; i < n ; i++){
            int u = -1;
            
            ll d_u = INF;
            for(int j = 0 ; j < n ; j++){
                if(vis[j]) continue;
                if(d[j] < d_u){
                    u = j;
                    d_u = d[j];
                }
            }
            vis[u] = true;
            // u - nodo con minima distancia entre los no visitados
            // una visitado un nodo ya esta definida su distancia
            if( u == -1) break;
            for(auto& [v,w] : adj[u]){
                if(d[v] > d[u] + w){
                    d[v] = d[u] + w;
                    cnt[v] = cnt[u];
                }
                else if (d[v] == d[u] + w){
                    cnt[v] = (cnt[v] + cnt[u]) % mod;
                }
            }
        }
        return cnt[n-1];
    }
};

int main(){
    return 0;
}