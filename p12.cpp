#include <iostream>
using namespace std;

template<typename data_type>
struct node {
    data_type data;
    node<data_type>* next;
    node(data_type data, node<data_type>* next = nullptr) : data(data), next(next) {}
};

template<typename data_type>
struct LinkedList {
    node<data_type>* head;
    node<data_type>* tail;
    int tamano;

    LinkedList() { head = tail = nullptr; tamano = 0; }

    bool empty() { return head == nullptr; }
    int  size()  { return tamano; }

    void push_front(data_type valor) {
        node<data_type>* new_node = new node<data_type>(valor, head);
        if (head == nullptr) tail = new_node;
        head = new_node;
        ++tamano;
    }

    void push_back(data_type valor) {
        node<data_type>* new_node = new node<data_type>(valor);
        if (tail == nullptr) head = tail = new_node;
        else { tail->next = new_node; tail = new_node; }
        ++tamano;
    }

    void insert(node<data_type>* prev, data_type valor) {
        node<data_type>* new_node = new node<data_type>(valor, prev->next);
        if (prev == tail) tail = new_node;
        prev->next = new_node;
        ++tamano;
    }

    void insert(int k, data_type valor) {
        if (k == 0) { push_front(valor); return; }
        node<data_type>* current = head;
        for (int i = 1; i <= k - 1; ++i) current = current->next;
        insert(current, valor);
    }

    void pop_front() {
        if (head == nullptr) return;
        node<data_type>* current = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete current;
        --tamano;
    }

    void erase(node<data_type>* prev) {
        if (prev->next == nullptr) return;
        node<data_type>* current = prev->next;
        if (current == tail) tail = prev;
        prev->next = current->next;
        delete current;
        --tamano;
    }

    void erase(int k) {
        if (k == 0) { pop_front(); return; }
        node<data_type>* current = head;
        for (int i = 1; i <= k - 1; ++i) current = current->next;
        erase(current);
    }

    void clear() {
        while (head != nullptr) pop_front();
    }

    void print() {
        node<data_type>* current = head;
        while (current != nullptr) { cout << current->data << ' '; current = current->next; }
        cout << '\n';
    }

    void reverse() {
        node<data_type>* last_chosen = nullptr;
        node<data_type>* current     = head;
        while (current != nullptr) {
            node<data_type>* nxt_node = current->next;
            current->next = last_chosen;
            last_chosen = current;
            current = nxt_node;
        }
        tail = head;
        head = last_chosen;
    }

    node<data_type>* middle() {
        node<data_type>* tortoise = head;
        node<data_type>* hare     = head;
        while (hare != nullptr and hare->next != nullptr) {
            tortoise = tortoise->next;
            hare = hare->next->next;
        }
        return tortoise;
    }

    node<data_type>* kth_from_end(int k) {
        node<data_type>* adelantado = head;
        for (int i = 0; i < k; ++i) {
            if (adelantado == nullptr) return nullptr;
            adelantado = adelantado->next;
        }
        node<data_type>* current = head;
        while (adelantado != nullptr) {
            current = current->next;
            adelantado = adelantado->next;
        }
        return current;
    }

    void remove_kth_from_end(int k) {
        node<data_type>* objetivo = kth_from_end(k);
        if (objetivo == nullptr) return;
        if (objetivo == head) pop_front();
        else erase(kth_from_end(k + 1));
    }

    void rotate_right(int k) {
        if (head == nullptr or head == tail) return;
        k %= tamano;
        if (k == 0) return;
        tail->next = head;
        for (int i = 0; i < tamano - k; ++i) {
            head = head->next;
            tail = tail->next;
        }
        tail->next = nullptr;
    }

    void remove_duplicates() {
        node<data_type>* current = head;
        while (current != nullptr and current->next != nullptr) {
            if (current->data == current->next->data) erase(current);
            else current = current->next;
        }
    }

    void merge_sorted(LinkedList<data_type>& otra) {
        node<data_type>* a = head;
        node<data_type>* b = otra.head;
        node<data_type>* nueva_head = nullptr;
        node<data_type>* nueva_tail = nullptr;

        while (a != nullptr and b != nullptr) {
            node<data_type>* elegido;
            if (a->data <= b->data) { elegido = a; a = a->next; }
            else                    { elegido = b; b = b->next; }
            if (nueva_tail == nullptr) nueva_head = nueva_tail = elegido;
            else { nueva_tail->next = elegido; nueva_tail = elegido; }
        }
        node<data_type>* resto = (a != nullptr) ? a : b;
        while (resto != nullptr) {
            if (nueva_tail == nullptr) nueva_head = nueva_tail = resto;
            else { nueva_tail->next = resto; nueva_tail = resto; }
            resto = resto->next;
        }

        head = nueva_head;
        tail = nueva_tail;
        if (tail != nullptr) tail->next = nullptr;
        tamano += otra.tamano;
        otra.head = otra.tail = nullptr;
        otra.tamano = 0;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    LinkedList<int> L;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < q; ++i) {
        string op;
        cin >> op;
        if (op[0] == 'I') { int k, x; cin >> k >> x; L.insert(k, x); }
        else              { int k;    cin >> k;      L.erase(k); }
    }
    L.print();

    return 0;
}
