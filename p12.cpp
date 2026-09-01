
#include <iostream>
using namespace std;

template<typename T>
struct node {
    T data;
    node<T>* next;
    node(T data, node<T>* next = nullptr) : data(data), next(next) {}
};

template<typename T>
struct LinkedList {
    node<T>* head;
    node<T>* tail;
    int n;                       // tamano, mantenido a mano

    LinkedList() { head = tail = nullptr; n = 0; }

    bool empty() { return head == nullptr; }
    int  size()  { return n; }

    // ---------- CONSTRUIR ----------------------------------------
    void push_front(T v) {
        node<T>* nn = new node<T>(v, head);
        if (head == nullptr) tail = nn;
        head = nn;
        ++n;
    }
    void push_back(T v) {
        node<T>* nn = new node<T>(v);
        if (tail == nullptr) head = tail = nn;
        else { tail->next = nn; tail = nn; }
        ++n;
    }
    void insert(node<T>* prev, T v) {          // inserta DESPUES de prev
        node<T>* nn = new node<T>(v, prev->next);
        if (prev == tail) tail = nn;
        prev->next = nn;
        ++n;
    }
    void insert(int k, T v) {                  // 0-indexed
        if (k == 0) { push_front(v); return; }
        node<T>* cur = head;
        for (int i = 1; i <= k - 1; ++i) cur = cur->next;
        insert(cur, v);
    }

    // ---------- BORRAR -------------------------------------------
    void pop_front() {
        if (!head) return;
        node<T>* cur = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete cur;
        --n;
    }
    void erase(node<T>* prev) {                // borra el SIGUIENTE de prev
        if (prev->next == nullptr) return;
        node<T>* cur = prev->next;
        if (cur == tail) tail = prev;
        prev->next = cur->next;
        delete cur;
        --n;
    }
    void erase(int k) {                        // 0-indexed
        if (k == 0) { pop_front(); return; }
        node<T>* cur = head;
        for (int i = 1; i <= k - 1; ++i) cur = cur->next;
        erase(cur);
    }
    void clear() {                             // IMPRESCINDIBLE entre casos de prueba
        while (head) pop_front();
    }

    // ---------- RECORRER -----------------------------------------
    void print() {
        for (node<T>* c = head; c; c = c->next) cout << c->data << ' ';
        cout << '\n';
    }

    // ---------- TECNICAS -----------------------------------------

    // Reverse iterativo. O(n) tiempo, O(1) espacio.
    void reverse() {
        node<T>* last = nullptr;
        node<T>* cur  = head;
        while (cur) {
            node<T>* nxt = cur->next;   // 1. guardo
            cur->next = last;           // 2. giro
            last = cur;                 // 3. nueva cima
            cur = nxt;                  // 4. avanzo
        }
        tail = head;                    // se intercambian
        head = last;
    }

    // Nodo del medio (tortuga y liebre). Con n par: el segundo del medio.
    node<T>* middle() {
        node<T> *slow = head, *fast = head;
        while (fast and fast->next) { slow = slow->next; fast = fast->next->next; }
        return slow;
    }

    // k-esimo desde el final (dos punteros a distancia fija). k >= 1.
    node<T>* kth_from_end(int k) {
        node<T>* ptr = head;
        for (int i = 0; i < k; ++i) { if (!ptr) return nullptr; ptr = ptr->next; }
        node<T>* cur = head;
        while (ptr) { cur = cur->next; ptr = ptr->next; }
        return cur;
    }
    void remove_kth_from_end(int k) {
        node<T>* target = kth_from_end(k);
        if (target == nullptr) return;
        if (target == head) pop_front();
        else erase(kth_from_end(k + 1));
    }

    // Rota k posiciones a la derecha. O(n) gracias al k %= n.
    void rotate_right(int k) {
        if (head == nullptr or head == tail) return;
        k %= n;
        if (k == 0) return;
        tail->next = head;                            // cierro el circulo
        for (int i = 0; i < n - k; ++i) {             // giro
            head = head->next;
            tail = tail->next;
        }
        tail->next = nullptr;                         // abro por el punto nuevo
    }

    // Quita duplicados ADYACENTES (lista ordenada).
    void remove_duplicates() {
        node<T>* cur = head;
        while (cur and cur->next) {
            if (cur->data == cur->next->data) erase(cur);   // no avanzo: puede haber 3+
            else cur = cur->next;
        }
    }

    // Fusiona "other" (ordenada) dentro de esta (ordenada). Reusa nodos.
    // Al terminar, "other" queda vacia.
    void merge_sorted(LinkedList<T>& other) {
        node<T>* a = head;
        node<T>* b = other.head;
        node<T>* nh = nullptr;
        node<T>* nt = nullptr;
        auto append = [&](node<T>* x) {
            if (nt == nullptr) nh = nt = x;
            else { nt->next = x; nt = x; }
        };
        while (a and b) {
            if (a->data <= b->data) { append(a); a = a->next; }
            else                    { append(b); b = b->next; }
        }
        node<T>* resto = a ? a : b;
        while (resto) { append(resto); resto = resto->next; }

        head = nh; tail = nt;
        if (tail) tail->next = nullptr;
        n += other.n;
        other.head = other.tail = nullptr; other.n = 0;
    }
};

// ===============================================================
//  ESQUELETO DE MAIN PARA CODEFORCES
// ===============================================================
int main() {
    cin.tie(0) -> sync_with_stdio(false);

    // --- UN SOLO CASO ---
    // int n, q;  cin >> n >> q;
    // LinkedList<int> L;
    // for (...) { ... L.push_back(x); }
    // ... procesar ...
    // L.print();

    // --- VARIOS CASOS HASTA EOF (ojo: L.clear() en cada vuelta) ---
    // int n, m;
    // int caso = 1;
    // while (cin >> n >> m) {
    //     LinkedList<int> L;              // o L.clear() si es reutilizada
    //     ...
    //     cout << "Case " << caso++ << ": " << S << '\n';
    // }

    // ---- demo de las tecnicas (borrar en el envio) ----
    LinkedList<int> L;
    for (int x : {1,2,3,4,5}) L.push_back(x);
    L.print();                                    // 1 2 3 4 5
    cout << "medio: " << L.middle()->data << '\n';        // 3
    cout << "2do desde el final: " << L.kth_from_end(2)->data << '\n';  // 4
    L.rotate_right(2);  L.print();                // 4 5 1 2 3
    L.reverse();        L.print();                // 3 2 1 5 4
    L.remove_kth_from_end(2); L.print();          // 3 2 1 4
    L.push_back(9);     L.print();                // 3 2 1 4 9   (tail vivo)

    LinkedList<int> A, B;
    for (int x : {1,3,5}) A.push_back(x);
    for (int x : {2,3,6}) B.push_back(x);
    A.merge_sorted(B);  A.print();                // 1 2 3 3 5 6
    A.remove_duplicates(); A.print();             // 1 2 3 5 6
    A.push_back(7);     A.print();                // 1 2 3 5 6 7

    return 0;
}