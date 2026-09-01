#include <iostream>
using namespace std;
 
template<typename T>
struct cnode {
    T data;
    cnode<T>* next;
    cnode(T data, cnode<T>* next = nullptr) : data(data), next(next) {}
};
 
template<typename T>
struct CircularList {
    cnode<T>* head;
    cnode<T>* tail;
    int n;
 
    CircularList() { head = tail = nullptr; n = 0; }
 
    bool empty() { return head == nullptr; }
    int  size()  { return n; }
    T&   front() { return head->data; }          // referencia: permite modificar
 
    // ---------- CONSTRUIR ----------------------------------------
    void push_back(T v) {
        if (head == nullptr) {
            cnode<T>* nn = new cnode<T>(v);
            head = tail = nn;
            nn->next = head;                 // <-- SE APUNTA A SI MISMO
        }                                    //     sin esto no es circular
        else {
            cnode<T>* nn = new cnode<T>(v, head);   // el ultimo apunta al primero
            tail->next = nn;
            tail = nn;
        }
        ++n;
    }
    // Inserta al inicio. Tambien O(1): el nodo nuevo se cuelga
    // de tail (que ya apuntaba a head) y pasa a ser el head.
    void push_front(T v) {
        if (head == nullptr) { push_back(v); return; }
        cnode<T>* nn = new cnode<T>(v, head);
        tail->next = nn;
        head = nn;                       // tail NO cambia
        ++n;
    }
 
    // ---------- LAS DOS OPERACIONES CLAVE ------------------------
 
    // Manda el frente al final. O(1): no se mueve ningun nodo,
    // solo avanzan los dos punteros (esto SOLO funciona por ser circular).
    void send_front_to_back() {
        if (head == nullptr) return;
        head = head->next;
        tail = tail->next;
    }
 
    // Quita el frente.
    void pop_front() {
        if (head == nullptr) return;
        cnode<T>* cur = head;
        if (head == tail) {                  // queda uno -> lista vacia
            head = tail = nullptr;
        }
        else {
            head = head->next;
            tail->next = head;               // <-- RECOSER el circulo
        }
        delete cur;
        --n;
    }
 
    void clear() { while (head) pop_front(); }   // entre casos de prueba
 
    // ---------- RECORRER -----------------------------------------
    // OJO: "while (c != nullptr)" NO sirve, nunca termina.
    // La parada es "he vuelto al head".
    void print() {
        if (head == nullptr) { cout << '\n'; return; }
        cnode<T>* c = head;
        do {
            cout << c->data << ' ';
            c = c->next;
        } while (c != head);
        cout << '\n';
    }
};
 
// ===============================================================
//  USO 1 — ROUND ROBIN
// ---------------------------------------------------------------
//  Cada proceso recibe como mucho q de CPU y vuelve a la cola.
//  Si lo que le falta cabe en el quantum, termina y sale.
// ===============================================================
struct process {
    string name;
    int pending;
    process(string name = "", int pending = 0) : name(name), pending(pending) {}
};
 
void round_robin() {
    int n, q;
    cin >> n >> q;
    CircularList<process> L;
    for (int i = 0; i < n; ++i) {
        string name; int duration;
        cin >> name >> duration;
        L.push_back(process(name, duration));
    }
    int timestamp = 0;
    while (not L.empty()) {
        process cur = L.front();              // copia
        if (cur.pending > q) {
            L.front().pending -= q;           // descuento el quantum
            L.send_front_to_back();           // y va al final
            timestamp += q;
        }
        else {
            L.pop_front();
            timestamp += cur.pending;         // solo lo que le faltaba
            cout << cur.name << ' ' << timestamp << '\n';
        }
    }
}
 
// ===============================================================
//  USO 2 — JOSEPHUS  (elimina uno de cada dos)
// ---------------------------------------------------------------
//  n ninos en circulo. El 1 sobrevive y va al final, el 2 se
//  elimina, el 3 sobrevive... hasta vaciar el circulo.
//  Complejidad O(n).
// ===============================================================
void josephus() {
    int n;
    cin >> n;
    CircularList<int> L;
    for (int i = 1; i <= n; ++i) L.push_back(i);
 
    bool first = true;
    while (not L.empty()) {
        L.send_front_to_back();               // el de delante sobrevive
        if (L.empty()) break;
        if (!first) cout << ' ';
        cout << L.front();                    // el siguiente se elimina
        first = false;
        L.pop_front();
    }
    cout << '\n';
}
 
// ===============================================================
int main() {
    cin.tie(0) -> sync_with_stdio(false);
 
    // --- demo (borrar en el envio) ---
    CircularList<int> L;
    for (int x : {1,2,3,4,5}) L.push_back(x);
    L.print();
    L.send_front_to_back();
    L.print();                    // 2 3 4 5 1
    L.pop_front();
    L.print();                    // 3 4 5 1
    cout << "size: " << L.size() << '\n';   // 4
 
    // descomenta la que necesites:
    // round_robin();
    // josephus();
    return 0;
}