#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int main() {
    int x,y,z;
    cin>>x>>y>>z;
    vector<vector<int>> goku(x + 1);
    for (int i = 0; i < y; i++) {
        int u ,v;
        cin>>u>>v;
        goku[u].emplace_back(v);
        goku[v].emplace_back(u);
    }
    for (int i = 1; i <= x; i++) sort(goku[i].begin(), goku[i].end());
    for (int i = 1; i <= z; i++) {
        int m,n,w;
        cin>>m>>n>>w;
        if (m == 1) {
            if (goku[n].size() >= w) cout << goku[n][w - 1] << '\n';
            else cout << -1 << '\n';
        }
        if (m == 2) {
            cout << upper_bound(goku[n].begin(), goku[n].end(), w) - goku[n].begin() << '\n';

        }
    }
};