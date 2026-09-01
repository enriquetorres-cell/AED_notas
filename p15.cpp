#include <iostream>
using namespace std;

struct node {
    long long e, c;                   
    node* next;
    node(long long e, long long c, node* next = nullptr) : e(e), c(c), next(next) {}
};

struct Poly {
    node *head = nullptr, *tail = nullptr;
    int n = 0;
    void push_back(long long e, long long c) {
        node* nn = new node(e, c);
        if (tail == nullptr) head = tail = nn;
        else { tail->next = nn; tail = nn; }
        ++n;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n1; cin >> n1;
    Poly P;  for (int i = 0; i < n1; ++i) { long long e, c; cin >> e >> c; P.push_back(e, c); }
    int n2; cin >> n2;
    Poly Q;  for (int i = 0; i < n2; ++i) { long long e, c; cin >> e >> c; Q.push_back(e, c); }

    Poly R;
    node *a = P.head, *b = Q.head;

    // ============ ESCRIBE TÚ DESDE AQUÍ ============
    while (a and b) {
        if (a->e < b->e) {
            R.push_back(a->e, a->c);
            a = a-> next;
        }
        else if (a->e > b->e) {
            R.push_back(b->e, b->c);
            b = b-> next;
        }
        else {
            long long sum = a-> c + b->c;
            if (sum != 0) {
                R.push_back(a->e, sum);
            }
            a = a->next;
            b = b->next;
        }
    }
    while (a) {
        R.push_back(a->e, a->c);
        a = a->next;
    }
    while (b) {
        R.push_back(b->e, b->c);
        b = b->next;
    }

    cout << R.n << '\n';
    for (node* c = R.head; c; c = c->next) cout << c->e << ' ' << c->c << '\n';
    return 0;
}