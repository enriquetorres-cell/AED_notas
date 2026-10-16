#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V = int>
struct AVL {
    struct Node {
        K key;
        V val;
        int height, size;
        Node *left, *right;
        Node(const K& k, const V& v) : key(k), val(v), height(0), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    long long rotations = 0;

    int h(Node* u) const { return u ? u->height : -1; }
    int sz(Node* u) const { return u ? u->size : 0; }
    int FB(Node* u) const { return h(u->left) - h(u->right); }
    void update(Node* u) {
        u->height = 1 + max(h(u->left), h(u->right));
        u->size = 1 + sz(u->left) + sz(u->right);
    }

    Node* rotate_right(Node* y) {
        rotations++;
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        update(y);
        update(x);
        return x;
    }

    Node* rotate_left(Node* x) {
        rotations++;
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        update(x);
        update(y);
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

    Node* insert(Node* u, const K& k, const V& v) {
        if (!u) return new Node(k, v);
        if (k < u->key) u->left = insert(u->left, k, v);
        else if (u->key < k) u->right = insert(u->right, k, v);
        else { u->val = v; return u; }
        return rebalance(u);
    }

    Node* min_node(Node* u) const {
        while (u && u->left) u = u->left;
        return u;
    }

    Node* erase(Node* u, const K& k) {
        if (!u) return nullptr;
        if (k < u->key) u->left = erase(u->left, k);
        else if (u->key < k) u->right = erase(u->right, k);
        else {
            if (!u->left || !u->right) {
                Node* child = u->left ? u->left : u->right;
                delete u;
                return child;
            }
            Node* s = min_node(u->right);
            u->key = s->key;
            u->val = s->val;
            u->right = erase(u->right, s->key);
        }
        return rebalance(u);
    }

    void insert(const K& k, const V& v = V()) { root = insert(root, k, v); }
    void erase(const K& k) { root = erase(root, k); }
    int size() const { return sz(root); }
    int height() const { return h(root); }

    Node* find(const K& k) const {
        Node* c = root;
        while (c) {
            if (k < c->key) c = c->left;
            else if (c->key < k) c = c->right;
            else return c;
        }
        return nullptr;
    }

    Node* floor(const K& x) const {
        Node *c = root, *ans = nullptr;
        while (c) {
            if (x < c->key) c = c->left;
            else { ans = c; c = c->right; }
        }
        return ans;
    }

    Node* ceil(const K& x) const {
        Node *c = root, *ans = nullptr;
        while (c) {
            if (c->key < x) c = c->right;
            else { ans = c; c = c->left; }
        }
        return ans;
    }

    K kth(int k) const {
        Node* u = root;
        while (true) {
            int r = sz(u->left) + 1;
            if (k == r) return u->key;
            if (k < r) u = u->left;
            else { k -= r; u = u->right; }
        }
    }

    int count_less(const K& x) const {
        int cnt = 0;
        Node* u = root;
        while (u) {
            if (u->key < x) { cnt += sz(u->left) + 1; u = u->right; }
            else u = u->left;
        }
        return cnt;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int q; cin >> q;
    AVL<long long, long long> T;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            long long s, e; cin >> s >> e;
            auto a = T.floor(s), b = T.ceil(s);
            bool choca = (a && a->val > s) || (b && b->key < e);
            if (choca) cout << "NO\n";
            else { T.insert(s, e); cout << "SI\n"; }
        } else if (op == 2) {
            long long s; cin >> s;
            T.erase(s);
        } else {
            long long t; cin >> t;
            auto a = T.floor(t);
            if (a && a->val > t) cout << a->key << ' ' << a->val << '\n';
            else cout << "LIBRE\n";
        }
    }
}