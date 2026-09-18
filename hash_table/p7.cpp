#include <bits/stdc++.h>
using namespace std;

const long long OFFSET = 2e9;

template<typename key_type, typename value_type>
struct my_map {
    int m;
    int _size;
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m = 1) : m(m), _size(0) { chains.resize(m); }

    int _hash(long long key) const {
        const int B = 311, MOD = 1e9 + 7;
        key += OFFSET;
        int hash_value = 0;
        while (key > 0) {
            int d = key % 10;
            hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
            key /= 10;
        }
        return hash_value % m;
    }

    int _hash(const string &key) const {
        const int B = 311, MOD = 1e9 + 7;
        int hash_value = 0;
        for (unsigned char c : key) {
            hash_value = (1ll * hash_value * B + (c + 1)) % MOD;
        }
        return hash_value % m;
    }

    value_type& operator [] (const key_type &key) {
        int cp = _hash(key);
        int at = 0;
        while (at < (int)chains[cp].size() and chains[cp][at].first != key) ++at;
        if (at == (int)chains[cp].size()) {
            chains[cp].emplace_back(key, value_type());
            ++_size;
        }
        return chains[cp][at].second;
    }

    bool has_key(const key_type &key) const {
        int cp = _hash(key);
        int at = 0;
        while (at < (int)chains[cp].size() and chains[cp][at].first != key) ++at;
        return at != (int)chains[cp].size();
    }

    void erase(const key_type &key) {
        int cp = _hash(key);
        int at = 0;
        while (at < (int)chains[cp].size() and chains[cp][at].first != key) ++at;
        if (at != (int)chains[cp].size()) {
            if (at + 1 < (int)chains[cp].size()) swap(chains[cp][at], chains[cp].back());
            chains[cp].pop_back();
            --_size;
        }
    }

    void erase_all(const value_type &value) {
        for (int cp = 0; cp < m; ++cp) {
            int at = 0;
            while (at < (int)chains[cp].size()) {
                if (chains[cp][at].second == value) {
                    if (at + 1 < (int)chains[cp].size()) {
                        swap(chains[cp][at], chains[cp].back());
                    }
                    chains[cp].pop_back();
                    --_size;
                } else {
                    ++at;
                }
            }
        }
    }

    int  size()  const { return _size; }
    bool empty() const { return _size == 0; }

    void print() const {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ":\n";
            for (auto &e : chains[i]) cout << "  " << e.first << " --> " << e.second << '\n';
            cout << "End bucket\n";
        }
    }
};

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        string s;
        cin >> s;
        my_map<int,int> gokussj1(2*m);
        int sumacum = 0;
        gokussj1[0] = -1;
        int total = 0;
        int cont = s.size();
        for (int j = 0; j < m; ++j) {
            if (s[j]== 'a')total ++;
            if (s[j]== 'b')total --;;
        }
        for (int j = 0; j < m; ++j) {

            if (s[j]== 'a')sumacum ++;
            if (s[j]== 'b')sumacum --;
            int h = sumacum -total;
            if (gokussj1.has_key(h) ){

                if (cont > (j-gokussj1[h])) {
                    cont = j-gokussj1[h];
                }
            }
            gokussj1[sumacum] = j;
        }
        if (total == 0) {
            cout << 0<< endl;
            continue;
        }
        else if (cont == m) {
            cout << -1 << endl;
        }
        else {
            cout << cont  <<endl;
        }

    }
}