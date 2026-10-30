#include<bits/stdc++.h>
using namespace::std;

int BFS(int inicio, int n, int m) {
    vector<int> dx = {0, 1, -1, 0, 0};
    vector<int> dy = {0, 0, 0, 1, -1};
    int total = 1 << (n * m);
    vector<int> D(total, -1);
    queue<int> Q;
    Q.emplace(inicio);
    D[inicio] = 0;
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        if (u == 0) return D[u];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int v = u;
                for (int k = 0; k < 5; ++k) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x < 0 or y < 0 or x >= n or y >= m) continue;
                    v ^= (1 << (x * m + y));
                }
                if (D[v] != -1) continue;
                D[v] = D[u] + 1;
                Q.emplace(v);
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int inicio = 0;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            if (s[j] == '1') inicio |= (1 << (i * m + j));
        }
    }
    cout << BFS(inicio, n, m) << '\n';
    return 0;
}