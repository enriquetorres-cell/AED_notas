#include<bits/stdc++.h>
using namespace::std;

bool BFS(int s, vector<vector<int>> &G, vector<bool> &vis) {
    queue<int> Q;
    Q.emplace(s);
    vis[s] = true;
    int nodos = 0, grados = 0;
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        nodos++;
        grados += G[u].size();
        for (int &v : G[u]) {
            if (vis[v]) continue;
            vis[v] = true;
            Q.emplace(v);
        }
    }
    int aristas = grados / 2;
    return aristas <= nodos;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    vector<bool> vis(n, false);
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        if (not BFS(i, G, vis)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "SI\n";
    return 0;
}