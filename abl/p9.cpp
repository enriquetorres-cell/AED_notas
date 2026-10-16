#include <bits/stdc++.h>
using namespace std;

long long potencia(long long a, int n) {
    if (n == 0) return 1;
    long long h = potencia(a, n / 2);
    return (n % 2 == 0) ? h * h : h * h * a;
}

int n;
vector<bool> elegido, usado;
vector<int> p;

void subconjuntos(int i) {
    if (i == n + 1) {
        cout << "{ ";
        for (int k = 1; k <= n; ++k) if (elegido[k]) cout << k << ' ';
        cout << "}\n";
        return;
    }
    elegido[i] = false; subconjuntos(i + 1);
    elegido[i] = true;  subconjuntos(i + 1);
}

void permutaciones() {
    if ((int)p.size() == n) {
        for (int x : p) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int v = 1; v <= n; ++v) {
        if (!usado[v]) {
            usado[v] = true; p.push_back(v);
            permutaciones();
            p.pop_back(); usado[v] = false;
        }
    }
}

int k;
void combinaciones(int desde) {
    if ((int)p.size() == k) {
        for (int x : p) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int v = desde; v <= n; ++v) {
        if (n - v + 1 < k - (int)p.size()) break;
        p.push_back(v);
        combinaciones(v + 1);
        p.pop_back();
    }
}

vector<bool> col, d1, d2;
vector<int> pos;
int soluciones = 0;
void reinas(int f) {
    if (f == n) {
        soluciones++;
        for (int c : pos) cout << c << ' ';
        cout << '\n';
        return;
    }
    for (int c = 0; c < n; ++c) {
        if (!col[c] && !d1[f - c + n] && !d2[f + c]) {
            col[c] = d1[f - c + n] = d2[f + c] = true; pos[f] = c;
            reinas(f + 1);
            col[c] = d1[f - c + n] = d2[f + c] = false;
        }
    }
}

vector<int> a;
int T;
vector<int> elegidos;
void suma(int i, int s) {
    if (s == T) {
        for (int x : elegidos) cout << x << ' ';
        cout << '\n';
        return;
    }
    if (i >= (int)a.size() || s + a[i] > T) return;
    elegidos.push_back(a[i]);
    suma(i + 1, s + a[i]);
    elegidos.pop_back();
    suma(i + 1, s);
}

void hanoi(int n, char origen, char destino, char apoyo) {
    if (n == 0) return;
    hanoi(n - 1, origen, apoyo, destino);
    cout << "disco " << n << ": " << origen << " -> " << destino << '\n';
    hanoi(n - 1, apoyo, destino, origen);
}

vector<string> tk;
pair<long long, int> evaluar(int i) {
    string t = tk[i];
    if (isdigit(t[0])) return {stoll(t), i + 1};
    auto [x, j] = evaluar(i + 1);
    auto [y, m] = evaluar(j);
    long long r = t == "+" ? x + y : t == "-" ? x - y : t == "*" ? x * y : x / y;
    return {r, m};
}

void parentesis(string s, int ab, int ce, int npar) {
    if ((int)s.size() == 2 * npar) { cout << s << '\n'; return; }
    if (ab < npar) parentesis(s + "(", ab + 1, ce, npar);
    if (ce < ab)   parentesis(s + ")", ab, ce + 1, npar);
}

map<char, int> cnt;
int largo;
void palabras(string& w) {
    if ((int)w.size() == largo) { cout << w << '\n'; return; }
    for (auto& [x, c] : cnt) {
        if (c > 0) {
            c--; w.push_back(x);
            palabras(w);
            w.pop_back(); c++;
        }
    }
}

int tab[4][4];
bool fil[4][5], colu[4][5], blo[4][5];
vector<pair<int,int>> vacias;
bool sudoku(int idx) {
    if (idx == (int)vacias.size()) return true;
    auto [r, c] = vacias[idx];
    int b = (r / 2) * 2 + c / 2;
    for (int v = 1; v <= 4; ++v) {
        if (!fil[r][v] && !colu[c][v] && !blo[b][v]) {
            tab[r][c] = v; fil[r][v] = colu[c][v] = blo[b][v] = true;
            if (sudoku(idx + 1)) return true;
            tab[r][c] = 0; fil[r][v] = colu[c][v] = blo[b][v] = false;
        }
    }
    return false;
}

int main() {
    cout << "== Potencia: 3^13 = " << potencia(3, 13) << "\n";

    n = 3; elegido.assign(n + 1, false);
    cout << "== Subconjuntos de {1,2,3}\n"; subconjuntos(1);

    usado.assign(n + 1, false); p.clear();
    cout << "== Permutaciones de 1..3\n"; permutaciones();

    n = 4; k = 2; p.clear();
    cout << "== Combinaciones C(4,2)\n"; combinaciones(1);

    n = 4; col.assign(n, false); d1.assign(2 * n, false); d2.assign(2 * n, false); pos.assign(n, 0);
    cout << "== 4 reinas (columna por fila)\n"; reinas(0);
    cout << "soluciones: " << soluciones << '\n';

    a = {3, 5, 6, 7}; T = 15; sort(a.begin(), a.end());
    cout << "== Suma de subconjuntos {3,5,6,7}, T=15\n"; suma(0, 0);

    cout << "== Hanoi n=3\n"; hanoi(3, 'A', 'C', 'B');

    tk = {"*", "+", "2", "3", "-", "7", "4"};
    cout << "== Prefija * + 2 3 - 7 4 = " << evaluar(0).first << '\n';

    cout << "== Parentesis n=3\n"; parentesis("", 0, 0, 3);

    string pal = "aabc", w; largo = pal.size();
    for (char ch : pal) cnt[ch]++;
    cout << "== Palabras de aabc\n"; palabras(w);

    int ini[4][4] = {{1,2,0,0},{0,0,0,0},{2,0,0,0},{0,0,0,3}};
    for (int r = 0; r < 4; ++r) for (int c = 0; c < 4; ++c) {
        tab[r][c] = ini[r][c];
        int v = ini[r][c], b = (r / 2) * 2 + c / 2;
        if (v) fil[r][v] = colu[c][v] = blo[b][v] = true;
        else vacias.push_back({r, c});
    }
    cout << "== Sudoku 4x4\n";
    if (sudoku(0)) for (auto& fila : tab) { for (int v : fila) cout << v << ' '; cout << '\n'; }
    else cout << "sin solucion\n";
}