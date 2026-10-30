#include<bits/stdc++.h>
using namespace::std;

vector<int> MultisourceBFS(vector<int> &src, int n, vector<vector<int>> &G) {   // CAMBIA: recibe hospitales y grafo, devuelve todo D
    vector<int> D(n, -1);                     // CAMBIA: 1D, un valor por pueblo
    queue<int> Q;                             // CAMBIA: la cola guarda un int
    for (auto &x : src) {                     // CAMBIA: varias fuentes
        D[x] = 0;                             // CAMBIA
        Q.emplace(x);                         // CAMBIA
    }
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();           // CAMBIA: sin tie, solo un número
        for (int &v : G[u]) {                 // CAMBIA: vecinos desde G[u], sin dx/dy
            if (D[v] != -1) continue;         // solo queda el filtro de visitada
            D[v] = D[u] + 1;
            Q.emplace(v);
        }
    }
    return D;                                 // CAMBIA: devuelve el vector completo
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;                       // CAMBIA: ahora son 3 números
    vector<int> special(k);                   // CAMBIA: lista de hospitales
    for (int i = 0; i < k; ++i) {
        cin >> special[i];
        --special[i];                         // CAMBIA: pasar a 0-indexado
    }
    vector<vector<int>> G(n, vector<int>());  // CAMBIA: lista de adyacencia
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;                             // CAMBIA: 0-indexado
        G[u].emplace_back(v);                 // CAMBIA: camino bidireccional,
        G[v].emplace_back(u);                 //         se agrega en ambos sentidos
    }
    vector<int> dist = MultisourceBFS(special, n, G);
    for (int i = 0; i < n; ++i) {             // CAMBIA: se imprimen los n valores
        cout << dist[i] << " \n"[i + 1 == n];
    }
    return 0;
}