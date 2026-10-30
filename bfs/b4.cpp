#include<bits/stdc++.h>
using namespace::std;

const long long MOD = 1e9 + 7;                       // CAMBIA: la respuesta va módulo 10^9+7

bool BFS(int s, vector<vector<int>> &G, vector<int> &D) {   // CAMBIA: una fuente, D viene del main, devuelve bool
    queue<int> Q;
    Q.emplace(s);
    D[s] = 0;                                        // CAMBIA: 0 = rojo (el primero del grupo)
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int &v : G[u]) {
            if (D[v] == -1) {                        // CAMBIA: sin pintar -> se pinta
                D[v] = 1 - D[u];                     // CAMBIA: color contrario (0 <-> 1)
                Q.emplace(v);
            } else if (D[v] == D[u]) {               // CAMBIA: rivales con el mismo color
                return false;                        // CAMBIA: imposible
            }
        }
    }
    return true;                                     // CAMBIA: el grupo se pintó sin conflicto
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;                                   // CAMBIA: ya no hay k
    vector<vector<int>> G(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    vector<int> D(n, -1);                            // CAMBIA: D = color, -1 sin pintar
    long long ans = 1;                               // CAMBIA: contador de formas
    for (int i = 0; i < n; ++i) {                    // CAMBIA: un BFS por cada grupo
        if (D[i] != -1) continue;                    // ya está en un grupo pintado
        if (not BFS(i, G, D)) {
            cout << "NO\n";
            return 0;
        }
        ans = ans * 2 % MOD;                         // CAMBIA: cada grupo da 2 formas
    }
    cout << "SI " << ans << '\n'
    return 0;
}