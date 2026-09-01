
#include <iostream>
using namespace std;

template<typename T>
struct dnode {
    T data;
    dnode<T>* next;
    dnode<T>* prev;
    dnode(T data, dnode<T>* next = nullptr, dnode<T>* prev = nullptr)
        : data(data), next(next), prev(prev) {}
};

template<typename T>
struct DoublyLinkedList {
    dnode<T>* head;
    dnode<T>* tail;
    int n;

    DoublyLinkedList() { head = tail = nullptr; n = 0; }

    bool empty() { return head == nullptr; }
    int  size()  { return n; }

    // ---------- CONSTRUIR ----------------------------------------
    void push_front(T v) {
        dnode<T>* nn = new dnode<T>(v, head, nullptr);
        if (head == nullptr) tail = nn;
        else head->prev = nn;
        head = nn;
        ++n;
    }
    void push_back(T v) {
        dnode<T>* nn = new dnode<T>(v, nullptr, tail);
        if (tail == nullptr) head = nn;
        else tail->next = nn;
        tail = nn;
        ++n;
    }
    // inserta v justo DESPUES de "at"
    void insert_after(dnode<T>* at, T v) {
        dnode<T>* nn = new dnode<T>(v, at->next, at);
        if (at == tail) tail = nn;
        else at->next->prev = nn;
        at->next = nn;
        ++n;
    }
    // inserta v justo ANTES de "at"   <-- imposible en lista simple
    void insert_before(dnode<T>* at, T v) {
        dnode<T>* nn = new dnode<T>(v, at, at->prev);
        if (at == head) head = nn;
        else at->prev->next = nn;
        at->prev = nn;
        ++n;
    }

    // ---------- BORRAR -------------------------------------------
    void pop_front() {
        if (!head) return;
        dnode<T>* cur = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete cur; --n;
    }
    void pop_back() {
        if (!tail) return;
        dnode<T>* cur = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete cur; --n;
    }
    // borra ESE nodo. La razon de ser de la lista doble.
    void erase(dnode<T>* x) {
        if (x == head) { pop_front(); return; }
        if (x == tail) { pop_back();  return; }
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete x; --n;
    }
    void delete_first(T key) {
        for (dnode<T>* c = head; c; c = c->next)
            if (c->data == key) { erase(c); return; }
    }
    void clear() { while (head) pop_front(); }     // entre casos de prueba

    // ---------- DESENGANCHAR SIN BORRAR --------------------------
    // Saca x de la lista pero NO lo destruye (para moverlo a otro sitio).
    void unlink(dnode<T>* x) {
        if (x->prev) x->prev->next = x->next; else head = x->next;
        if (x->next) x->next->prev = x->prev; else tail = x->prev;
        x->next = x->prev = nullptr;
        --n;
    }
    // Vuelve a meter un nodo ya existente justo antes / despues de "at".
    void link_before(dnode<T>* at, dnode<T>* x) {
        x->next = at; x->prev = at->prev;
        if (at->prev) at->prev->next = x; else head = x;
        at->prev = x;
        ++n;
    }
    void link_after(dnode<T>* at, dnode<T>* x) {
        x->prev = at; x->next = at->next;
        if (at->next) at->next->prev = x; else tail = x;
        at->next = x;
        ++n;
    }
    // Mover = unlink + link. Ambos O(1).
    void move_before(dnode<T>* x, dnode<T>* y) { if (x != y) { unlink(x); link_before(y, x); } }
    void move_after (dnode<T>* x, dnode<T>* y) { if (x != y) { unlink(x); link_after (y, x); } }

    // ---------- RECORRER -----------------------------------------
    void print() {
        for (dnode<T>* c = head; c; c = c->next) cout << c->data << ' ';
        cout << '\n';
    }
    void print_reverse() {                    // imposible en lista simple
        for (dnode<T>* c = tail; c; c = c->prev) cout << c->data << ' ';
        cout << '\n';
    }
};

// ===============================================================
//  NOTA PARA EL PROBLEMA DE LAS CAJAS
// ---------------------------------------------------------------
//  1) Los comandos dicen "mueve la caja X". Buscarla recorriendo
//     seria O(n) por comando -> 1e10 operaciones. Solucion:
//         dnode<int>* pos[MAXN];      // pos[X] = nodo de la caja X
//     Array para LLEGAR al nodo, punteros para REORDENAR.
//
//  2) Mover en O(1) -> move_before / move_after de arriba.
//     Por eso hace falta prev: sin el no puedes desenganchar X.
//
//  3) El comando 4 (invertir toda la linea) NO se implementa
//     invirtiendo: seria O(n) por comando. Se guarda un
//         bool reversed = false;
//     y cuando esta activo se intercambia el significado de
//     "izquierda"/"derecha" (o sea, de next y prev). El comando 4
//     pasa a ser  reversed = !reversed;  -> O(1).
//     Misma idea que el k %= n de RotateList: no repitas una
//     operacion cara, guarda solo el efecto neto.
//
//  4) La suma final se pasa de int (2 500 050 000). Usa long long.
//
//  5) Hasta 10 casos de prueba seguidos -> reinicia la estructura
//     en cada uno (clear() o una lista nueva).
// ===============================================================

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    DoublyLinkedList<int> L;
    for (int x : {1,2,3,4,5}) L.push_back(x);
    L.print();                       // 1 2 3 4 5
    L.print_reverse();               // 5 4 3 2 1

    dnode<int>* n1 = L.head;         // el 1
    dnode<int>* n4 = L.head->next->next->next;   // el 4
    L.move_before(n1, n4);           // mueve el 1 a la izquierda del 4
    L.print();                       // 2 3 1 4 5

    L.insert_before(L.head, 0);      L.print();  // 0 2 3 1 4 5
    L.delete_first(3);               L.print();  // 0 2 1 4 5
    L.pop_back();                    L.print();  // 0 2 1 4
    L.push_back(9);                  L.print();  // 0 2 1 4 9
    cout << "size: " << L.size() << '\n';        // 5

    return 0;
}