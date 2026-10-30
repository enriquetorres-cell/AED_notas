#include<iostream>
#include <vector>
using namespace std;
int main() {
    int  n,m,q;
    cin >> n>> m >> q;
    vector<vector<int>> goku(n+1);
    for (int i = 0; i < m; i++) {
        int a , b;
        cin >> a >> b;
        goku[a].emplace_back(b);
        goku[b].emplace_back(a);
    }
    vector<bool> g(n+1);
    for (int i = 0; i < q; i++) {
        int cont = 0;
        int u ,v;
        cin >> u >> v;
        for (int x : goku[u]) {
            g[x] = true;
        }
        for (int m: goku[v]) {
            if (g[m] == true) {
                cont ++;
            }
        }
        cout << cont << '\n';
        for (int x : goku[u]) {
            g[x] = false;
        }
    }

}