    #include <iostream>
    #include <vector>
    using namespace std;
    const int dx[] = {1,-1,0,0};
    const int dy[] = {0,0,1,-1};
    int main() {
        int n , m;
        cin >> n >> m;
        vector<int> deg(n+1,0);

        for (int i = 0; i < m; i++) {
            int u,v;
            cin >> u >> v;
            deg[u]++;
            deg[v]++;
        }
        int cont = 0;
        for (int i = 1; i <=n; i++) {
            if (deg[i] % 2 == 1) {
                cont++;
            }
        }
        if (cont == 0) {
            cout << "CIRCUITO"<< endl;
        }
        if (cont == 2) {
            cout << "CAMINO"<< endl;
        }
        if (cont > 2) {
            cout  << "IMPOSIBLE"<< endl;
        }
    }