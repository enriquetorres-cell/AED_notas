#include<bits/stdc++.h>
using namespace::std;

vector<int> MultisourceBFS(vector<int> &src, int n, vector<vector<int>> &G) {
    vector<int> D(n + 1, -1);                    // CAMBIA: n + 1 casilleros, se usan 1..n
    queue<int> Q;
    for (auto &x : src) {
        D[x] = 0;
        Q.emplace(x);
    }
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int &v : G[u]) {
            if (D[v] != -1) continue;
            D[v] = D[u] + 1;
            Q.emplace(v);
        }
    }
    return D;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> special(k);
    for (int i = 0; i < k; ++i) {                // no cambia: i solo cuenta líneas
        cin >> special[i];                       // CAMBIA: sin --special[i]
    }
    vector<vector<int>> G(n + 1, vector<int>()); // CAMBIA: n + 1 casilleros
    for (int i = 0; i < m; ++i) {                // no cambia: i solo cuenta líneas
        int u, v;
        cin >> u >> v;                           // CAMBIA: sin --u; --v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    vector<int> dist = MultisourceBFS(special, n, G);
    for (int i = 1; i <= n; ++i) {               // CAMBIA: del pueblo 1 al n
        cout << dist[i] << " \n"[i == n];        // CAMBIA: el último ahora es i == n
    }
    return 0;
}