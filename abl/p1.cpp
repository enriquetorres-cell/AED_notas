#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct AVL {
    struct Node {
        T data;
        int height, size;
        Node *left, *right;
        Node(const T& d) : data(d), height(0), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    AVL() = default;
    ~AVL() { destroy(root); }
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    int h(Node* u) const  { return u ? u->height : -1; }
    int sz(Node* u) const { return u ? u->size : 0; }
    int FB(Node* u) const { return h(u->left) - h(u->right); }
    void update(Node* u) {
        u->height = 1 + max(h(u->left), h(u->right));
        u->size   = 1 + sz(u->left) + sz(u->right);
    }

    Node* rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        update(y); update(x);
        return x;
    }
    Node* rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        update(x); update(y);
        return y;
    }

    Node* rebalance(Node* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u->left) < 0) u->left = rotate_left(u->left);
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u->right) > 0) u->right = rotate_right(u->right);
            return rotate_left(u);
        }
        return u;
    }

    Node* insert(Node* u, const T& k) {
        if (!u) return new Node(k);
        if (k < u->data)      u->left  = insert(u->left, k);
        else if (u->data < k) u->right = insert(u->right, k);
        else return u;
        return rebalance(u);
    }
    void insert(const T& k) { root = insert(root, k); }

    Node* erase(Node* u, const T& k) {
        if (!u) return nullptr;
        if (k < u->data)      u->left  = erase(u->left, k);
        else if (u->data < k) u->right = erase(u->right, k);
        else {
            if (!u->left || !u->right) {
                Node* child = u->left ? u->left : u->right;
                delete u;
                return child;
            }
            Node* s = min_node(u->right);
            u->data = s->data;
            u->right = erase(u->right, s->data);
        }
        return rebalance(u);
    }
    void erase(const T& k) { root = erase(root, k); }

    bool contains(const T& k) const {
        Node* c = root;
        while (c) {
            if (k < c->data) c = c->left;
            else if (c->data < k) c = c->right;
            else return true;
        }
        return false;
    }
    Node* min_node(Node* u) const { while (u && u->left) u = u->left; return u; }
    Node* max_node(Node* u) const { while (u && u->right) u = u->right; return u; }

    Node* successor(const T& k) const {
        Node *c = root, *ans = nullptr;
        while (c) {
            if (k < c->data) { ans = c; c = c->left; }
            else c = c->right;
        }
        return ans;
    }
    Node* predecessor(const T& k) const {
        Node *c = root, *ans = nullptr;
        while (c) {
            if (c->data < k) { ans = c; c = c->right; }
            else c = c->left;
        }
        return ans;
    }

    T kth(int k) const {
        Node* u = root;
        while (u) {
            int r = sz(u->left) + 1;
            if (k == r) return u->data;
            if (k < r) u = u->left;
            else { k -= r; u = u->right; }
        }
        throw out_of_range("kth: k fuera de rango");
    }
    int count_less(const T& x) const {
        int cnt = 0; Node* u = root;
        while (u) {
            if (u->data < x) { cnt += sz(u->left) + 1; u = u->right; }
            else u = u->left;
        }
        return cnt;
    }
    int size() const { return sz(root); }
    int height() const { return h(root); }

    void inorder(Node* u, ostream& os) const {
        if (!u) return;
        inorder(u->left, os);
        os << u->data << ' ';
        inorder(u->right, os);
    }
    void preorder(Node* u, ostream& os) const {
        if (!u) return;
        os << u->data << ' ';
        preorder(u->left, os);
        preorder(u->right, os);
    }
    void postorder(Node* u, ostream& os) const {
        if (!u) return;
        postorder(u->left, os);
        postorder(u->right, os);
        os << u->data << ' ';
    }
    void print_inorder()   const { inorder(root, cout);   cout << '\n'; }
    void print_preorder()  const { preorder(root, cout);  cout << '\n'; }
    void print_postorder() const { postorder(root, cout); cout << '\n'; }

    int verify(Node* u, const T* lo, const T* hi) const {
        if (!u) return -1;
        if ((lo && !(*lo < u->data)) || (hi && !(u->data < *hi))) return -2;
        int a = verify(u->left, lo, &u->data), b = verify(u->right, &u->data, hi);
        if (a == -2 || b == -2) return -2;
        if (u->height != 1 + max(a, b) || abs(a - b) > 1) return -2;
        if (u->size != 1 + sz(u->left) + sz(u->right)) return -2;
        return u->height;
    }
    bool is_valid() const { return verify(root, nullptr, nullptr) != -2; }

private:
    void destroy(Node* u) { if (!u) return; destroy(u->left); destroy(u->right); delete u; }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    AVL<int> T;
    for (int x : {10, 20, 30, 40, 50, 25}) {
        T.insert(x);
        cout << "insert " << x << ": raiz=" << T.root->data << " altura=" << T.height() << '\n';
    }
    cout << "inorder:  "; T.print_inorder();
    cout << "preorder: "; T.print_preorder();
    cout << "3er menor: " << T.kth(3) << ", menores que 35: " << T.count_less(35) << '\n';
    auto s = T.successor(25);
    cout << "sucesor de 25: " << (s ? to_string(s->data) : "no") << '\n';
    T.erase(30);
    cout << "tras borrar 30: "; T.print_inorder();
    cout << "valido: " << (T.is_valid() ? "si" : "no") << '\n';
    return 0;
}