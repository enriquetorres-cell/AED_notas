#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int main() {
    int x,y,z;
    cin>>x>>y>>z;
    map<pair<int,int>, int>goku;
    for (int i = 0; i < y; i++) {
        int u ,v;
        cin>>u>>v;

        if (goku.count({v,u})) {
            goku[{v,u}] ++;
        }
        else {
            goku[{u,v}] ++;
        }
    }
    for (int i = 0 ; i < z; i++) {
        int u ,v;
        cin>>u>>v;
        if (goku.count({u,v})) {
            cout << goku[{u,v}] << '\n';
        }
        else if (goku.count({v,u})) {
            cout << goku[{v,u}] << '\n';
        }
        else {
            cout << 0 << endl;
        }
    }
}

