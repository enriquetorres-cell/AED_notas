#include <iostream>
#include <vector>
using namespace std;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int main() {
    int x , y;
    cin >> x >> y;

    vector<string> goku(x);
    vector<int> contador(5);

    for (int i = 0; i < x; i++) {
        cin >> goku[i];
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (goku[i][j] == '#') {
                int d = 0;
                for (int g = 0; g < 4; g++) {
                    int nx = i + dx[g];
                    int ny = j + dy[g];
                    if (nx < 0 || ny < 0 || nx >= x || ny >= y) continue;
                    if (goku[nx][ny] == '#') {
                        d++;
                    }
                }
                contador[d]++;
            }
            if (goku[i][j] == '.') {continue;}
        }
    }
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += (4-i)* contador[i];
    }
    cout << sum << " ";
    for (int i = 0; i < 5; i++) {
        cout << contador[i] << " ";
    }
}