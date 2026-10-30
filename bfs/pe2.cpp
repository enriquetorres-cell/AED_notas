#include<bits/stdc++.h>
using namespace::std;

int BFS(int N, int Dado, vector<int> &salto) {
    vector<int> D(N + 1, -1);
    queue<int> Q;
    Q.emplace(1);
    D[1] = 0;
    while (not Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int d = 1; d <= Dado; ++d) {
            int y = x + d;
            if (y > N) break;
            if (salto[y] != 0) y = salto[y];
            if (D[y] != -1) continue;
            D[y] = D[x] + 1;
            Q.emplace(y);
        }
    }
    return D[N];
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int N, Dado, k;
    cin >> N >> Dado >> k;
    vector<int> salto(N + 1, 0);
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        salto[a] = b;
    }
    cout << BFS(N, Dado, salto) << '\n';
    return 0;
}