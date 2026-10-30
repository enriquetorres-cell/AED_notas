#include <iostream>
#include <vector>
using namespace std;
bool mat[3001][3001];
int main() {
    int n , m;
    cin>>n>>m;
    vector<vector<int>>goku(n+1);
    vector<pair<int,int>> aristas;

    for (int i = 1; i <= m; i++) {
        int u ,v;
        cin>>u>>v;
        goku[u].push_back(v);
        goku[v].push_back(u);
        mat[u][v] = true;
        mat[v][u] = true;
        aristas.push_back(make_pair(u,v));
    }
    long long cont = 0;
    for (auto & e : aristas){
        int u = e.first;
        int v = e.second;
        int w ;
        for (auto m: goku[u]) {
            if (mat[v][m] == true) {
                cont ++;
            }
        }

    }
    cout << cont /3;
}