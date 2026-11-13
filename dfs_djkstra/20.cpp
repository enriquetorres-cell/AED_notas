#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = (int) 2e5 + 5;
vector<int> adj[N];
int n,m;

void dfs(int u, int c, vector<int>& color){
    color[u] = c;
    for(int& v : adj[u]){
        if(color[v] == -1) 
            dfs(v,1-c,color);
    }
}

void slv(){
    for(int i = 0 ; i < n-1 ; i++){
        int u,v; cin>>u>>v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> color(n,-1);
    dfs(0,0,color);
    int x = 0 , y = 0;
    for(int i = 0 ; i < n ; i++){
        if(color[i] == 0) x++;
        else y++;
    }
    ll ans = (ll) x * y  - (n-1);
    cout<<ans<<"\n";
}

int main() {
    while(cin>>n){
        slv();
        for(int i = 0 ; i < n ; i++) adj[i].clear();
    }
    return 0;
}