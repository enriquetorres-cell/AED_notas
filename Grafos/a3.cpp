#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int main() {
    int n , m;
    cin >> n >> m;
    vector<int>g(n+1,0);
    unordered_set<long long> goku;
    vector<pair<int,int>> y;
    int cont = 0;
    for (int i = 0; i < m; i++) {
        int u , v;
        cin >> u >> v;
        g[v] ++;
        y.emplace_back(u,v);
        goku.emplace(1ll*u*(n+1)+v);

    }
    int parejas = 0;
    for (auto &a : y) {
        int u ,v;
        tie(u,v) =a;
        if (goku.find(1ll*v*(n+1)+u) != goku.end()) {
            parejas++;
        }
    }
    int goat = 1;

    for (int i = 2 ; i <= n; i++) {
        if (g[i] > g[goat]) {
            goat = i;
        }
    }
    cout << parejas/2 <<" "<< goat << " " <<g[goat]<< endl;
}