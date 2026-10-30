#include<bits/stdc++.h>
using namespace::std;

int BFS(int s, int t, int w, vector<bool> &prohibido) {
    int total = 1;
    for (int i = 0; i < w; ++i) total *= 10;
    if (prohibido[s]) return -1;
    vector<int> D(total, -1);
    queue<int> Q;
    Q.emplace(s);
    D[s] = 0;
    while (not Q.empty()) {
        int x = Q.front(); Q.pop();
        int p = 1;
        for (int i = 0; i < w; ++i) {
            int dig = (x / p) % 10;
            vector<int> nuevos = {(dig + 1) % 10, (dig + 9) % 10};
            for (int &nd : nuevos) {
                int y = x - dig * p + nd * p;
                if (prohibido[y]) continue;
                if (D[y] != -1) continue;
                D[y] = D[x] + 1;
                Q.emplace(y);
            }
            p *= 10;
        }
    }
    return D[t];
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int w;
    cin >> w;
    string s, t;
    cin >> s >> t;
    int k;
    cin >> k;
    int total = 1;
    for (int i = 0; i < w; ++i) total *= 10;
    vector<bool> prohibido(total, false);
    for (int i = 0; i < k; ++i) {
        string c;
        cin >> c;
        prohibido[stoi(c)] = true;
    }
    cout << BFS(stoi(s), stoi(t), w, prohibido) << '\n';
    return 0;
}