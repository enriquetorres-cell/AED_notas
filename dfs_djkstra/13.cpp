#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    static const int N = 1e5 + 5;
    vector<int> adj[N];

    void dfs(int u,vector<bool>& vis){
        vis[u] = true;
        for(auto& v : adj[u]){
            if(!vis[v]) dfs(v,vis);
        }
    }

    int makeConnected(int n, vector<vector<int>>& edges) {
        if(edges.size() < n-1) return -1;
        for(auto& e : edges){
            int u = e[0] , v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool> vis(n,false);
        int cnt = 0;
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){
                cnt++;
                dfs(i,vis);
            }
        }
        return cnt - 1;
    }
};

int main(){
    return 0;
}