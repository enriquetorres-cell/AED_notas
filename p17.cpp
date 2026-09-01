#include <iostream>
using namespace std;

const int MAXN = 100005;

struct node {
    int data;
    node* next;
    node* prev;
    node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

struct DoublyLinkedList {
    node* centinela;

    DoublyLinkedList() {
        centinela = new node(0);
        centinela->next = centinela;
        centinela->prev = centinela;
    }

    void link(node* a, node* b) {
        a->next = b;
        b->prev = a;
    }

    void push_back(node* x) {
        link(centinela->prev, x);
        link(x, centinela);
    }

    void unlink(node* x) {
        link(x->prev, x->next);
    }

    void insert_before(node* at, node* x) {
        link(at->prev, x);
        link(x, at);
    }

    void insert_after(node* at, node* x) {
        link(x, at->next);
        link(at, x);
    }
};

node* pos[MAXN];

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int n, m;
    int caso = 1;
    while (cin >> n >> m) {
        DoublyLinkedList L;
        for (int i = 1; i <= n; ++i) {
            pos[i] = new node(i);
            L.push_back(pos[i]);
        }
        bool reversed_ = false;

        for (int j = 0; j < m; ++j) {
            int op;
            cin >> op;

            if (op == 4) {
                reversed_ = !reversed_;
                continue;
            }

            int a, b;
            cin >> a >> b;
            node* X = pos[a];
            node* Y = pos[b];

            if (reversed_ and op != 3) op = 3 - op;

            if (op == 1 and Y->prev == X) continue;
            if (op == 2 and Y->next == X) continue;

            node* lx = X->prev;
            node* rx = X->next;
            node* ly = Y->prev;
            node* ry = Y->next;

            if (op == 1) {
                L.unlink(X);
                L.link(ly, X);
                L.link(X, Y);
            }
            else if (op == 2) {
                L.unlink(X);
                L.link(Y, X);
                L.link(X, ry);
            }
            else {
                if (rx == Y) {
                    L.link(lx, Y);
                    L.link(Y, X);
                    L.link(X, ry);
                }
                else if (ry == X) {
                    L.link(ly, X);
                    L.link(X, Y);
                    L.link(Y, rx);
                }
                else {
                    L.link(lx, Y);
                    L.link(Y, rx);
                    L.link(ly, X);
                    L.link(X, ry);
                }
            }
        }

        long long suma = 0;
        node* current = reversed_ ? L.centinela->prev : L.centinela->next;
        for (int i = 1; i <= n; ++i) {
            if (i % 2 == 1) suma += current->data;
            current = reversed_ ? current->prev : current->next;
        }

        cout << "Case " << caso++ << ": " << suma << '\n';

        for (int i = 1; i <= n; ++i) delete pos[i];
        delete L.centinela;
    }

    return 0;
}