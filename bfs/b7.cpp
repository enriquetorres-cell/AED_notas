#include<bits/stdc++.h>
using namespace::std;

int BFS(string inicio) {
    string meta = "123450";
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    map<string, int> D;
    queue<string> Q;
    Q.emplace(inicio);
    D[inicio] = 0;
    while (not Q.empty()) {
        string u = Q.front(); Q.pop();
        if (u == meta) return D[u];
        int p = u.find('0');
        int x = p / 3, y = p % 3;
        for (int k = 0; k < 4; ++k) {
            int vx = x + dx[k];
            int vy = y + dy[k];
            if (vx < 0 or vy < 0 or vx >= 2 or vy >= 3) continue;
            string v = u;
            swap(v[p], v[vx * 3 + vy]);
            if (D.count(v)) continue;
            D[v] = D[u] + 1;
            Q.emplace(v);
        }
    }
    return -1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string inicio = "";
    for (int i = 0; i < 6; ++i) {
        int x;
        cin >> x;
        inicio += char('0' + x);
    }
    cout << BFS(inicio) << '\n';
    return 0;
}