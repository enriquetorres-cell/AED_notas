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
    T&   front() { return head->data; }         
 
    void push_back(T v) {
        if (head == nullptr) {
            cnode<T>* nn = new cnode<T>(v);
            head = tail = nn;
            nn->next = head;                
        }                                  
        else {
            cnode<T>* nn = new cnode<T>(v, head); 
            tail->next = nn;
            tail = nn;
        }
        ++n;
    }
    void push_front(T v) {
        if (head == nullptr) { push_back(v); return; }
        cnode<T>* nn = new cnode<T>(v, head);
        tail->next = nn;
        head = nn;
        ++n;
    }
 
 
    void send_front_to_back() {
        if (head == nullptr) return;
        head = head->next;
        tail = tail->next;
    }
 
    void pop_front() {
        if (head == nullptr) return;
        cnode<T>* cur = head;
        if (head == tail) {                  
            head = tail = nullptr;
        }
        else {
            head = head->next;
            tail->next = head;         
        }
        delete cur;
        --n;
    }
 
    void clear() { while (head) pop_front(); }  
 
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
        process cur = L.front();            
        if (cur.pending > q) {
            L.front().pending -= q;         
            L.send_front_to_back();        
            timestamp += q;
        }
        else {
            L.pop_front();
            timestamp += cur.pending;        
            cout << cur.name << ' ' << timestamp << '\n';
        }
    }
}

void josephus() {
    int n;
    cin >> n;
    CircularList<int> L;
    for (int i = 1; i <= n; ++i) L.push_back(i);
 
    bool first = true;
    while (not L.empty()) {
        L.send_front_to_back();            
        if (L.empty()) break;
        if (!first) cout << ' ';
        cout << L.front();                   
        first = false;
        L.pop_front();
    }
    cout << '\n';
}
 
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    CircularList<int> L;
    for (int x : {1,2,3,4,5}) L.push_back(x);
    L.print();
    L.send_front_to_back();
    L.print();                    // 2 3 4 5 1
    L.pop_front();
    L.print();                    // 3 4 5 1
    cout << "size: " << L.size() << '\n';   // 4
 
  
    return 0;
}
