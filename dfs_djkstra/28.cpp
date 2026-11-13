#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = (int) 2e5 + 5;
int n;
ll a,b,c;

using i2 = pair<ll,ll>;


const ll INF = (ll) 1e18;

vector<ll> Dijkstra(int s, vector<vector<ll>>& W){
    vector<ll> d(n,INF);
    d[s] = 0;
    vector<bool> vis(n,false);
    int iter = n;
    while(iter--){
        //u el nodo con menor distancia que no ha sido visitado
        
        int u = -1;
        ll d_u = INF;
        for(int i = 0 ; i < n ; i++){
            if(vis[i]) continue;
            if(d[i] < d_u){
                u = i;
                d_u = d[i];
            }
        }

        assert(u != -1);

        vis[u] = true;

        for(int v = 0 ; v < n ; v++){
            ll wuv = W[u][v];
            if(d[v] > d[u] + wuv){
                d[v] = d[u] + wuv;
            }
        }
    }
    return d;
}


void slv(){
    vector<vector<ll>> Dc(n,vector<ll>(n)),Dt(n,vector<ll>(n));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            ll x; cin >> x;
            Dc[i][j] = a*x;
            Dt[i][j] = b*x + c;
        }
    }
    auto d1 = Dijkstra(0,Dc);
    auto dn = Dijkstra(n-1,Dt);
    ll ans = INF;
    for(int u = 0 ; u < n ; u++){
        ans = min(ans , d1[u] + dn[u]);
    }
    cout<<ans<<"\n";
}


int main() {
	while(cin >> n >> a >> b >> c) {
        slv();
    }
    return 0;
}
